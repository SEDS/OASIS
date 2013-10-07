// $Id: inscount_tls.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Callback.h"
#include "pin++/Guard.h"
#include "pin++/Lock.h"
#include "pin++/Trace_Tool.h"
#include "pin++/Pintool.h"
#include "pin++/TLS.h"

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

// Force each thread's data to be in its own data cache line so that
// multiple threads do not contend for the same data cache line.
// This avoids the false sharing problem.
#define PADSIZE 56  // 64 byte line size: 64-8

// a running count of the instructions
class thread_data_t
{
public:
  thread_data_t (void)
    : count_ (0) {}

  UINT64 count_;
  UINT8 pad_[PADSIZE];
};

/**
 * @class docount
 *
 * Callback that increments the counter.
 */
class docount : public OASIS::Pin::Callback1 <docount, IARG_THREAD_ID>
{
public:
  docount (void)
    : tls_ (0),
      ins_count_ (0)
  {

  }

  void init (OASIS::Pin::TLS <thread_data_t> * tls, UINT64 count)
  {
    this->tls_ = tls;
    this->ins_count_ = count;
  }

  void handle_analyze (THREADID thr_id)
  {
    this->tls_->get (thr_id)->count_ += this->ins_count_;
  }

private:
  OASIS::Pin::TLS <thread_data_t> * tls_;

  UINT64 ins_count_;
};

/**
 * @class inscount_tls
 *
 * Pin tool that counts the number of instructions in a program.
 */
class inscount_tls : public OASIS::Pin::Trace_Tool <inscount_tls>
{
public:
  inscount_tls (void)
    : num_threads_ (0)
  {

  }

  void handle_instrument (const OASIS::Pin::Trace & trace)
  {
    // Visit every block in the trace, and attach a counter.
    docount * callback = new docount[trace.num_bbl ()];
    docount * iter = callback;

    for (OASIS::Pin::Bbl bbl = trace.bbl_head ();
         bbl.is_valid ();
         bbl.next ())
    {
      iter->init (&this->tls_, bbl.ins_count ());
      bbl.insert_call (IPOINT_ANYWHERE, iter ++);
    }
  }

  void handle_thread_start (THREADID thr_id, OASIS::Pin::Context & ctxt, INT32 flags)
  {
    do
    {
      OASIS::Pin::Guard guard (this->lock_, thr_id + 1);
      ++ this->num_threads_;
    } while (false);

    this->tls_.set (thr_id, new thread_data_t ());
  }

  void handle_fini (INT32)
  {
    std::ofstream fout ("inscount_tls.out");
    fout << "Total number of threads = " << this->num_threads_ << endl;

    for (INT32 t = 0; t < this->num_threads_; t ++)
      fout << "Count[" << decstr (t) << "]= " << this->tls_.get (t)->count_ << std::endl;

    fout.close ();
  }

private:
  OASIS::Pin::TLS <thread_data_t> tls_;

  OASIS::Pin::Lock lock_;

  int num_threads_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <inscount_tls> (argc, argv, true)
    .enable_thread_start ()
    .start_program ();
}

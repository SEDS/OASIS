// $Id: inscount2.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Trace_Tool.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

/**
 * @class docount
 *
 * Callback that increments the counter.
 */
class docount : public OASIS::Pin::Callback0 <docount>
{
public:
  docount (void)
    : count_ (0),
      ins_count_ (0)
  {

  }

  void handle_analyze (void)
  {
    ++ this->count_;
  }

  void ins_count (UINT64 count)
  {
    this->ins_count_ = count;
  }

  UINT64 count (void) const
  {
    return this->ins_count_ * this->count_;
  }

private:
  UINT64 count_;
  UINT64 ins_count_;
};

/**
 * @class icount
 *
 * Pin tool that counts the number of instructions in a program.
 */
class icount : public OASIS::Pin::Trace_Tool <icount>
{
public:
  struct item_t
  {
    item_t (int count)
      : count_ (count),
        callbacks_ (new docount[count])
    {

    }

    item_t (const item_t & rhs)
      : count_ (rhs.count_),
        callbacks_ (rhs.callbacks_)
    {

    }

    ~item_t (void)
    {

    }

    item_t & operator = (item_t & rhs)
    {
      this->callbacks_ = rhs.callbacks_;
      rhs.callbacks_ = 0;

      return *this;
    }

    UINT64 count (void) const
    {
      UINT64 value = 0;

      for (docount * iter = this->callbacks_, * iter_end = this->callbacks_ + this->count_;
           iter != iter_end;
           ++ iter)
        {
          value += iter->count ();
        }

      return value;
    }

    int count_;
    docount * callbacks_;
  };

  typedef std::list < item_t > list_type;

  void handle_instrument (const OASIS::Pin::Trace & trace)
  {
    // Allocate a callback for each BBL.
    item_t callbacks (trace.num_bbl ());
    docount * callback = callbacks.callbacks_;

    for (OASIS::Pin::Bbl bbl = trace.bbl_head ();
         bbl.is_valid ();
         bbl.next ())
    {
      callback->ins_count (bbl.ins_count ());
      bbl.insert_call (IPOINT_ANYWHERE, callback ++);
    }

    this->traces_.push_back (callbacks);
  }

  void handle_fini (INT32)
  {
    list_type::const_iterator
      iter = this->traces_.begin (),
      iter_end = this->traces_.end ();

    UINT64 count = 0;

    for (; iter != iter_end; ++ iter)
      count += iter->count ();

    std::ofstream fout ("inscount.out");
    fout <<  "Count " << count << std::endl;

    fout.close ();
  }

private:
  list_type traces_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <icount> (argc, argv).start_program ();
}

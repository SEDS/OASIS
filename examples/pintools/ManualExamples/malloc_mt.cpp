// $Id: malloc_mt.cpp 2300 2013-10-05 05:33:16Z hillj $

#include "pin++/Image_Tool.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Lock.h"
#include "pin++/Guard.h"
#include "pin++/Routine.h"

#include <stdio.h>

#if defined (TARGET_MAC)
  #define MALLOC "_malloc"
#else
  #define MALLOC "malloc"
#endif

/**
 * @class Before_Malloc
 */
class Before_Malloc :
  public OASIS::Pin::Callback2 <Before_Malloc, IARG_FUNCARG_ENTRYPOINT_VALUE, IARG_THREAD_ID>
{
public:
  Before_Malloc (FILE * file, OASIS::Pin::Lock & lock)
    : file_ (file),
      lock_ (lock)
  {
  }

  void handle_analyze (int size, THREADID thr_id)
  {
    OASIS::Pin::Guard guard (this->lock_, thr_id + 1);

    fprintf (this->file_, "thread %d entered malloc(%d)\n", thr_id, size);
    fflush (this->file_);
  }

private:
  FILE * file_;
  OASIS::Pin::Lock & lock_;
};

/**
 * @class malloc_mt
 */
class malloc_mt : public OASIS::Pin::Image_Tool <malloc_mt>
{
public:
  malloc_mt (void)
    : file_ (::fopen ("malloc_mt.out", "w")),
      before_malloc_ (file_, lock_)
  {

  }

  void handle_instrument (const OASIS::Pin::Image & img)
  {
    using OASIS::Pin::Routine;
    Routine rtn = img.find_routine (MALLOC);

    if (rtn.valid ())
    {
      using OASIS::Pin::Routine_Guard;
      Routine_Guard guard (rtn);

      rtn.insert_call (IPOINT_BEFORE, &this->before_malloc_, 0);
    }
  }

  void handle_fini (INT32)
  {
    ::fclose (this->file_);
  }

private:
  FILE * file_;
  OASIS::Pin::Lock lock_;
  Before_Malloc before_malloc_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <malloc_mt> (argc, argv, true)
    .enable_thread_start ()
    .enable_thread_fini ()
    .start_program ();
}

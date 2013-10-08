// $Id: detach.cpp 2297 2013-10-01 20:31:06Z hillj $

#include "pin++/Instruction_Tool.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <iostream>

/**
 * @class docount
 *
 * Callback that increments the counter.
 */
class docount : public OASIS::Pin::Callback0 <docount>
{
public:
  docount (void)
    : count_ (0) { }

  void handle_analyze (void)
  {
    ++ this->count_;

    if ((this->count_ % 10000) == 0)
      OASIS::Pin::Tool::current ()->detach ();
  }

  UINT64 count (void) const
  {
    return this->count_;
  }

private:
  UINT64 count_;
};

/**
 * @class icount
 *
 * Pin tool that detaches Pin from an application
 */
class detach : public OASIS::Pin::Instruction_Tool <detach>
{
public:
  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    ins.insert_call (IPOINT_BEFORE, &this->callback_);
  }

  void handle_detach (void)
  {
    std::cerr << "Detached at icount = " << this->callback_.count () << std::endl;
  }

private:
  docount callback_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <detach> (argc, argv)
    .enable_detach ()
    .start_program ();
}

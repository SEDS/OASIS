// $Id: icount.cpp 2246 2013-09-06 23:22:57Z hillj $

#include "pin++/Instruction_Tool.h"
#include "pin++/Instruction_Callback0.h"

#include <iostream>

/**
 * @class docount
 *
 * Callback that increments the counter.
 */
class docount : public OASIS::Pin::Instruction_Callback0 <docount>
{
public:
  docount (void)
    : count_ (0) { }

  void handle_analyze (void)
  {
    ++ this->count_;
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
 * Pin tool that counts the number of instructions in a program.
 */
class icount : public OASIS::Pin::Instruction_Tool
{
public:
  virtual void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    ins.insert_call (IPOINT_BEFORE, &this->callback_);
  }

  virtual void handle_fini (INT32 code)
  {
    std::cerr <<  "Count " << this->callback_.count () << std::endl;
  }

private:
  docount callback_;
};

//
// main
//
int main (int argc, char * argv [])
{
  icount tool;

  tool.init (argc, argv);
  tool.start_program ();
}

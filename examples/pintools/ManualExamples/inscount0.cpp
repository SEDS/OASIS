// $Id: inscount0.cpp 2285 2013-09-18 05:24:04Z hillj $

#include "pin++/Callback.h"
#include "pin++/Instruction_Tool.h"
#include "pin++/Pintool.h"

#include <fstream>

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
class icount : public OASIS::Pin::Instruction_Tool <icount>
{
public:
  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    ins.insert_call (IPOINT_BEFORE, &this->callback_);
  }

  void handle_fini (INT32 code)
  {
    std::ofstream fout ("inscount.out");
    fout <<  "Count " << this->callback_.count () << std::endl;

    fout.close ();
  }

private:
  docount callback_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <icount> (argc, argv).start_program ();
}

// $Id: itrace.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Instruction_Tool.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <stdio.h>

/**
 * @class printip
 */
class printip : public OASIS::Pin::Callback1 <printip, IARG_INST_PTR>
{
public:
  printip (FILE * file)
    : file_ (file)
  {
  }

  void handle_analyze (ADDRINT addr)
  {
    ::fprintf (this->file_, "0x%p\n", addr);
  }

private:
  FILE * file_;
};

/**
 * @class itrace
 */
class itrace : public OASIS::Pin::Instruction_Tool <itrace>
{
public:
  itrace (void)
    : file_ (fopen ("itrace.out", "w")),
      printip_ (file_)
  {

  }

  void handle_instrument (const OASIS::Pin::Ins_Ref & ins)
  {
    ins.insert_call (IPOINT_BEFORE, &this->printip_);
  }

  void handle_fini (INT32)
  {
    fprintf (this->file_, "#eof\n");
    fclose (this->file_);
  }

private:
  FILE * file_;
  printip printip_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <itrace> (argc, argv).start_program ();
}

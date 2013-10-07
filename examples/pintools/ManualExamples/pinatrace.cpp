// $Id: pinatrace.cpp 2290 2013-09-20 05:02:26Z hillj $

#include <stdio.h>

#include "pin++/Instruction_Tool.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#if defined (TARGET_MAC)
  #define MALLOC "_malloc"
  #define FREE "_free"
#else
  #define MALLOC "malloc"
  #define FREE "free"
#endif

/**
 * @class Record_Memory_Read
 */
class Record_Memory_Read :
  public OASIS::Pin::Callback2 <Record_Memory_Read, IARG_INST_PTR, IARG_MEMORYOP_EA>
{
public:
  Record_Memory_Read (FILE * file)
    : file_ (file)
  {

  }

  inline void handle_analyze (ADDRINT ip, ADDRINT addr)
  {
    fprintf (this->file_, "%p: R %p\n", ip, addr);
  }

private:
  FILE * file_;
};

/**
 * @class Record_Memory_Write
 */
class Record_Memory_Write :
  public OASIS::Pin::Callback2 <Record_Memory_Write, IARG_INST_PTR, IARG_MEMORYOP_EA>
{
public:
  Record_Memory_Write (FILE * file)
    : file_ (file)
  {

  }

  inline void handle_analyze (ADDRINT ip, ADDRINT addr)
  {
    fprintf (this->file_,"%p: W %p\n", ip, addr);
  }

private:
  FILE * file_;
};

/**
 * @class pinatrace
 */
class pinatrace : public OASIS::Pin::Instruction_Tool <pinatrace>
{
public:
  pinatrace (void)
    : file_ (fopen ("pinatrace.out", "w")),
      mem_read_ (file_),
      mem_write_ (file_)
  {

  }

  void handle_instrument (const OASIS::Pin::Ins_Ref & ins)
  {
    // Instruments memory accesses using a predicated call, i.e.
    // the instrumentation is called iff the instruction will actually be executed.
    //
    // On the IA-32 and Intel(R) 64 architectures conditional moves and REP
    // prefixed instructions appear as predicated instructions in Pin.
    UINT32 operands = ins.memory_operand_count ();

    // Iterate over each memory operand of the instruction.
    for (UINT32 mem_op = 0; mem_op < operands; ++ mem_op)
    {
      if (ins.is_memory_operand_read (mem_op))
        ins.insert_predicated_call (IPOINT_BEFORE, &this->mem_read_, mem_op);

      // Note that in some architectures a single memory operand can be
      // both read and written (for instance incl (%eax) on IA-32)
      // In that case we instrument it once for read and once for write.
      if (ins.is_memory_operand_written (mem_op))
        ins.insert_predicated_call (IPOINT_BEFORE, &this->mem_write_, mem_op);
    }
  }

  void handle_fini (INT32)
  {
    fprintf (this->file_, "#eof\n");
    fclose (this->file_);
  }

private:
  FILE * file_;
  Record_Memory_Read mem_read_;
  Record_Memory_Write mem_write_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <pinatrace> (argc, argv).start_program ();
}

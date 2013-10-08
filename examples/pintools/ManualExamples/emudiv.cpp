// $Id: emudiv.cpp 2308 2013-10-07 15:23:19Z dfeiock $

#include "pin++/Callback.h"
#include "pin++/Instruction_Tool.h"
#include "pin++/Pintool.h"
#include "pin++/Try_Block.h"

#include <iostream>
#include <cstdio>

class Divide_Handler :
  public OASIS::Pin::Try_Block <Divide_Handler>
{
public:
  Divide_Handler (THREADID thr_id, CONTEXT * ctx)
    : Try_Block (thr_id),
      ctx_ (ctx)
  {

  }

  inline
  EXCEPT_HANDLING_RESULT handle_exception (THREADID tid, OASIS::Pin::Exception & ex, PHYSICAL_CONTEXT * pctx)
  {
    if (ex.exception_code () == EXCEPTCODE_INT_DIVIDE_BY_ZERO)
    {
#if 1
      //Temporary work-around, Remove when Mantis #1986 is resolved
      string str = ex.to_string ();
      printf ("GlobalHandler: Caught divide by zero exception. %s\n", str.c_str ());
#else
      std::cout << "GlobalHandler: Caught divide by zero exception. " << PIN_ExceptionToString (info) << endl;
#endif

      ADDRINT faultIp = PIN_GetContextReg (this->ctx_, REG_INST_PTR);
      ex.exception_address (faultIp);
      ex.raise (this->ctx_, tid); // never returns
    }

    return EHR_CONTINUE_SEARCH;
  }

private:
  CONTEXT * ctx_;
};

class Emulate_Int_Divide :
  public OASIS::Pin::Callback5 <Emulate_Int_Divide, IARG_REG_REFERENCE, IARG_REG_REFERENCE, IARG_REG_VALUE, IARG_CONTEXT, IARG_THREAD_ID>
{
public:
  inline
  void handle_analyze (PIN_REGISTER * pGdx, PIN_REGISTER * pGax, ADDRINT divisor, CONTEXT * ctxt, THREADID thr_id)
  {
    Divide_Handler div_handler (thr_id, ctxt);

    UINT64 dividend = *((ADDRINT *)pGdx);
    dividend <<= 32;
    dividend += *((ADDRINT *)pGax);
    *((ADDRINT *)pGax) = dividend / divisor;
    *((ADDRINT *)pGdx) = dividend % divisor;
  }
};

class Emulate_Mem_Divide :
  public OASIS::Pin::Callback6 <Emulate_Mem_Divide, IARG_REG_REFERENCE, IARG_REG_REFERENCE, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_CONTEXT, IARG_THREAD_ID>
{
public:
  inline
  void handle_analyze (PIN_REGISTER * pGdx, PIN_REGISTER * pGax, ADDRINT pDivisor, unsigned int opSize, CONTEXT * ctxt, THREADID thr_id)
  {
    ADDRINT divisor = 0;
    PIN_SafeCopy (&divisor, (VOID *)pDivisor, opSize);
    Divide_Handler div_handler (thr_id, ctxt);

    UINT64 dividend = *((ADDRINT *)pGdx);
    dividend <<= 32;
    dividend += *((ADDRINT *)pGax);

    *((ADDRINT *)pGax) = dividend / divisor;
    *((ADDRINT *)pGdx) = dividend % divisor;
  }
};

/**
 * @class icount
 *
 * Pin tool that counts the number of instructions in a program.
 */
class emudiv : public OASIS::Pin::Instruction_Tool <emudiv>
{
public:
  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    if (ins.mnemonic () == "DIV")
    {
      if (ins.operand_is_reg (0))
        ins.insert_call (IPOINT_BEFORE, &this->emulate_int_divide_, REG_GDX, REG_GAX, REG (ins.operand_reg (0)));
      else
        ins.insert_call (IPOINT_BEFORE, &this->emulate_mem_divide_, REG_GDX, REG_GAX);

      // Remove the old instruction.
      ins.remove ();
    }
  }

  inline
  EXCEPT_HANDLING_RESULT handle_internal_exception (THREADID, OASIS::Pin::Exception & ex, PHYSICAL_CONTEXT *)
  {
    std::cout << "GlobalHandler: Caught unexpected exception. " << ex << std::endl;
    return EHR_UNHANDLED;
  }

private:
  Emulate_Mem_Divide emulate_mem_divide_;
  Emulate_Int_Divide emulate_int_divide_;
};

int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <emudiv> (argc, argv)
    .enable_internal_exception_handler ()
    .start_program ();
}

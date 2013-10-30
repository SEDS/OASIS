// $Id: invocation.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Callback.h"
#include "pin++/Context.h"

#include <fstream>
#include <iostream>

class taken : public OASIS::Pin::Callback <taken (OASIS::Pin::ARG_CONTEXT) >
{
public:
  taken (ofstream & fout)
    : fout_ (fout)
  {

  }

  void handle_analyze (const OASIS::Pin::Context & ctx)
  {
    this->fout_ << "Taken: IP = " << hex << ctx.get_reg (REG_INST_PTR) << dec << endl;
  }

private:
  std::ofstream & fout_;
};

class before : public OASIS::Pin::Callback <before (OASIS::Pin::ARG_CONTEXT) >
{
public:
  before (ofstream & fout)
    : fout_ (fout) { }

  void handle_analyze (const OASIS::Pin::Context & ctx)
  {
    this->fout_ << "Before: IP = " << hex << ctx.get_reg (REG_INST_PTR) << dec << endl;
  }

private:
  std::ofstream & fout_;
};

class after : public OASIS::Pin::Callback <after (OASIS::Pin::ARG_CONTEXT) >
{
public:
  after (ofstream & fout)
    : fout_ (fout) { }

  void handle_analyze (const OASIS::Pin::Context & ctx)
  {
    this->fout_ << "After: IP = " << hex << ctx.get_reg (REG_INST_PTR) << dec << endl;
  }

private:
  std::ofstream & fout_;
};

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  Instrument (std::ofstream & fout)
    : before_ (fout),
      after_ (fout),
      taken_ (fout)
  {

  }

  void handle_instrument (const OASIS::Pin::Image & img)
  {
    for (OASIS::Pin::Section::iterator_type sec_iter, sec_iter_end = sec_iter.make_end ();
         sec_iter != sec_iter_end;
         ++ sec_iter)
    {
      // RTN_InsertCall () and INS_InsertCall () are executed in order of
      // appearance.  In the code sequence below, the IPOINT_AFTER is
      // executed before the IPOINT_BEFORE.

      for (OASIS::Pin::Routine::iterator_type rtn_iter = sec_iter->routine_head (), rtn_iter_end = rtn_iter.make_end ();
           rtn_iter != rtn_iter.make_end ();
           ++ rtn_iter)
      {
        // IPOINT_AFTER is implemented by instrumenting each return
        // instruction in a routine.  Pin tries to find all return
        // instructions, but success is not guaranteed.
        rtn_iter->insert_call (IPOINT_AFTER, &this->after_);

        // Examine each instruction in the routine.
        using OASIS::Pin::Ins;

        for (Ins::iterator_type iter = rtn_iter->instruction_head (), iter_end = iter.make_end ();
             iter != iter_end;
             ++ iter)
        {
          if (iter->is_return ())
          {
            iter->insert_call (IPOINT_BEFORE, &this->before_);
            iter->insert_call (IPOINT_TAKEN_BRANCH, &this->taken_);
          }
        }
      }
    }

  }

private:
  before before_;
  after after_;
  taken taken_;
};

class invocation : public OASIS::Pin::Tool <invocation>
{
public:
  invocation (void)
    : fout_ ("invocation.out")
  {
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    this->fout_.close ();
  }

private:
  std::ofstream fout_;
};

DECLARE_PINTOOL (invocation)

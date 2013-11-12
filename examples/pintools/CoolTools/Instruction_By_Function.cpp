// $Id: Instruction_By_Function.cpp 2278 2013-09-15 20:12:52Z hillj $

/**
 * Pintool which counts the number of instructions per routine per image
 * Ouputs in CSV format to stderr
 */

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"

#include <iomanip>
#include <iostream>

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    using OASIS::Pin::Section;

    for (Section::iterator_type sec_iter = img.section_head (), sec_iter_end = sec_iter.make_end ();
         sec_iter != sec_iter_end;
         ++ sec_iter)
    {
      using OASIS::Pin::Routine;

      for (Routine::iterator_type rtn_iter = sec_iter->routine_head (), rtn_iter_end = rtn_iter.make_end ();
           rtn_iter != rtn_iter_end;
           ++ rtn_iter)
      {
        using OASIS::Pin::Routine_Guard;
        using OASIS::Pin::Ins;
        int count = 0;

        Routine_Guard guard (*rtn_iter);

        for (Ins::iterator_type iter = rtn_iter->instruction_head (), iter_end = iter.make_end ();
             iter != iter_end;
             ++ iter)
        {
          ++ count;
        }

        // Output the count
        std::cerr
          << img.name () << "," << rtn_iter->name () << "," << count << std::endl;
      }
    }
  }
};

class Instruction_By_Function: public OASIS::Pin::Tool <Instruction_By_Function>
{
public:
  Instruction_By_Function (void)
  {
    this->init_symbols ();
    std::cerr
      << "Image,Routine,Instructions" << std::endl;
  }

private:
  Instrument inst_;
};

DECLARE_PINTOOL (Instruction_By_Function)

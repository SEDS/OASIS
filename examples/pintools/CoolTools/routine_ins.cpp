// $Id: staticcount.cpp 2278 2013-09-15 20:12:52Z hillj $

/**
 * Pintool which counts the number of instructions per routine per image
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
          << setw (30) << img.name () << " "
          << setw (30) << rtn_iter->name () << " "
          << setw (20) << count << std::endl;
      }
    }
  }
};

class staticcount : public OASIS::Pin::Tool <staticcount>
{
public:
  staticcount (void)
  {
    this->init_symbols ();
    std::cerr
      << setw (30) << "Image" << " "
      << setw (30) << "Routine" << " "
      << setw (20) << "Instructions" << std::endl;
  }

private:
  Instrument inst_;
};

DECLARE_PINTOOL (staticcount)

// $Id: staticcount.cpp 2278 2013-09-15 20:12:52Z hillj $

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"

#include <iostream>

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    int count = 0;
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

        Routine_Guard guard (*rtn_iter);

        for (Ins::iterator_type iter = rtn_iter->instruction_head (), iter_end = iter.make_end ();
             iter != iter_end;
             ++ iter)
        {
          ++ count;
        }
      }
    }

    std::cerr << "Image " << img.name () << " has " << count << " instructions" << std::endl;
  }
};

class staticcount : public OASIS::Pin::Tool <staticcount>
{
public:
  staticcount (void)
  {
    this->init_symbols ();
  }

private:
  Instrument inst_;
};

DECLARE_PINTOOL (staticcount)

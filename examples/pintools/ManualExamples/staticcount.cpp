// $Id: staticcount.cpp 2278 2013-09-15 20:12:52Z hillj $

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"

#include <iostream>

/**
 * @class staticcount
 *
 * Pin tool that prints a log of the image load and unload events
 * along with static instruction counts for each image
 */
class staticcount : public OASIS::Pin::Image_Instrument <staticcount>
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

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <staticcount> (argc, argv, true).start_program ();
}

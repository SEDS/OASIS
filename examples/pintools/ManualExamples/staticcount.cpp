// $Id: staticcount.cpp 2278 2013-09-15 20:12:52Z hillj $

#include "pin++/Image_Tool.h"
#include "pin++/Pintool.h"

#include <iostream>

/**
 * @class staticcount
 *
 * Pin tool that prints a log of the image load and unload events
 * along with static instruction counts for each image
 */
class staticcount : public OASIS::Pin::Image_Tool <staticcount>
{
public:
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    int count = 0;

    for (OASIS::Pin::Section sec = img.section_head (); sec.valid (); sec.next ())
    {
      for (OASIS::Pin::Routine rtn = sec.routine_head (); rtn.valid (); rtn.next ())
      {
        OASIS::Pin::Routine_Guard guard (rtn);

        using OASIS::Pin::Ins;

        for (Ins::iterator_type iter = rtn.instruction_head (), iter_end = iter.make_end ();
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

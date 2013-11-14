// $Id: Function_Instructions.cpp 2308 2013-10-07 15:23:19Z dfeiock $

#include "pin++/Image.h"
#include "pin++/Pintool.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

class Function_Instructions : OASIS::Pin::Tool <Function_Instructions>
{
public:
  Function_Instructions (void)
  {
    std::cout << "in ctor" << std::endl;
    this->init_symbols ();
  }

  int execute (void)
  {
    std::cout << "in execute" << std::endl;
    using OASIS::Pin::Image;
    using OASIS::Pin::Routine;
    using OASIS::Pin::Section;

    Image img = Image::open (inputfile_.Value ().c_str ());
    std::cout << "opened image" << std::endl;

    if (!img.valid ())
    {
      std::cout << "Could not open " << inputfile_.Value() << endl;
      exit (1);
    }

    std::cout <<
      std::setw (60) << "Routine" << std::setw (80) << "Instructions" << std::endl <<
      std::setw (60) << "------------------------------------------------------------" <<
      std::setw (80) << "--------------------" << std::endl;


    for (Section::iterator_type sec_iter = img.section_head (), sec_iter_end = sec_iter.make_end ();
         sec_iter != sec_iter_end;
         ++ sec_iter)
    {

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

        std::cout <<
          std::setw (60) << rtn_iter->name () << std::setw (80) << count << std::endl;
      }
    }

    img.close ();
    return 0;
  }

private:
  static KNOB <string> inputfile_;
};

KNOB <string> Function_Instructions::inputfile_ (KNOB_MODE_WRITEONCE, "pintool", "i", "<imagename>", "specify an image to read");

//int main (INT32 argc, CHAR **argv)
int main (int argc, char * argv [])
{
  std::cout << "in main" << std::endl;
  PIN_InitSymbols ();
  PIN_Init(argc,argv);
  return OASIS::Pin::Pintool <Function_Instructions> (argc, argv)->execute ();
}

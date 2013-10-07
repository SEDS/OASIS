// $Id: nonstatica.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Image_Tool.h"
#include "pin++/Pintool.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
/**
 * @class nonstatica
 *
 * Pin tool that detaches Pin from an application
 */
class nonstatica : public OASIS::Pin::Image_Tool <nonstatica>
{
public:
  struct address_range
  {
    ADDRINT start;
    ADDRINT end;
  };

  typedef std::vector <address_range> list_type;

  void handle_instrument (const OASIS::Pin::Image & img)
  {
    for (OASIS::Pin::Section sec = img.section_head (); sec.valid (); sec.next ())
    {
      for (OASIS::Pin::Routine rtn = sec.routine_head (); rtn.valid (); rtn.next ())
      {
        std::cout <<
          "  Rtn: " << std::setw (8) << std::hex << rtn.address () <<
          " " << rtn.name () << std::endl;

        std::string path;
        int line;
        this->get_source_location (rtn.address (), NULL, &line, &path);

        if (path != "")
          std::cout << "File " << path << " Line " << line << std::endl;

        OASIS::Pin::Routine_Guard guard (rtn);
        OASIS::Pin::Ins first_instruction = rtn.instruction_head ();

        if (!first_instruction.is_valid ())
          continue;

        address_range range;
        range.start = first_instruction.address ();
        range.end = range.start + first_instruction.size ();
        OASIS::Pin::Ins lastIns = OASIS::Pin::Ins::invalid;

        for (OASIS::Pin::Ins ins = rtn.instruction_head (); ins.is_valid (); ins.next ())
        {
          std::cout << "    " << std::setw (8) << std::hex << ins.address ()
            << " " << ins.disassemble () << std::endl;
          if (lastIns.is_valid ())
          {
            if ((lastIns.address () + lastIns.size ()) == ins.address ())
            {
              range.end = ins.address () + ins.size ();
            }
            else
            {
              std::cout
                << "  range_list.push_back "
                << std::setw (8) << std::hex << range.start << " "
                << std::setw (8) << range.end << std::endl;

              this->range_list_.push_back (range);

              for (list_type::iterator ri = this->range_list_.begin ();
                   ri != this->range_list_.end ();
                   ri++)
              {
                if ((ins.address () >= ri->start) && (ins.address () < ri->end))
                {
                  std::cout
                    << "***Error - above instruction already appreared in this RTN" << std::endl
                    << "  in range_list " << std::setw (8) << std::hex
                    << ri->start << " " << std::setw (8) << std::hex
                    << ri->end << std::endl;

                  std::exit (1);
                }
              }
              range.start = ins.address ();
              range.end = ins.address () + ins.size ();
            }
          }
          lastIns = ins;
        }

        this->range_list_.clear ();
      }
    }
  }

private:
  list_type range_list_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <nonstatica> (argc, argv, true).start_program ();
}

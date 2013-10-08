// $Id: nonstatica.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Image_Tool.h"
#include "pin++/Pintool.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

struct address_range
{
  ADDRINT start;
  ADDRINT end;
};

typedef std::vector <address_range> list_type;

/**
 * @class nonstatica
 *
 * Pin tool that detaches Pin from an application
 */
class nonstatica : public OASIS::Pin::Image_Tool <nonstatica>
{
public:
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

        using OASIS::Pin::Ins;
        Ins::iterator_type ins_iter = rtn.instruction_head ();

        if (!ins_iter->is_valid ())
          continue;

        address_range range;
        range.start = ins_iter->address ();
        range.end = range.start + ins_iter->size ();

        Ins::iterator_type last_ins (Ins::invalid);

        for (Ins::iterator_type ins_iter_end = ins_iter.make_end ();
             ins_iter != ins_iter_end;
             ++ ins_iter)
        {
          std::cout
            << "    " << std::setw (8) << std::hex << ins_iter->address ()
            << " " << ins_iter->disassemble () << std::endl;

          if (last_ins->is_valid ())
          {
            if ((last_ins->address () + last_ins->size ()) == ins_iter->address ())
            {
              range.end = ins_iter->address () + ins_iter->size ();
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
                if ((ins_iter->address () >= ri->start) && (ins_iter->address () < ri->end))
                {
                  std::cout
                    << "***Error - above instruction already appreared in this RTN" << std::endl
                    << "  in range_list " << std::setw (8) << std::hex
                    << ri->start << " " << std::setw (8) << std::hex
                    << ri->end << std::endl;

                  std::exit (1);
                }
              }

              range.start = ins_iter->address ();
              range.end = range.start + ins_iter->size ();
            }
          }

          last_ins = ins_iter;
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

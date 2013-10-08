// $Id: proccount.cpp 2281 2013-09-16 13:41:50Z dfeiock $

#include "pin++/Routine_Tool.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Section.h"
#include "pin++/Image.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <list>
#include <memory>

class routine_count : public OASIS::Pin::Callback0 <routine_count>
{
public:
  class docount : public OASIS::Pin::Callback0 <docount>
  {
  public:
    docount (routine_count & rc)
      : rc_ (rc)
    {

    }

    void handle_analyze (void)
    {
      ++ this->rc_.icount_;
    }

  private:
    routine_count & rc_;
  };

  routine_count (void)
    : rtnCount_ (0),
      icount_ (0)
  {
    this->docount_.reset (new docount (*this));
  }

  std::string name_;
  std::string image_;
  ADDRINT address_;
  RTN rtn_;
  UINT64 rtnCount_;
  UINT64 icount_;

  std::auto_ptr <docount> docount_;

  void handle_analyze (void)
  {
    ++ this->rtnCount_;
  }
};

/**
 * @class proccount
 */
class proccount : public OASIS::Pin::Routine_Tool <proccount>
{
public:
  proccount (void)
    : fout_ ("proccount.out")
  {

  }

  void handle_instrument (const OASIS::Pin::Routine & rtn)
  {
    using OASIS::Pin::Section;
    using OASIS::Pin::Image;
    using OASIS::Pin::Ins;

    // Allocate a counter for this routine
    routine_count * rc = new routine_count ();

    // The RTN goes away when the image is unloaded, so save it now
    // because we need it in the fini
    rc->name_ = rtn.name ();
    rc->image_ = StripPath (Image (Section (rtn.section ()).image ()).name ().c_str ());
    rc->address_ = rtn.address ();

    // Add the counter to the listing.
    this->rtn_count_.push_back (rc);
    rtn.insert_call (IPOINT_BEFORE, rc);

    for (Ins::iterator_type iter = rtn.instruction_head (), iter_end = iter.make_end ();
         iter != iter_end;
         ++ iter)
    {
      iter->insert_call (IPOINT_BEFORE, rc->docount_.get ());
    }
  }

  void handle_fini (INT32)
  {
    this->fout_
      << setw (23) << "Procedure" << " "
      << setw (15) << "Image" << " "
      << setw (18) << "Address" << " "
      << setw (12) << "Calls" << " "
      << setw (12) << "Instructions" << endl;

    std::list <routine_count *>::const_iterator
      iter = this->rtn_count_.begin (),
      iter_end = this->rtn_count_.end ();

    for (; iter != iter_end; ++ iter)
    {
      if ((*iter)->rtnCount_ == 0)
        continue;

      this->fout_
        << setw (23) << (*iter)->name_ << " "
        << setw (15) << (*iter)->image_ << " "
        << setw (18) << hex << (*iter)->address_ << dec << " "
        << setw (12) << (*iter)->rtnCount_ << " "
        << setw (12) << (*iter)->icount_ << endl;
    }

    this->fout_.close ();
  }

private:
  static const char * StripPath (const char * path)
  {
#if defined (TARGET_WINDOWS)
    const char * file = strrchr (path,'\\');
#else
    const char * file = strrchr (path,'/');
#endif

    if (file)
      return file +1 ;
    else
      return path;
  }

  std::ofstream fout_;
  std::list <routine_count *> rtn_count_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <proccount> (argc, argv, true).start_program ();
}

// $Id: inscount1.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Buffer.h"
#include "pin++/Trace_Instrument.h"

#include <fstream>
#include <list>

class docount : public OASIS::Pin::Callback0 <docount>
{
public:
  docount (void)
    : count_ (0),
      ins_count_ (0)
  {

  }

  void handle_analyze (void)
  {
    ++ this->count_;
  }

  void ins_count (UINT64 count)
  {
    this->ins_count_ = count;
  }

  UINT64 count (void) const
  {
    return this->ins_count_ * this->count_;
  }

private:
  UINT64 count_;
  UINT64 ins_count_;
};

class Trace : public OASIS::Pin::Trace_Instrument <Trace>
{
public:
  void handle_instrument (const OASIS::Pin::Trace & trace)
  {
    // Allocate a callback for each BBL.
    item_type item (trace.num_bbl ());
    item_type::iterator callback = item.begin ();

    using OASIS::Pin::Bbl;

    for (Bbl::iterator_type iter = trace.bbl_head (), iter_end = iter.make_end (); iter != iter_end; ++ iter)
    {
      callback->ins_count (iter->ins_count ());
      iter->insert_call (IPOINT_BEFORE, callback ++);
    }

    this->traces_.push_back (item);
  }

  UINT64 count (void) const
  {
    list_type::const_iterator
      iter = this->traces_.begin (),
      iter_end = this->traces_.end ();

    UINT64 count = 0;

    for (; iter != iter_end; ++ iter)
    {
      for (item_type::const_iterator item_iter = iter->begin (), item_iter_end = iter->end ();
           item_iter != item_iter_end;
           ++ item_iter)
      {
        count += item_iter->count ();
      }
    }

    return count;
  }

private:
  typedef OASIS::Pin::Buffer <docount> item_type;
  typedef std::list <item_type> list_type;

  list_type traces_;
};

class inscount : public OASIS::Pin::Tool <inscount>
{
public:
  inscount (void)
  {
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    std::ofstream fout (outfile_.Value ().c_str ());
    fout <<  "Count " << this->trace_.count () << std::endl;
    fout.close ();
  }

private:
  Trace trace_;

  /// @{ KNOBS
  static KNOB <string> outfile_;
  /// @}
};

KNOB <string> inscount::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "o", "inscount.out", "specify output file name");

DECLARE_PINTOOL (inscount);

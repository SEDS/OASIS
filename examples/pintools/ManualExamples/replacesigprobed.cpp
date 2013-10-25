// $Id: replacesigprobed.cpp 2294 2013-10-01 20:09:09Z hillj $

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Replacement_Routine.h"

#include <iostream>

class new_malloc : public OASIS::Pin::Replacement_Routine <new_malloc, void * (int)>
{
public:
  static void * execute (UINT32 arg0)
  {
    std::cout
      << "NewMalloc ("
      << std::hex << ADDRINT (new_malloc::original_funcptr ()) << ", "
      << std::dec << arg0 << ")"
      << std::endl << flush;

    return new_malloc::call_original (arg0);
  }
};

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    OASIS::Pin::Routine rtn = img.find_routine ("malloc");

    if (rtn.valid ())
    {
      std::cout << "Replacing malloc in " << img.name () << endl;
      rtn.replace_signature_probed <new_malloc> (CALLINGSTD_DEFAULT);
    }
  }
};

class replacesigprobed : public OASIS::Pin::Tool <replacesigprobed>
{
public:
  replacesigprobed (void)
  {
    this->init_symbols ();
  }

private:
  Instrument instrument_;
};

DECLARE_PINTOOL_PROBED (replacesigprobed)

// $Id: replacesigprobed.cpp 2294 2013-10-01 20:09:09Z hillj $

#include "pin++/Image_Tool.h"
#include "pin++/Pintool.h"
#include "pin++/Replacement_Routine.h"

#include <iostream>

class new_malloc : public OASIS::Pin::Replacement_Routine <new_malloc, void * (int)>
{
public:
  inline static void * execute (UINT32 arg0)
  {
    // Normally one would do something more interesting with this data.
    //
    std::cout
      << "NewMalloc ("
      << std::hex << ADDRINT (new_malloc::original_funcptr ()) << ", "
      << std::dec << arg0 << ")"
      << std::endl << flush;

    // Call the relocated entry point of the original (replaced) routine.
    //
    return new_malloc::call_original (arg0);
  }
};

class replacesigprobed : public OASIS::Pin::Image_Tool <replacesigprobed>
{
public:
  inline void handle_instrument (const OASIS::Pin::Image & img)
  {
    OASIS::Pin::Routine rtn = img.find_routine ("malloc");

    if (rtn.valid ())
    {
      std::cout << "Replacing malloc in " << img.name () << endl;
      rtn.replace_signature_probed <new_malloc> (CALLINGSTD_DEFAULT);
    }
  }
};

int main (INT32 argc, CHAR *argv[])
{
  using OASIS::Pin::Pintool;
  Pintool <replacesigprobed> (argc, argv, true).start_program_probed ();

  return 0;
}

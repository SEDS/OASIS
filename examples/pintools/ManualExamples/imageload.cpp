// $Id: imageload.cpp 2266 2013-09-10 14:08:35Z hillj $

#include "pin++/Image_Tool.h"
#include "pin++/Pintool.h"

#include <fstream>

/**
 * @class imageload
 */
class imageload : public OASIS::Pin::Image_Tool <imageload>
{
public:
  imageload (void)
    : fout_ ("imageload.out")
  {

  }

  void handle_instrument (const OASIS::Pin::Image & img)
  {
    this->fout_ << "Loading " << img.name () << ", Image id = " << img.id () << std::endl;
  }

  void handle_unload (const OASIS::Pin::Image & img)
  {
    this->fout_ << "Unloading " << img.name () << std::endl;
  }

  void handle_fini (INT32)
  {
    this->fout_.close ();
  }

private:
  std::ofstream fout_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <imageload> (argc, argv, true).start_program ();
}

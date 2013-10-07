// $Id: Flush_Generator.cpp 2118 2012-01-13 20:29:17Z dpuranik $

#include "Flush_Generator.h"
#include "Csharp.h"

#include "fe/PDL_Probe.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Simple_Type.h"

#include "boost/bind.hpp"
#include <algorithm>

namespace OASIS_PDL_BE
{
namespace Csharp
{
//
// Flush_Generator
//
Flush_Generator::
Flush_Generator (std::ostream & csfile)
:csfile_ (csfile)
{

}

//
// ~Flush_Generator
//
Flush_Generator::~Flush_Generator (void)
{

}

//
// visit_probe
//
void Flush_Generator::visit_probe (const OASIS_PDL_Probe & p)
{
  this->csfile_
    << std::endl
    << "/// Flush the contents. This method is not allowed to be overloaded" << std::endl
    << "/// past the implementation of this class." << std::endl
    << "public virtual new int flush ()"<<std::endl
    << "{"<<std::endl
    << "if (0 != this.package_data (this.packager_))" << std::endl
    << "  return -1;"<< std::endl
    << single_line_comment ("Send the data to the EINode.")
    << "return this.send_data (this.packager_);"<<std::endl
    << "}"<<std::endl;
}

}
}

// -*- C++ -*-
// $Id: Standard_EINode.inl 2235 2013-02-06 20:18:09Z dfeiock $

namespace OASIS
{

//
// configuration
//
OASIS_INLINE
const Einode_Configuration & Standard_EINode::configuration (void) const
{
  return this->config_;
}

//
// software_probes
//
OASIS_INLINE
const SoftwareProbe_Hash_Map & Standard_EINode::software_probes (void) const
{
  return this->probes_;
}

}

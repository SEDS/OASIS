// $Id: Software_Probe_Factory_T.cpp 1771 2011-03-02 20:56:37Z hillj $

#if !defined (__OASIS_INLINE__)
#include "Software_Probe_Factory_T.inl"
#endif

#include "ace/CORBA_macros.h"

namespace OASIS
{

//
// create
//
template <typename T>
Software_Probe_Impl * Software_Probe_Factory_T <T>::create (void)
{
  // Allocate a new probe.
  Software_Probe_Impl * probe = 0;
  ACE_NEW_THROW_EX (probe,
                    T (),
                    ACE_bad_alloc ());

  // Return the probe to the EINode
  return probe;
}

}

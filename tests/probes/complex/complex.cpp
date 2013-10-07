// $Id$

#include "complex.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  // 
  // dump
  // 
  void ::OASIS::Point::dump (std::ostream & output) 
  {

    output << "  x: " << this->x << std::endl;
    output << "  y: " << this->y << std::endl;
  }

  // 
  // operator >>
  // 
  bool operator >> (ACE_InputCDR & in, ::OASIS::Point & s) 
  {
    if (!(in >> s.x))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage x\n")),
                        false);

    if (!(in >> s.y))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage y\n")),
                        false);

    return in.good_bit ();
  }


  // 
  // ComplexSoftwareProbe::__metadata__
  // 
  const ComplexSoftwareProbe::METADATA_TYPE ComplexSoftwareProbe::__metadata__;

  // 
  // ComplexSoftwareProbe::metadata
  // 
  const ComplexSoftwareProbe::METADATA_TYPE & ComplexSoftwareProbe::metadata (void) const 
  {
    return ::OASIS::ComplexSoftwareProbe::__metadata__;
  }

  // 
  // ComplexSoftwareProbe
  // 
  ComplexSoftwareProbe::ComplexSoftwareProbe (void) 
  {
  }

  // 
  // ~ComplexSoftwareProbe
  // 
  ComplexSoftwareProbe::~ComplexSoftwareProbe (void) 
  {
  }

  // 
  // recall
  // 
  int ComplexSoftwareProbe::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::OASIS::ComplexSoftwareProbe::recall (input);
  }


  // 
  // recall
  // 
  int ComplexSoftwareProbe::recall (ACE_InputCDR & in) 
  {
    if (0 != ::OASIS::Software_Probe::recall (in))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall ")
                         ACE_TEXT ("::OASIS::Software_Probe data\n")),
                        -1);

    if (!(in >> this->value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage value\n")),
                        -1);

    if (!(in >> this->p_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage p\n")),
                        -1);

    return in.good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void ComplexSoftwareProbe::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  value: " << this->value_ << std::endl;
    output << "  p: ";
    this->p_.dump (output);
    output << std::endl;
  }

  // 
  // value
  // 
  ACE_INT64 ComplexSoftwareProbe::value (void) const
  {
    return this->value_;
  }

  // 
  // p
  // 
  const ::OASIS::Point & ComplexSoftwareProbe::p (void) const
  {
    return this->p_;
  }

  // 
  // p
  // 
  ::OASIS::Point & ComplexSoftwareProbe::p (void)
  {
    return this->p_;
  }
}


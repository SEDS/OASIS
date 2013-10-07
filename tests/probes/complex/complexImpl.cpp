// $Id$

#include "complexImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  // 
  // dump
  // 
  void ::OASIS::PointImpl::dump (std::ostream & output) 
  {

    output << "  x: " << this->x << std::endl;
    output << "  y: " << this->y << std::endl;
  }

  // 
  // operator <<
  // 
  bool operator << (ACE_OutputCDR & out, const ::OASIS::PointImpl & s) 
  {
    if (!(out << s.x))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package x\n")),
                        false);

    if (!(out << s.y))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package y\n")),
                        false);

    return out.good_bit ();
  }


  // 
  // ComplexSoftwareProbeImpl
  // 
  ComplexSoftwareProbeImpl::ComplexSoftwareProbeImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // ComplexSoftwareProbeImpl::__metadata__
  // 
  const ::OASIS::ComplexSoftwareProbe_Metadata ComplexSoftwareProbeImpl::__metadata__ =
  ::OASIS::ComplexSoftwareProbe_Metadata ();


  // 
  // ComplexSoftwareProbeImpl::metadata
  // 
  const ::OASIS::ComplexSoftwareProbe_Metadata & ComplexSoftwareProbeImpl::metadata (void) const 
  {
    return ::OASIS::ComplexSoftwareProbeImpl::__metadata__;
  }

  // 
  // ~ComplexSoftwareProbeImpl
  // 
  ComplexSoftwareProbeImpl::~ComplexSoftwareProbeImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int ComplexSoftwareProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value\n")),
                        -1);

    if (!(p.data_stream () << this->p_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package p\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void ComplexSoftwareProbeImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value: " << this->value () << std::endl;
    output << "  p: ";
    this->p ().dump (output);
    output << std::endl;
  }

  // 
  // value
  // 
  void ComplexSoftwareProbeImpl::value (ACE_INT64 value)
  {
    this->value_ = value;
  }

  // 
  // value
  // 
  ACE_INT64 ComplexSoftwareProbeImpl::value (void) const
  {
    return this->value_;
  }

  // 
  // p
  // 
  void ComplexSoftwareProbeImpl::p (const ::OASIS::PointImpl & p)
  {
    this->p_ = p;
  }

  // 
  // p
  // 
  const ::OASIS::PointImpl & ComplexSoftwareProbeImpl::p (void) const
  {
    return this->p_;
  }

  // 
  // p
  // 
  ::OASIS::PointImpl & ComplexSoftwareProbeImpl::p (void)
  {
    return this->p_;
  }
}


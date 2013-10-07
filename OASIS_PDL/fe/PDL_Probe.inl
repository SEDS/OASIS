// -*- C++ -*-
// $Id: PDL_Probe.inl 2235 2013-02-06 20:18:09Z dfeiock $

//
// OASIS_PDL_Probe_Attr
//
OASIS_INLINE
OASIS_PDL_Probe_Attr::OASIS_PDL_Probe_Attr (void)
: version_major_ (1),
  version_minor_ (0),
  is_abstract_ (false)
{

}

//
// OASIS_PDL_Module
//
OASIS_INLINE
OASIS_PDL_Probe::OASIS_PDL_Probe (void)
: base_probe_ (0)
{

}

//
// ~OASIS_PDL_Module
//
OASIS_INLINE
OASIS_PDL_Probe::~OASIS_PDL_Probe (void)
{

}

//
// attr
//
OASIS_INLINE
const OASIS_PDL_Probe_Attr * OASIS_PDL_Probe::attr (void) const
{
  return this->attr_.get ();
}

//
// attr
//
OASIS_INLINE
void OASIS_PDL_Probe::attr (OASIS_PDL_Probe_Attr * attr)
{
  this->attr_.reset (attr);
}

//
// has_base_probe
//
OASIS_INLINE
bool OASIS_PDL_Probe::has_base_probe (void) const
{
  return this->base_probe_ != 0;
}

//
// base_probe
//
OASIS_INLINE
const OASIS_PDL_Probe * OASIS_PDL_Probe::base_probe (void) const
{
  return this->base_probe_;
}

//
// base_probe
//
OASIS_INLINE
void OASIS_PDL_Probe::base_probe (OASIS_PDL_Probe * p)
{
  this->base_probe_ = p;
}

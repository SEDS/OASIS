// $Id: Standard_Software_Probe_Data_Packager.inl 2224 2012-12-10 06:35:58Z dfeiock $

namespace OASIS
{
//
// Standard_Software_Probe_Data_Packager
//
OASIS_INLINE
Standard_Software_Probe_Data_Packager::Standard_Software_Probe_Data_Packager (void)
: ph_tv_sec_ (0),
  ph_tv_usec_ (0),
  ph_state_ (0),
  ph_seqnum_ (0),
  ph_data_size_ (0),
  is_init_ (false),
  end_of_header_ (0),
  fixed_size_ (0)
{

}

//
// ~Standard_Software_Probe_Data_Packager
//
OASIS_INLINE
Standard_Software_Probe_Data_Packager::~Standard_Software_Probe_Data_Packager (void)
{

}

//
// clone
//
OASIS_INLINE
Software_Probe_Data_Packager *
Standard_Software_Probe_Data_Packager::clone (void)
{
  return new Standard_Software_Probe_Data_Packager ();
}

//
// length
//
OASIS_INLINE
size_t Standard_Software_Probe_Data_Packager::length (void) const
{
  return this->probe_.total_length ();
}

//
// data_size
//
OASIS_INLINE
size_t Standard_Software_Probe_Data_Packager::data_size (void) const
{
  return this->probe_.total_length () - this->end_of_header_;
}

}

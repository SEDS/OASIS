// $Id: Software_Probe_Data_Packager.inl 2224 2012-12-10 06:35:58Z dfeiock $

namespace OASIS
{
//
// Software_Probe_Data_Packager
//
OASIS_INLINE
Software_Probe_Data_Packager::Software_Probe_Data_Packager (void)
{

}

//
// ~Software_Probe_Data_Packager
//
OASIS_INLINE
Software_Probe_Data_Packager::~Software_Probe_Data_Packager (void)
{

}

//
// release
//
OASIS_INLINE
void Software_Probe_Data_Packager::release (void)
{
  delete this;
}

}

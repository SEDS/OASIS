// $Id: Software_Probe_Header.inl 2256 2013-09-08 03:25:36Z hillj $

namespace OASIS
{

//
// Software_Probe_Header
//
OASIS_INLINE
Software_Probe_Header::Software_Probe_Header (void)
: seqnum_ (0),
  state_ (0),
  datasize_ (0)
{

}

//
// ~Software_Probe_Header
//
OASIS_INLINE
Software_Probe_Header::~Software_Probe_Header (void)
{

}


//
// operator ==
//
OASIS_INLINE
bool Software_Probe_Header::
operator == (const Software_Probe_Header & rhs) const
{
  return
    this->uuid_ == rhs.uuid_ &&
    this->last_ts_ == rhs.last_ts_ &&
    this->seqnum_ == rhs.seqnum_ &&
    this->state_ == rhs.state_ &&
    this->datasize_ == rhs.datasize_;
}

//
// operator !=
//
OASIS_INLINE
bool Software_Probe_Header::
operator != (const Software_Probe_Header & rhs) const
{
  return !(*this == rhs);
}

}

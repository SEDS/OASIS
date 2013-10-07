// $Id: Software_Probe_Data_Preparer.inl 2140 2012-03-23 16:51:45Z dfeiock $

namespace OASIS
{
//
// Software_Probe_Data_Preparer
//
OASIS_INLINE
Software_Probe_Data_Preparer::
Software_Probe_Data_Preparer (const char * data, size_t length)
: block_ (length + ACE_CDR::MAX_ALIGNMENT)
{
  ACE_CDR::mb_align (&this->block_);
  this->block_.copy (data, length);
}

//
// Software_Probe_Data_Preparer
//
OASIS_INLINE
Software_Probe_Data_Preparer::
Software_Probe_Data_Preparer (OASIS::DAC::Data_Packet & packet)
: block_ (packet.probe_data_length () + ACE_CDR::MAX_ALIGNMENT)
{
  ACE_CDR::mb_align (&this->block_);
  this->block_.copy (packet.probe_data (), packet.probe_data_length ());
}

//
// ~Software_Probe_Data_Preparer
//
OASIS_INLINE
Software_Probe_Data_Preparer::~Software_Probe_Data_Preparer (void)
{

}

//
// message_block
//
OASIS_INLINE
ACE_Message_Block *
Software_Probe_Data_Preparer::message_block (void)
{
  return &this->block_;
}

}

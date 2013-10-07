// -*- C++ -*-
// $Id: SwitchProbe_Impl.inl 2214 2012-08-10 15:00:08Z dfeiock $

namespace OASIS
{
namespace Network
{
namespace Switch
{

//
// SwitchProbe_Impl
//
OASIS_INLINE
SwitchProbe_Impl::SwitchProbe_Impl (void)
{
  /// Initalize the base_ports_oids
  ACE_CString base_oid;

  /// Name
  base_oid = ".1.3.6.1.2.1.2.2.1.2.";
  this->base_port_oids_.push_back (base_oid);

  /// Status
  base_oid = ".1.3.6.1.2.1.2.2.1.8.";
  this->base_port_oids_.push_back (base_oid);

  /// Speed
  base_oid = ".1.3.6.1.2.1.2.2.1.5.";
  this->base_port_oids_.push_back (base_oid);

  /// Bytes In
  base_oid = ".1.3.6.1.2.1.2.2.1.10.";
  this->base_port_oids_.push_back (base_oid);

  /// Discards In
  base_oid = ".1.3.6.1.2.1.2.2.1.13.";
  this->base_port_oids_.push_back (base_oid);

  /// Errors In
  base_oid = ".1.3.6.1.2.1.2.2.1.14.";
  this->base_port_oids_.push_back (base_oid);

  /// Bytes Out
  base_oid = ".1.3.6.1.2.1.2.2.1.16.";
  this->base_port_oids_.push_back (base_oid);

  /// Discards Out
  base_oid = ".1.3.6.1.2.1.2.2.1.19.";
  this->base_port_oids_.push_back (base_oid);

  /// Errors Out
  base_oid = ".1.3.6.1.2.1.2.2.1.20.";
  this->base_port_oids_.push_back (base_oid);

  /// Out Queue Length
  base_oid = ".1.3.6.1.2.1.2.2.1.21.";
  this->base_port_oids_.push_back (base_oid);

  /// Type
  base_oid = ".1.3.6.1.2.1.2.2.1.3.";
  this->base_port_oids_.push_back (base_oid);
}

//
// ~SwitchProbe_Impl
//
OASIS_INLINE
SwitchProbe_Impl::~SwitchProbe_Impl (void)
{

}

} // namespace OASIS
} // namespace Network
} // namespace Switch

// -*- C++ -*-
// $Id: Software_Probe_Instance.inl 2197 2012-06-04 20:12:04Z dfeiock $

namespace OASIS
{

//
// Software_Probe_Instance
//
OASIS_INLINE
Software_Probe_Instance::Software_Probe_Instance (void)
: inst_name_ ("<undefined>"),
  inst_uuid_ ("<undefined>"),
  inst_type_name_ ("<undefined>"),
  einode_name_ ("<undefined>")
{

}

//
// Software_Probe_Instance
//
OASIS_INLINE
Software_Probe_Instance::
Software_Probe_Instance (const char * inst_name,
                         const ACE_Utils::UUID & inst_uuid,
                         const char * inst_type_name,
                         const char * einode_name)
: inst_name_ (inst_name),
  inst_uuid_ (inst_uuid),
  inst_type_name_ (inst_type_name),
  einode_name_(einode_name)
{

}

//
// Software_Probe_Instance
//
OASIS_INLINE
Software_Probe_Instance::
Software_Probe_Instance (const char * inst_name,
                         const char * inst_uuid,
                         const char * inst_type_name,
                         const char * einode_name)
: inst_name_ (inst_name),
  inst_uuid_ (inst_uuid),
  inst_type_name_ (inst_type_name),
  einode_name_(einode_name)
{

}

}

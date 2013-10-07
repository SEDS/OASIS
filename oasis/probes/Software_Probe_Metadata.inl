// -*- C++ -*-
// $Id: Software_Probe_Metadata.inl 2211 2012-07-25 12:55:51Z dfeiock $

namespace OASIS
{

//
// Software_Probe_Metadata
//
OASIS_INLINE
Software_Probe_Metadata::
Software_Probe_Metadata (const char * uuid,
                         const char * type_info,
                         ACE_UINT8 version_major,
                         ACE_UINT8 version_minor,
                         const char * schema)
: uuid_ (uuid),
  type_info_ (type_info),
  version_major_ (version_major),
  version_minor_ (version_minor),
  schema_ (schema)
{

}

}

// -*- C++ -*-

//=============================================================================
/**
 * @file      PDL_Backend_Manager.h
 *
 *  $Id: PDL_Backend_Manager.h 1866 2011-08-22 13:06:27Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_BACKEND_MANAGER_H_
#define _OASIS_PDL_BACKEND_MANAGER_H_

#include <string>

#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "oasis/config.h"

#include "PDL_BE_export.h"

// Forward decl.
class OASIS_PDL_File;

// Forward decl.
class OASIS_PDL_Backend;

/// Type definition for the backend container.
typedef ACE_Hash_Map_Manager <std::string,
                              OASIS_PDL_Backend *,
                              ACE_Null_Mutex>
                              OASIS_PDL_Backend_Container;

/**
 * @class OASIS_PDL_Backend
 *
 * Base class for all backend generators.
 */
class OASIS_PDL_BE_Export OASIS_PDL_Backend_Manager
{
public:
  /// Default constructor.
  OASIS_PDL_Backend_Manager (void);

  /// Destructor.
  ~OASIS_PDL_Backend_Manager (void);

  int load_backend (const std::string & backend);

  int load_backend (const std::string & name,
                    const std::string & backend);

  int load_backend (const std::string & name,
                    const std::string & location,
                    const std::string & symbol);

  /// Get the collection of loaded backend generators.
  OASIS_PDL_Backend_Container & backends (void);
  const OASIS_PDL_Backend_Container & backends (void) const;

private:
  /// Collection of loaded backends.
  OASIS_PDL_Backend_Container backends_;
};

#define OASIS_PDL_GLOBAL_BE_MANAGER \
  ACE_Singleton <OASIS_PDL_Backend_Manager, ACE_Null_Mutex>::instance ()

#endif  // !defined _OASIS_PDL_BE_INIT_H_

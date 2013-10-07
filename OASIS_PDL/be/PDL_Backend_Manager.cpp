// $Id: PDL_Backend_Manager.cpp 1866 2011-08-22 13:06:27Z hillj $

#include "PDL_Backend_Manager.h"
#include "PDL_Backend.h"
#include "ace/DLL.h"

//
// OASIS_PDL_Backend_Manager
//
OASIS_PDL_Backend_Manager::OASIS_PDL_Backend_Manager (void)
{

}

//
// ~OASIS_PDL_Backend_Manager
//
OASIS_PDL_Backend_Manager::~OASIS_PDL_Backend_Manager (void)
{
  // Release the required backends.
  OASIS_PDL_Backend_Container::ITERATOR iter (this->backends_);
  for (; !iter.done (); ++ iter)
    iter->item ()->destroy ();
}

//
// load_backend
//
int OASIS_PDL_Backend_Manager::load_backend (const std::string & backend)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - loading backend %s\n"),
              backend.c_str ()));

  // Locate the ':', which marks the separation between the
  // backends location and symbol.
  size_t pos = backend.find (':');

  if (pos == std::string::npos)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to located ':' ")
                       ACE_TEXT ("in backend [%s]\n"),
                       backend.c_str ()),
                       -1);

  const std::string name = backend.substr (0, pos);
  const std::string symbol = backend.substr (pos + 1);

  return this->load_backend (name, symbol);
}

//
// load_backend
//
int OASIS_PDL_Backend_Manager::
load_backend (const std::string & name, const std::string & backend)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - loading backend %s\n"),
              backend.c_str ()));

  // Locate the ':', which marks the separation between the
  // backends location and symbol.
  size_t pos = backend.find (':');

  if (pos == std::string::npos)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to located ':' ")
                       ACE_TEXT ("in symbol [%s]\n"),
                       backend.c_str ()),
                       -1);

  const std::string location = backend.substr (0, pos);
  const std::string symbol = backend.substr (pos + 1);

  return this->load_backend (name, location, symbol);
}

//
// load_backend
//
int OASIS_PDL_Backend_Manager::
load_backend (const std::string & name,
              const std::string & location,
              const std::string & symbol)
{
  ACE_DLL be_dll;

  if (0 != be_dll.open (location.c_str (), ACE_DEFAULT_SHLIB_MODE, 0))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open ")
                       ACE_TEXT ("library [%s]\n"),
                       location.c_str ()),
                       -1);

  // Load the creation function symbol from the loaded module.
  typedef OASIS_PDL_Backend * (* FUNCTOR) (void);
  FUNCTOR func = (FUNCTOR) be_dll.symbol (symbol.c_str ());

  if (func == 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to load symbol (%s)\n"),
                       symbol.c_str ()),
                       -1);

  // Create the factory using the loaded symbol. We then are going
  // to store the factory for later usage.
  OASIS_PDL_Backend * be = (*func) ();

  if (0 != this->backends_.bind (name, be))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to store ")
                       ACE_TEXT ("backend [name=%s\n]"),
                       name.c_str ()),
                       -1);

  return 0;
}

//
// backends
//
const OASIS_PDL_Backend_Container &
OASIS_PDL_Backend_Manager::backends (void) const
{
  return this->backends_;
}

//
// backends
//
OASIS_PDL_Backend_Container & OASIS_PDL_Backend_Manager::backends (void)
{
  return this->backends_;
}

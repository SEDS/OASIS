// $Id: NetworkProbe_Impl.cpp 2232 2013-01-28 16:07:41Z dfeiock $

#include "NetworkProbe_Impl.h"

#include "ace/ARGV.h"
#include "ace/CORBA_macros.h"
#include "ace/Get_Opt.h"

#if defined (_WIN32)
  #include <iphlpapi.h>
  #define WIN32_MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
  #define WIN32_FREE(x) HeapFree(GetProcessHeap(), 0, (x))
#else
#include "Procnetdev_Parser.h"
#endif

#include <sstream>
#include <fstream>


namespace OASIS
{
namespace System
{
namespace Network
{

OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_IMPL (create_OASIS_System_Network_NetworkProbe_Impl_Factory,
                                          System_NetworkProbe_Impl_Factory);


//
// SystemNetworkProbe_Impl
//
SystemNetworkProbe_Impl::SystemNetworkProbe_Impl (void)
#if !defined (_WIN32)
  : parser_ (new Procnetdev_Parser ())
#endif
{
}

//
// ~SystemNetworkProbe_Impl
//
SystemNetworkProbe_Impl::~SystemNetworkProbe_Impl (void)
{

}

//
// init
//
int SystemNetworkProbe_Impl::init (const char * args, const char * name)
{
#if defined (_WIN32)
  if (0 != ::OASIS::System::Network::WindowsNetworkProbeImpl::init (args, name))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init\n")),
                       -1);
#else
  if (0 != ::OASIS::System::Network::LinuxNetworkProbeImpl::init (args, name))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init\n")),
                       -1);
#endif
  // Parse the command-line options.
  if (0 != this->parse_args (args))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse probe options\n")),
                       -1);
  return 0;
}

//
// parse_args
//
int SystemNetworkProbe_Impl::parse_args (const char * args)
{
  // Convert the command string into a vector of commands.
  ACE_ARGV_T <char> argv (args);
  const char * optargs = "";

  // Parse the command-line options.
  ACE_Get_Opt get_opt (argv.argc (), argv.argv (), optargs, 0);
  get_opt.long_option ("nic", ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("nic", get_opt.long_option ()))
      {
        if (0 != this->handle_nic_command (get_opt.opt_arg ()))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to handle --nic ")
                             ACE_TEXT ("command\n")),
                             -1);
      }
      break;
    }
  }

  return 0;
}

//
// handle_nic_command
//
int SystemNetworkProbe_Impl::handle_nic_command (const char * args)
{
  ACE_CString nic (args);

  // Extract the interface from the option's argument
  this->nic (nic);
  return 0;
}

//
// handle_collect_data
//
int SystemNetworkProbe_Impl::handle_collect_data (void)
{
#if defined (_WIN32)
  // Modified based on http://msdn.microsoft.com/en-us/library/Aa365943
  MIB_IFTABLE * pIfTable;
  MIB_IFROW * pIfRow;
  DWORD dwSize = 0;
  DWORD dwRetVal = 0;

  // Allocate memory for our pointers.
  pIfTable = (MIB_IFTABLE *) WIN32_MALLOC(sizeof (MIB_IFTABLE));

  if (pIfTable == NULL)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - Error allocating memory for GetIfTable\n")),
                       -1);

  // Make an initial call to GetIfTable to get the necessary size into dwSize
  dwSize = sizeof (MIB_IFTABLE);
  if (GetIfTable (pIfTable, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER) {
    WIN32_FREE (pIfTable);
    pIfTable = (MIB_IFTABLE *) WIN32_MALLOC (dwSize);
    if (pIfTable == NULL)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - Error allocating memory for GetIfTable\n")),
                         -1);
  }

  // Make a second call to GetIfTable to get the actual data we want.
  if ( (dwRetVal = GetIfTable (pIfTable, &dwSize, FALSE)) != NO_ERROR) {
    WIN32_FREE(pIfTable);
    pIfTable = NULL;
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - GetIfTable failed with error %u\n"),
                       dwRetVal),
                       -1);
  }

  // Find requested nic
  for (size_t i = 0; i < pIfTable->dwNumEntries; i++) {
    pIfRow = (MIB_IFROW *) & pIfTable->table[i];
    if (strcmp( (char *)pIfRow->bDescr, this->nic_.c_str ()))
      continue;

    // Collect metrics
    this->recv_bytes_ = pIfRow->dwInOctets;
    this->recv_packets_ = pIfRow->dwInNUcastPkts + pIfRow->dwInUcastPkts;
    this->recv_errors_ = pIfRow->dwInErrors;
    this->recv_drop_ = pIfRow->dwInDiscards;
    this->recv_multicast_ = pIfRow->dwInUcastPkts;
    this->sent_bytes_ = pIfRow->dwOutOctets;
    this->sent_packets_ = pIfRow->dwOutNUcastPkts + pIfRow->dwOutUcastPkts;
    this->sent_errors_ = pIfRow->dwOutErrors;
    this->sent_drop_ = pIfRow->dwOutDiscards;
    this->recv_unknown_ = pIfRow->dwInUnknownProtos;
    this->outbound_queue_length_ = pIfRow->dwOutQLen;
    break;
  }

  WIN32_FREE(pIfTable);
  pIfTable = NULL;

#else
  // Read the contents of /proc/net/dev.
  if (!this->parser_->read_data (this))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read the contents ")
                       ACE_TEXT ("of /proc/net/dev\n")),
                      -1);
#endif

  return 0;
}

}
}
}

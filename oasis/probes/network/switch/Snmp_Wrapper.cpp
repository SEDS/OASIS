// $Id: Snmp_Wrapper.cpp 2214 2012-08-10 15:00:08Z dfeiock $
#include "Snmp_Wrapper.h"

#if !defined (__OASIS_INLINE__)
#include "Snmp_Wrapper.inl"
#endif  // !defined __OASIS_INLINE__

namespace OASIS
{
namespace Network
{
namespace Switch
{

//
// ~Snmp_Wrapper
//
Snmp_Wrapper::~Snmp_Wrapper (void)
{
  if (this->response_)
    snmp_free_pdu(this->response_);
  snmp_close(this->session_);

  SOCK_CLEANUP;
}

//
// init
//
int Snmp_Wrapper::init (const char * host, const char * community)
{
  // Initalize session config
  init_snmp("snmp_wrapper");
  snmp_sess_init (&this->session_config_);
  session_config_.peername = ACE_OS::strdup (host);
  session_config_.version = SNMP_VERSION_1;
  session_config_.community = reinterpret_cast <u_char *> (ACE_OS::strdup (community));
  session_config_.community_len = ACE_OS::strlen (reinterpret_cast <char *> (session_config_.community));

  // Open the session
  SOCK_STARTUP;
  this->session_ = snmp_open (&this->session_config_);
  if (!this->session_)
  {
    SOCK_CLEANUP;
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open snmp session\n")),
                       -1);
  }

  // Initalize the request
  this->request_config_ = snmp_pdu_create (SNMP_MSG_GET);

  return 0;
}

//
// add_oid
//
int Snmp_Wrapper::add_oid (OID & oid)
{
  // Store the oid and register it with the request
  snmp_add_null_var (this->request_config_, oid.query (), oid.query_length ());
  ACE_CString key;
  this->stringify_oid (oid.query (), oid.query_length (), key);
  if (0 != this->oids_.bind (key, &oid))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to add oid\n")),
                       -1);
  return 0;
}

//
// query
//
int Snmp_Wrapper::query (void)
{
  // As best I can tell, requests cannot be reused.
  this->request_ = snmp_clone_pdu (this->request_config_);
  int status = snmp_synch_response (this->session_, this->request_, &this->response_);
  if (!(status == STAT_SUCCESS && this->response_->errstat == SNMP_ERR_NOERROR))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to execute snmp request: status [%d], errstat [%d]\n"),
                       status,
                       this->response_->errstat),
                       -1);

  ACE_CString key;
  for (netsnmp_variable_list * vars = this->response_->variables; vars; vars = vars->next_variable)
  {
    OID * oid = 0;
    key = "";
    this->stringify_oid (vars->name, vars->name_length, key);
    if (0 != this->oids_.find (key, oid))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to find oid for snmp variable [%s]\n"),
                         key.c_str ()),
                         -1);

    oid->value (*vars);
  }

  return 0;
}

//
// stringify_oid
//
void
Snmp_Wrapper::stringify_oid (oid * src, size_t src_len, ACE_CString & dest)
{
  const char delimeter = ',';

  dest += src [0];

  for (size_t i = 1; i < src_len; ++i)
  {
    dest += delimeter;
    dest += src[i];
  }
}

} // namespace OASIS
} // namespace Network
} // namespace Switch

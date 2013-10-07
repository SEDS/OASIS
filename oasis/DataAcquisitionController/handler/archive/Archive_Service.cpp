// $Id: Archive_Service.cpp 2238 2013-03-08 20:50:44Z tmpeiris $

#include "Archive_Service.h"
#include "Metrics_Table.h"
#include "oasis/probes/Software_Probe_Header.h"
#include "oasis/DataAcquisitionController/Data_Packet.h"
#include "oasis/DataAcquisitionController/Execution_Context.h"

#include "adbc/SQLite/Exception.h"

OASIS_DAC_DATA_HANDLER_IMPL (_make_OASIS_DAC_Archive_Service, OASIS::DAC_Archive_Service);

namespace OASIS
{

//
// DAC_Archive_Service
//
DAC_Archive_Service::DAC_Archive_Service (void)
{
}

//
// ~DAC_Archive_Service
//
DAC_Archive_Service::~DAC_Archive_Service (void)
{

}

//
// init
//
int DAC_Archive_Service::init (int argc, ACE_TCHAR * argv [])
{
  try
  {
    int retval = 0;
    // Initialize all the tables in the database.
    using DAC::EXECUTION_CONTEXT;
    DAC::Database & database = EXECUTION_CONTEXT::instance ()->get_database ();
    Metrics_Table::_create (database);

    // Allocate a new metrics table object.
    Metrics_Table * tbl_metrics = 0;
    ACE_NEW_RETURN (tbl_metrics, Metrics_Table (database), -1);
    this->tbl_metrics_.reset (tbl_metrics);

  }
  catch (const ADBC::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.message ().c_str ()));
  }

  int retval = 0;

#if defined (OASIS_HAS_TAO)
  retval = this->tao_service_.init (argc, argv, this);
#endif

  return retval;
}

//
// handle_data
//
int DAC_Archive_Service::handle_data (const DAC::Data_Packet & packet)
{
  try
  {
    // Recall the software probe portion of the data sent from the
    // EINode. This will be needed for storing metrics in the database.
    OASIS::Software_Probe_Header probe;

    int retval = probe.recall (packet.probe_data (),
                               packet.probe_data_length (),
                               packet.byte_order ());

    if (0 != retval)
    {
      ACE_Utils::UUID uuid;
      packet.einode_uuid (uuid);
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall data ")
                         ACE_TEXT ("from EINode %s\n"),
                         uuid.to_string ()->c_str ()),
                         -1);
    }

    // Now that we have recalled the base data, we can submit it
    // to the database for storage!
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - storing metrics for probe %s\n"),
                probe.uuid_.to_string ()->c_str ()));

    const char * data =
      packet.probe_data () + (packet.probe_data_length () - probe.datasize_);

    ACE_Utils::UUID uuid;
    packet.einode_uuid (uuid);

    this->tbl_metrics_->insert_metrics (uuid,
                                        probe.uuid_,
                                        probe.last_ts_,
                                        probe.seqnum_,
                                        probe.state_,
                                        probe.datasize_,
                                        data);

    return 0;
  }
  catch (const ADBC::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.message ().c_str ()));
  }

  return -1;
}

//
// fini
//
int DAC_Archive_Service::fini ()
{
  int retval = 0;
#if defined (OASIS_HAS_TAO)
  retval = this->fini ();
#endif

  return retval;
}

//
// get_remote_service
//
RemoteService_ptr DAC_Archive_Service::get_remote_service()
{
  RemoteService_ptr ptr = 0;
#if defined (OASIS_HAS_TAO)
  ptr = this->tao_service_.get_remote_service ();
#endif

  return ptr;
}

//
// get_data_cursor
//
#if defined (OASIS_HAS_TAO)
Metric_Cursor_i * DAC_Archive_Service::
get_data_cursor (const char * __sqlstr__,
                 std::vector <std::string> & values)
{
  return this->tbl_metrics_->get_metric_cursor (
    __sqlstr__, values);
}
#endif

}
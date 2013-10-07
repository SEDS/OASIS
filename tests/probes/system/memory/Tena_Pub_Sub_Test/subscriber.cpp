// $Id: subscriber.cpp 2006 2011-10-10 23:46:16Z dfeiock $

#include "TENA/Middleware/config.h"
#include "TENA/Middleware/RuntimePtr.h"
#include "TENA/Middleware/ApplicationConfiguration.h"

#include "oasis/middleware/tena/Subscriber_Task.h"

#include "Data_Observer.h"
#include "TENA/Time/Impl.h"

#if defined (_WIN32)
  #include "OASIS/System/Memory/WindowsMemoryProbe.h"
#else
  #include "OASIS/System/Memory/LinuxMemoryProbe.h"
#endif

static void
parse_endpoint (std::string const & str, TENA::Middleware::Endpoint & endpoint)
{
  endpoint = TENA::Middleware::Endpoint (str);
}

class Configuration :
  public TENA::Middleware::ApplicationConfiguration
{
public:
  /*! \brief Initialize the application configuration and parse the supplied
   *         options.
   *
   * \param[in,out] argc The number of elements in the command-line options
   *                     vector.
   *
   * \param[in,out] argv The vector of command-line options.
   *
   * \param[in] configFilePathname Pathname of the configuration file.
   *
   * \param[in] configFilePrefix Prefix of configuration file options to parse.
   *
   * \param[in] envPrefix Prefix of environment variables to apply for this
   *                      application; "" disables parsing of the environment.
   */
  Configuration (int & argc, char * argv [], std::string const & pathname)
    : TENA::Middleware::ApplicationConfiguration (argc, argv, pathname, "Client", "", "")
  {
    this->defineSettings ();
  }

  //! Adds allowable settings (i.e., "options") for this application.
  void defineSettings ()
  {
    this->addSettings()
      ( "emEndpoint",
        TENA::Middleware::Utils::Value< TENA::Middleware::Endpoint >()
        .setInitializer( &parse_endpoint ),
        "The endpoint on which the executionManager is listening for requests, "
        "e.g., -emEndpoint <hostname>:55100 to contact an EM running on the "
        "host, <hostname>, listening on port 55100." )

      ("sessionName",
       TENA::Middleware::Utils::Value < std::string > ().setDefault ("TestSession"),
       "Set the session name for the execution" );

  }
};

//
// main
//
int main (int argc, char * argv [])
{
  try
  {
    // Initialize the TENA middleware.
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - subscriber: initializing TENA middleware\n")));

    Configuration config (argc, argv, "");
    config.parse (argc, argv);

    TENA::Middleware::RuntimePtr runtime (TENA::Middleware::init (config.tenaConfiguration ()));

    // Join an existing execution.
    TENA::Middleware::Endpoint endpoint = config["emEndpoint"].getValue < TENA::Middleware::Endpoint > ();

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - subscriber: joining execution %s\n"),
                endpoint.toString ().c_str ()));

    TENA::Middleware::ExecutionPtr execution (runtime->joinExecution (endpoint));

    // Begin a session.
    std::string session_name = config["sessionName"].getValue <std::string> ();

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - subscriber: creating session %s\n"),
                session_name.c_str ()));

    TENA::Middleware::SessionPtr session (execution->createSession (session_name));

    // Register a subscriber for the MemoryProbe data!
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - subscriber: subscribing to data\n"),
                session_name.c_str ()));

#if defined (_WIN32)
    namespace PlatformMemoryProbe = OASIS::System::Memory::WindowsMemoryProbe;
#else
    namespace PlatformMemoryProbe = OASIS::System::Memory::LinuxMemoryProbe;
#endif

    PlatformMemoryProbe::SubscriptionPtr subscription (new PlatformMemoryProbe::Subscription ());
    OASIS::Test::Data_Observer * data_observer = new OASIS::Test::Data_Observer (10);
    PlatformMemoryProbe::AbstractObserverPtr observer (data_observer);
    subscription->addObserver (observer);

    PlatformMemoryProbe::subscribe (*session, subscription, false);

    // Activate the task to recieve events.
    OASIS::Tena_Subscriber_Task task (session);
    if (0 != task.activate (1))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - subscriber: failed to activate task\n")),
                         1);

    // Wait for the observer to receive data.
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - subscriber: waiting to receive all data...\n")));
    data_observer->wait ();

    // Unsubscribe from the data.
    ACE_ERROR ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - subscriber: shutting down test\n")));
    PlatformMemoryProbe::unsubscribe (*session);

    // Kill the session and wait for all threads to return.
    ACE_ERROR ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - subscriber: waiting for task to exit\n")));

    task.reset ();
    task.wait ();

    ACE_ERROR ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - subscriber: test completed!!\n")));

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - subscriber: %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - subscriber exception: caught unknown exception\n")));
  }

  return 1;
}

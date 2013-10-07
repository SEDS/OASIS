eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2225 2012-12-13 23:05:29Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the test and execution manager
$the_TEM_ep = "localhost:50000";
print "**** info: running the test execution manager\n";
$the_TnE_options = "--dac-list=the_DACS.dat -ORBEndpoint iiop://$the_TEM_ep --name=SmokeTest --debug";
$the_TnE = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_tem", $the_TnE_options);
$the_TnE->Spawn ();
sleep (5);

# Start the DAC
print "**** info: running the DAC\n";
$the_DAC_ep = "localhost:20000";
$the_DAC_options = "-ORBInitRef TEM=corbaloc:iiop:localhost:50000/OASIS/TEM -ORBEndpoint iiop://$the_DAC_ep -c dac.conf --name=SmokeTest -v --debug";

$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();
sleep (5);

# Run the client application
print "**** info: running the client application\n";
$the_SmokeTest_opts = "-c einode.conf";
$the_SmokeTest = new PerlACE::Process ("OASIS_Command_Injector_Test_Client", $the_SmokeTest_opts);
$the_SmokeTest->Spawn ();
sleep (5);

# Use the command injector to change the publication rate.
@commands = ("\"SmokeTest.TestEINode.DummyProbe --hertz=1\"",
             "\"SmokeTest.TestEINode.DummyProbe --hertz=3\"",
             "\"SmokeTest.TestEINode.DummyProbe --hertz=2\"",
             "\"SmokeTest.TestEINode.DummyProbe --hertz=5\"");

foreach (@commands) {
  $injector_opts = "-ORBInitRef TEM=corbaloc:iiop:$the_TEM_ep/OASIS/TEM $_";
  print "$injector_opts\n";

  $the_Injector = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_cmd", $injector_opts);
  $the_Injector->Spawn ();

  sleep (5);

  # Kill the application
  $the_Injector->Kill ();
  $the_Injector->TimedWait (1);
}

# Kill the application
$the_SmokeTest->Kill ();
$the_SmokeTest->TimedWait (1);

# Kill the test and execution manager.
$the_TnE->Kill ();
$the_TnE->TimedWait (1);

# Kill the DAC
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

exit 0;

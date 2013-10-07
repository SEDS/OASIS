eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2115 2012-01-13 13:57:53Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the DAC
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 --name=SmokeTest --channels=channels.conf --database=StandardDAC.db";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (5);

# Run the subscriber application
$the_Subcriber_opts = "-ORBInitRef DAC=corbaloc:iiop:localhost:20000/SmokeTest";
$the_Subcriber = new PerlACE::Process ("DAC_Publisher_Service_Smoke_Test_Subscriber", $the_Subcriber_opts);
$the_Subcriber->Spawn ();

sleep (2);

# Run the test application
$the_SmokeTest_opts = "";
$the_SmokeTest = new PerlACE::Process ("DAC_Publisher_Service_Smoke_Test_App", $the_SmokeTest_opts);
$the_SmokeTest->Spawn ();

sleep (15);

# Kill the application
$the_SmokeTest->Kill ();
$the_SmokeTest->TimedWait (1);

# Kill the processes
$the_Subcriber->Kill ();
$the_Subcriber->TimedWait (1);

# Kill the DAC
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

exit 0;

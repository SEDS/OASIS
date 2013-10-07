eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2115 2012-01-13 13:57:53Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

$TENA_HOME = "$ENV{'TENA_HOME'}";
$TENA_VERSION = "$ENV{'TENA_VERSION'}";
$TENA_PLATFORM = "$ENV{'TENA_PLATFORM'}";

# Start the TENA execution manager
print "===== Starting the execution manager...\n";
$the_EM_options = "-listenEndpoints localhost:50000 -nonInteractive";
$the_EM = new PerlACE::Process ("$TENA_HOME/$TENA_VERSION/bin/$TENA_PLATFORM/executionManager", $the_EM_options);
$the_EM->Spawn ();

sleep (5);

# Start the DAC
print "===== Starting the DAC...\n";
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 --name=test --config=main.conf --database=test.db -v --debug";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (5);

# Start the application.
print "===== Starting the driver application...\n";
$the_App_options = "--config=test.einode";
$the_App = new PerlACE::Process ("OASIS_Tena_Publisher_Handle_Registration_Test", $the_App_options);
$the_App->Spawn ();

sleep (15);

# Kill the application
$the_App->Kill ();
$the_App->TimedWait (1);

# Kill the DAC
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

# Kill the TENA execution manager
$the_EM->Kill ();
$the_EM->TimedWait (1);

exit 0;

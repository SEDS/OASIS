eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2110 2012-01-12 19:47:19Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

$TENA_HOME = "$ENV{'TENA_HOME'}";
$TENA_VERSION = "$ENV{'TENA_VERSION'}";
$TENA_PLATFORM = "$ENV{'TENA_PLATFORM'}";

$emListenEndpoint = "localhost:50000";
$emEndpoint = "iiop://$emListenEndpoint";

# Start the TENA execution manager
print "===== (script): Starting the execution manager...\n";
$the_EM_options = "-listenEndpoints $emListenEndpoint -nonInteractive";
$the_EM = new PerlACE::Process ("$TENA_HOME/$TENA_VERSION/bin/$TENA_PLATFORM/executionManager", $the_EM_options);
$the_EM->Spawn ();

sleep (5);

# Start the client application.
print "===== (script): Starting the subscriber application...\n";
$the_Client_App_options = "-emEndpoint $emEndpoint -sessionName TestSession -listenEndpoints localhost:50003";
$the_Client_App = new PerlACE::Process ("OASIS_Tena_Memory_Pub_Sub_Test_Subscriber", $the_Client_App_options);
$the_Client_App->Spawn ();

sleep (5);

# Start the DAC
#print "===== (script): Starting the DAC...\n";
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 --name=test --config=main.conf --database=test.db -v --debug";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (5);

# Start the publisher application.
print "===== (script): Starting the publisher application...\n";
$the_App_options = "--config=test.einode";
$the_App = new PerlACE::Process ("OASIS_Tena_Memory_Pub_Sub_Test", $the_App_options);
$the_App->Spawn ();

print "===== (script): Waiting 10 seconds for subscriber application to exit...\n";
$the_Client_App->WaitKill (10);
$the_Client_App->TimedWait (1);

# Kill the publisher
print "===== (script): Killing the publisher...\n";
$the_App->Kill ();
$the_App->TimedWait (1);

# Kill the DAC
print "===== (script): Killing the DAC...\n";
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

# Kill the TENA execution manager
print "===== (script): Killing the execution manager...\n";
$the_EM->Kill ();
$the_EM->TimedWait (1);

exit 0;

eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 1839 2011-08-15 04:18:17Z hillj $
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

# Start the DAC
print "===== (script): Starting the DAC...\n";
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 --name=test --config=main.conf --database=test.db";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (5);

# Kill the DAC
print "===== (script): Killing the DAC...\n";
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

# Kill the TENA execution manager
print "===== (script): Killing the execution manager...\n";
$the_EM->Kill ();
$the_EM->TimedWait (1);

exit 0;

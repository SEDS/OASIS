eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2115 2012-01-13 13:57:53Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the DAC
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 --name=LoggerTest -c ace_logger.conf --database=ace_logger.db";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (2);

# Run the smoke test.
$the_App_opts = "-ORBInitRef DAC=corbaloc:iiop:localhost:20000/LoggerTest";
$the_App = new PerlACE::Process ("OASIS_ACE_Logging_Software_Probe_Test", $the_App_opts);
$the_App->Spawn ();

sleep (15);

# Kill the application
$the_App->Kill ();
$the_App->TimedWait (1);

# Kill the DAC
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

exit 0;

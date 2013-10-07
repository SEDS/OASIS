eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2124 2012-01-23 17:24:00Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the DAC
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 --name=StandardDAC -c Daemon_Test.dac --database=StandardDAC.db -v --debug";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (5);

# Run the example.
$the_Example_options = "--debug --disable=Memory -c Daemon_Test.einode";
$the_Example = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_mon", $the_Example_options);
$the_Example->Spawn ();

sleep (10);

# Kill the example
$the_Example->Kill ();
$the_Example->TimedWait (1);

# Kill the DAC process.
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

exit 0;

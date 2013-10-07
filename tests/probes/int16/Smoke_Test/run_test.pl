eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2149 2012-04-03 16:29:09Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the DAC
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 --name=StandardDAC -c Smoke_Test.dac --database=StandardDAC.db -v --debug";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (2);

# Run the example
$the_Example_options = "-c Smoke_Test.einode";
$the_Example = new PerlACE::Process ("OASIS_Int16_Smoke_Test", $the_Example_options);
$the_Example->SpawnWaitKill (15);

# Kill the DAC process.
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

exit 0;

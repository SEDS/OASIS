eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2155 2012-04-26 19:17:07Z dpuranik $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the DAC
$the_DAC_options = "-ORBEndpoint iiop://localhost:30000 --name=SmokeTest -c Smoke_Test.conf -v --debug";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (2);

# Run the example.
$the_Example_options = "--debug -c Smoke_Test.einode --hertz=1";
$the_Example = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_mon", $the_Example_options);
$the_Example->Spawn ();

sleep (999999);

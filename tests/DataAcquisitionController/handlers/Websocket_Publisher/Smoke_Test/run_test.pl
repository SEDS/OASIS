eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2209 2012-06-23 04:03:35Z dpuranik $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the test and execution manager
$the_TnE_options = "--dac-list=the_DACS.dat -ORBEndpoint iiop://localhost:50000 --name=SmokeTestTEM --debug -disable=Memory";
$the_TnE = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_tem", $the_TnE_options);
$the_TnE->Spawn ();

sleep (5);

# Start the DAC
$the_DAC_options = "-ORBEndpoint iiop://localhost:30000 -ORBInitRef TEM=corbaloc:iiop:localhost:50000/OASIS/TEM --name=SmokeTest1 -v --debug -c Smoke_Test.conf";
$the_DAC1 = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC1->Spawn ();

#sleep (5);

# Start the DAC
#$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 -ORBInitRef TEM=corbaloc:iiop:localhost:50000/OASIS/TEM --name=SmokeTest2 -v --debug";
#$the_DAC2 = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
#$the_DAC2->Spawn ();

sleep (5);

# Start the DAC
#$the_DAC_options = "-ORBEndpoint iiop://localhost:25000 -ORBInitRef TEM=corbaloc:iiop:localhost:50000/OASIS/TEM --name=SmokeTest3 -v --debug";
#$the_DAC3 = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
#$the_DAC3->Spawn ();

# Run the example.
$the_Example_options = "--debug -c Smoke_Test.einode --hertz=1";
$the_Example = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_mon", $the_Example_options);
$the_Example->Spawn ();

#sleep (5);

#$the_DAC1->TerminateWaitKill (10);


sleep (999999);

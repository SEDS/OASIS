eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2190 2012-05-31 18:13:59Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the test and execution manager
print "**** info: running the test execution manager\n";
$the_TnE_options = "-ORBEndpoint iiop://localhost:50000 --name=SmokeTest";
$the_TnE = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_tem", $the_TnE_options);
$the_TnE->Spawn ();

sleep (2);

# Start the DAC
print "**** info: running the DAC\n";
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 -ORBInitRef TEM=corbaloc:iiop:localhost:50000/OASIS/TEM --name=SmokeTest -v --debug";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (2);

# Finally, run the smoke test.
print "**** info: running the smoke test\n";
$the_SmokeTest_opts = "-ORBInitRef TEM=corbaloc:iiop:localhost:50000/OASIS/TEM --value=1";
$the_SmokeTest = new PerlACE::Process ("OASIS_TestExecutionManager_SmokeTest", $the_SmokeTest_opts);
$the_SmokeTest->Spawn ();
$the_SmokeTest->Wait ();

# Start the DAC
print "**** info: running the DAC\n";
$another_DAC_options = "-ORBEndpoint iiop://localhost:30000 -ORBInitRef TEM=corbaloc:iiop:localhost:50000/OASIS/TEM --name=AnotherTest -v --debug";
$another_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $another_DAC_options);
$another_DAC->Spawn ();

sleep (2);

# Finally, run the smoke test.
print "**** info: running the smoke test\n";
$the_SmokeTest_opts = "-ORBInitRef TEM=corbaloc:iiop:localhost:50000/OASIS/TEM --value=2";
$the_SmokeTest = new PerlACE::Process ("OASIS_TestExecutionManager_SmokeTest", $the_SmokeTest_opts);
$the_SmokeTest->Spawn ();
$the_SmokeTest->Wait ();

# Kill the DAC
print "**** info: killing the DAC\n";
$the_DAC->TerminateWaitKill (5);

# Kill the DAC
print "**** info: killing the DAC\n";
$another_DAC->TerminateWaitKill (5);

# Finally, run the smoke test.
print "**** info: running the smoke test\n";
$the_SmokeTest_opts = "-ORBInitRef TEM=corbaloc:iiop:localhost:50000/OASIS/TEM --value=0";
$the_SmokeTest = new PerlACE::Process ("OASIS_TestExecutionManager_SmokeTest", $the_SmokeTest_opts);
$the_SmokeTest->Spawn ();
$the_SmokeTest->Wait ();

# Kill the test and execution manager.
$the_TnE->TerminateWaitKill (2);

exit 0;

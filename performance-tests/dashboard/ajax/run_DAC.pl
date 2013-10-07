eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_DAC.pl 2166 2012-05-01 16:30:28Z dpuranik $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the DAC
$the_DAC_options = "-ORBEndpoint iiop://192.168.2.2:30000 --name=SmokeTest -c Smoke_Test.conf -v --debug";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep(5);

# Start the test and execution manager
$the_TnE_options = "--dac-list=the_DACS.dat -ORBEndpoint iiop://192.168.2.2:50000 --name=SmokeTest --debug";
$the_TnE = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_tem", $the_TnE_options);
$the_TnE->Spawn ();

sleep (999999);

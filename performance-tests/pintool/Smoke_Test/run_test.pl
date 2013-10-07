eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2240 2013-08-13 18:13:43Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";
$PIN_ROOT = "$ENV{'PIN_ROOT'}";

# Start the DAC
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 --name=StandardDAC -c Smoke_Test.dac --database=StandardDAC.db -v --debug";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (15);

# Instruction counter
#$config = "Smoke_Test.instruction0.einode";
#$pintool = "$PIN_ROOT/source/tools/SimpleExamples/obj-ia32/icount.so";

# Address trace
$config = "Smoke_Test.instuction1_inst_ptr.einode";
$pintool = "$PIN_ROOT/source/tools/ManualExamples/obj-ia32/itrace.so";

# Commands
#$cmd = "find $OASIS_ROOT -name *.conf";
#$timeout = 5;

#$cmd = "ls";
#$timeout = 5;

$cmd = "grep -rli oasis $OASIS_ROOT";
$timeout = 7;

$oasis_options = "-t $OASIS_ROOT/oasis/tools/PINtool/libOASIS_PINtool.so \"-bc$config\" -- $cmd";
$pin_options = "-t $pintool -- $cmd";

$oasis = new PerlACE::Process ("$PIN_ROOT/pin", $oasis_options);
$pin = new PerlACE::Process ("$PIN_ROOT/pin", $pin_options);
for ($i=0; $i<20; $i++)
{
  # Run oasis PINtool
  $oasis->Spawn ();
  sleep ($timeout);
  $oasis->Kill ();
  $oasis->TimedWait (1);

  # Run native PINtool
  $pin->Spawn ();
  sleep ($timeout);
  $pin->Kill ();
  $pin->TimedWait (1);
}

# Kill the DAC process.
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

exit 0;

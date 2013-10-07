eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 2115 2012-01-13 13:57:53Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Start the DAC
$the_opts = "";
$the_Test = new PerlACE::Process ("OASIS_Vector_Software_Probe_Test", $the_opts);
$the_Test->Spawn ();

sleep (15);

# Kill the application
$the_Test->Kill ();
$the_Test->TimedWait (1);

exit 0;

eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_EINode.pl 2161 2012-04-30 18:20:47Z dpuranik $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

# Run the example.
$the_Example_options = "--debug -c Smoke_Test.einode --hertz=1";
$the_Example = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_mon", $the_Example_options);
$the_Example->Spawn ();

sleep (999999);

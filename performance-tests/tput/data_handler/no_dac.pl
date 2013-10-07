eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: no_dac.pl 2142 2012-03-26 18:02:24Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

my $output_file = 'no_dac.csv';

my %tests = ('0', 'byte_0.einode',
             '8', 'byte_8.einode',
             '16', 'byte_16.einode',
             '32', 'byte_32.einode',
             '64', 'byte_64.einode',
             '128', 'byte_128.einode',
             '256', 'byte_256.einode');

my @seconds_per_test = (2, 10, 60);

my $total_iterations = 5;

# Prepare output file
open (OUTPUT, ">$output_file");
print OUTPUT "Bytes,Duration,Events,TPUT\n";
close (OUTPUT);

# Iterations loop
for ($i = 1; $i <= $total_iterations; $i++)
{
  print "*** Start iteration $i ***\n";

  # Test durations loop
  foreach $test_duration (@seconds_per_test)
  {
    # Test type loop
    while (my ($bytes, $einode_config) = each (%tests))
    {
      print "*** Starting $bytes byte test for $test_duration seconds ***\n";

      open (OUTPUT, ">>$output_file");
      print OUTPUT "$bytes,$test_duration,";
      close (OUTPUT);

      $the_Example_options = "-c $einode_config -b $bytes -o $output_file";
      $the_Example = new PerlACE::Process ('OASIS_Data_Handler_Byte_Tput_Test', $the_Example_options);
      $the_Example->Spawn ();

      sleep ($test_duration);

      # Kill the application
      $the_Example->TerminateWaitKill (15);
    }
  }
}

exit 0;

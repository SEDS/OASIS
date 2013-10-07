eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: local_dac_tao_publisher.pl 2142 2012-03-26 18:02:24Z dfeiock $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$OASIS_ROOT = "$ENV{'OASIS_ROOT'}";

my $output_file = 'local_dac_tao_publisher.csv';

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

# Start the DAC
$the_DAC_options = "-ORBEndpoint iiop://localhost:20000 --name=StandardDAC -c tao_handler.dac --database=StandardDAC.db";
$the_DAC = new PerlACE::Process ("$OASIS_ROOT/bin/oasis_dac", $the_DAC_options);
$the_DAC->Spawn ();

sleep (5);

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

# Kill the DAC process.
$the_DAC->Kill ();
$the_DAC->TimedWait (1);

exit 0;

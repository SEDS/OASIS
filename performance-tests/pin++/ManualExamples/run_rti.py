#!/usr/bin/python3

# Times executions of pin++ vs native pin and outputs in a pivot table CSV

import time
import os
import argparse
import sys
import subprocess
import csv

#
# Parse args
#
def parse_args ():
  parser = argparse.ArgumentParser (description='Gathers performance metrics of pin++ vs native pin')

  parser.add_argument ('--outfile', default='results.csv', type=str, help='Output file. Defaults to results.csv')
  parser.add_argument ('--pinppdir', default=os.environ['OASIS_ROOT'] + '/examples/pintools', type=str, help='Pin++ pintool directory. Defaults to $OASIS_ROOT/examples/pintools')
  parser.add_argument ('--pindir', default=os.environ['PIN_ROOT'] + '/source/tools', type=str, help='Native pintool directory.  Defaults to $PIN_ROOT/source/tools')
  parser.add_argument ('--publisher', default=None, type=str, help='Full command to execute the publisher (including args)')
  parser.add_argument ('--subscriber', default=None, type=str, help='Full command to execute the subscriber (including args)')
  parser.add_argument ('--iterations', default=10, type=int, help='Number of iterations to time for each pintool')

  return parser.parse_args ()

#
# Find pintools
#
def find_pintools (path):
  pintools = []

  for root, dirs, files in os.walk (path):
    for file in files:
      if file.endswith ('.so') and (os.name == 'posix'):
        pintools.append (os.path.join (root, file))
      elif (os.name == 'nt') and file.endswith ('.dll'):
        pintools.append (os.path.join (root, file))
      elif (os.name == 'mac') and file.endswith ('.dylib'):
        pintools.append (os.path.join (root, file))

    for dir in dirs:
      pintools.extend (find_pintools (dir))

  return pintools

#
# Remove paths
#
def remove_paths (list):
  results = []
  for item in list:
    results.append (os.path.split (item)[-1])
  return results

#
# Match pintools
#
def match_pintools (native, pinpp):
  # Native format: [path]/inscount0.so
  # Pin++ format: [path]/libinscount0.so
  results = []

  # Full paths are in the provided lists, let's remove them
  pruned_native = remove_paths (native)
  pruned_pinpp = remove_paths (pinpp)

  # NOTE: This assumes there aren't two pintools with the same name in
  # different paths.
  for native_tool in pruned_native:
    search = 'lib' + native_tool
    if search in pruned_pinpp:
      # Assumes the pruned lists have matching indexes to the provided lists
      results.append ([native [pruned_native.index (native_tool)],
                       pinpp [pruned_pinpp.index (search)]])

  return results

#
# Run publisher
#
def run_pub (pintool, command):
  cmd = ' '.join ([os.path.join (os.environ['PIN_ROOT'], 'pin'),
                  '-t',
                  pintool,
                  '--',
                  command])

  # DEBUG: Check the command
  #print (repr (cmd))

  # Run the command
  # Had to use shell=True for trailing arguments (i.e. '1>/dev/null &2>1')
  return subprocess.Popen (cmd, shell=True, stdout=subprocess.PIPE)

#
# Run subscriber
#
def run_sub (pintool, command):
  # Build the command
  # Example: $PIN_ROOT/pin -t pintool.so -- ls
  cmd = ' '.join ([os.path.join (os.environ['PIN_ROOT'], 'pin'),
                  '-t',
                  pintool,
                  '--',
                  command])

  # DEBUG: Check the command
  #print (repr (cmd))

  # Run the command
  start = time.time ()
  # Had to use shell=True for trailing arguments (i.e. '1>/dev/null &2>1')
  subprocess.call (cmd, shell=True)
  end = time.time ()
  return end - start

#
# Main entry point for the application
#
def main ():
  # Parse the arguments
  args = parse_args ()

  # Check for pub and sub commands
  if (not args.publisher or not args.subscriber):
    print ("Error: Publisher or Subscriber commands not provided")
    sys.exit (1)

  # Find all the pintools which have been compiled in the pin directory
  print ('INFO: Finding native pintools in <%s>' % (args.pindir))
  native_pintools = find_pintools (args.pindir)

  # Find all the pintools which have been compiled in the pin++ directory
  print ('INFO: Finding pin++ pintools in <%s>' % (args.pinppdir))
  pinpp_pintools = find_pintools (args.pinppdir)

  # Match the pin++ pintools to the native pintools, since pintool names are different
  pintools = match_pintools (native_pintools, pinpp_pintools)
  if not pintools:
    print ('ERROR: No matching native and pin++ pintools found, are they compiled?')
    sys.exit (1)

  # Open the file and write the header
  outfile = open (args.outfile, 'w')
  writer = csv.writer (outfile)
  writer.writerow (['Pintool', 'Command', 'Iteration', 'Native', 'Pin++', 'Difference', 'Difference_Percent']) 

  # Execute the test
  for native, pinpp in pintools:
    for iteration in range (1, args.iterations + 1):
      tool_name = os.path.split (native)[-1]
      print ('INFO: Executing pintool <%s>, iteration <%s>'
             % (tool_name, iteration))

      # Run native
      pub = run_pub (native, args.publisher)
      native_time = run_sub (native, args.subscriber)
      print (repr (pub.communicate ()))

      # Run pinpp
      pub = run_pub (pinpp, args.publisher)
      pinpp_time = run_sub (pinpp, args.subscriber)
      print (repr (pub.communicate ()))

      # Write the results
      writer.writerow ([tool_name,
                        command,
                        iteration,
                        native_time,
                        pinpp_time,
                        pinpp_time - native_time,
                        pinpp_time * 100 / native_time - 100])
main ()

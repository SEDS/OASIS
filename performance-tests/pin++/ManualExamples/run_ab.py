#!/usr/bin/python3

# Uses Apache Benchmark (ab) to time executions of pin++ vs native pin

import time
import os
import argparse
import sys
import subprocess
import csv
import signal
import re

#
# Parse args
#
def parse_args ():
  parser = argparse.ArgumentParser (description='Gathers performance metrics of pin++ vs native pin')

  parser.add_argument ('--outfile', default='results.csv', type=str, help='Output file. Defaults to results.csv')
  parser.add_argument ('--pinppdir', default=os.environ['OASIS_ROOT'] + '/examples/pintools', type=str, help='Pin++ pintool directory. Defaults to $OASIS_ROOT/examples/pintools')
  parser.add_argument ('--pindir', default=os.environ['PIN_ROOT'] + '/source/tools', type=str, help='Native pintool directory.  Defaults to $PIN_ROOT/source/tools')
  parser.add_argument ('--apache_conf', default='/etc/apache2/apache2.conf', type=str, help='Full path to apache config.  Defaults to /etc/apache2/apache2.conf')
  parser.add_argument ('--url', default=None, type=str, help='URL to test with apache benchmark.')
  parser.add_argument ('--requests', default=[1, 10, 100, 1000, 10000, 100000], type=int, nargs='+', help='Space-separated list of the number of requests to test.')
  parser.add_argument ('--concurrency', default=[1, 10, 100, 1000], type =int, nargs='+', help='Space-separated list of the number of clients to test.')
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
# Start apache
#
def start_apache (apache_conf):
  # Runs apache in foreground
  # Example: /usr/sbin/apachectl -f apache_conf -DFOREGROUND
  path = os.path.abspath (os.path.dirname (apache_conf))
  cmd = 'apachectl -d . -f %s -e info -DFOREGROUND 1>/dev/null 2>&1' % (apache_conf)

  # Use setsid to put child processes into a process group so they will
  # all terminate at the same time
  return subprocess.Popen (cmd, cwd=path, shell=True, preexec_fn=os.setsid)

#
# Children pids
#
def children_pids (pid):
  proc = subprocess.Popen ('ps -o pid,ppid ax | grep "%d"' % pid, shell=True, stdout=subprocess.PIPE)
  pidppid = [x.split() for x in proc.communicate()[0].split("\n") if x]

  return list(int(p) for p, pp in pidppid if int(pp) == pid)

#
# Attach children
#
def attach_children (process, pintool):
  for child in children_pids (process.pid):
    print ('INFO: Attaching pin to child process <%s> of parent <%s>' % (child, process.pid))
    cmd = ' '.join ([os.path.join (os.environ['PIN_ROOT'], 'pin'),
                     '-pid',
                     '%s' % child,
                     '-t',
                     pintool])

    subprocess.call (cmd, shell=True)

#
# Run ab
#
def run_ab (url, concurrency, requests):
  # Build the command
  # Example: ab -c 10 -r 10 localhost/index.html
  cmd = ' '.join (['ab',
                   '-c',
                   '%s' % concurrency,
                   '-n',
                   '%s' % requests,
                   url])

  # DEBUG: Check the command
#  print (repr (cmd))

  # Run the command
  return subprocess.check_output (cmd, shell=True)

#
# Main entry point for the application
#
def main ():
  # Parse the arguments
  args = parse_args ()

  # Check for URL
  if (not args.url):
    print ("Error: No URL specified")
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
  writer.writerow (['Pintool', 'Concurrency', 'Requests', 'Iteration', 'Native', 'Pin++', 'Difference', 'Difference_Percent']) 

  # Compiled regex to get the average time per request across
  # all concurrent requests
  time_per_request = re.compile ('Time per request:\s+(\d+\.\d+) \[.*\] \(mean, across')

  # Execute the test
  for concurrency in args.concurrency:
    for requests in args.requests:
      if (concurrency > requests):
        continue

      for native, pinpp in pintools:
        for iteration in range (1, args.iterations + 1):
          tool_name = os.path.split (native)[-1]
          print ('INFO: Executing pintool <%s>, iteration <%s>'
                 % (tool_name, iteration))

          # Get native results
          process = start_apache (args.apache_conf)
          time.sleep (2)
          attach_children (process, native)
          native_output = run_ab (args.url, concurrency, requests)
          os.killpg (process.pid, signal.SIGTERM)
          time.sleep (2)

          # Get pin++ results
          process = start_apache (args.apache_conf)
          time.sleep (2)
          attach_children (process, pinpp)
          pinpp_output = run_ab (args.url, concurrency, requests)
          os.killpg (process.pid, signal.SIGTERM)
          time.sleep (2)

          # Find the average time per request
          native_time = float (time_per_request.search (native_output).group (1))
          pinpp_time = float (time_per_request.search (pinpp_output).group (1))

          # Write the results
          writer.writerow ([tool_name,
                            concurrency,
                            requests,
                            iteration,
                            native_time,
                            pinpp_time,
                            pinpp_time - native_time,
                            pinpp_time * 100 / native_time - 100])

main ()

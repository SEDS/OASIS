#!/usr/bin/env python

###############################################################################
#
# @file        run_test_all.py
#
# $Id: run_test_all.py 1891 2011-09-03 06:20:36Z hillj $
#
# @author      James H. Hill
#
###############################################################################

import getopt
import os
import sys
import signal
import subprocess

#
# interrupt_signal_handler
#
def interrupt_signal_handler (signal, frame):
  # Kill the current test process.
  p.kill ()

  # Exit the system gracefully.
  sys.exit (0)

#
# Utility function that executes the specified test script.
#
# @param[in]            uri
#
def run_test_script (dir):
    cmd = ["perl", "--", "run_test.pl"]

    print "*** INFO: executing test script in", dir
    global p
    p = subprocess.Popen (cmd, cwd=dir)

    # Wait for the process to complete. We should set a timeout
    # value here so we do not deadlock on a single test forever!
    p.wait ()

#
# Main entry point for the application.
#
def main ():
    try:
      # Setup the signal handlers.
      signal.signal (signal.SIGINT, interrupt_signal_handler)

      # Parse the command-line arguments.
      opts, args = getopt.getopt (sys.argv[1:],
                                  "p:",
                                  ["path="])

      path = "."

      for o, a in opts:
        if o == "--prefix":
          prefix = a
        elif o in ("-p", "--path"):
          path = a;
        else:
          assert False, "unhandled option"

      for root, dirs, files in os.walk (path):
        if "run_test.pl" in files:
          run_test_script (root)

        if '.svn' in dirs:
          dirs.remove ('.svn')

    except getopt.error as ex:
        print ("Error: " + ex.args[0])
        sys.exit (1)

#
# Invoke the main entry point, if applicable.
#
if __name__ == "__main__":
    main ()

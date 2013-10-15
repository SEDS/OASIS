This script looks in the pinppdir and pindir paths and 
identifies all libraries.  Libraries are then matched via 
filename (i.e. inscount.so matches with libinscount.so).  
Only the pintools which have matching native and pin++ 
implementations are tested.

Basic Usage
------------

Use the script as follows:

    %> python3 run_test.py [arguments]
    
Example:    

    %> python3 run_test.py --binary ls

### Supported Arguments

The script supports the following arguments:

* outfile - Result output filename
* pinppdir - Pin++ pintool directory
* pindir - Native pintool directory
* binary - The binary to use for the test
* binary\_file - File with one binary per line to test
* iterations - Number of times to test the pintools

### Output Format

The output file is a CSV format.  Each row contains:

* pintool - Name of the pintool
* command - The binary used for the test
* iteration - The iteration number
* native - Execution time of the native pintool
* pin++ - Execution time of the pin++ pintool
* difference - Time difference (pin++ - native)
* difference\_percent - difference as a percentage

Running in Emulab
------------------

There is an experiment named 'pinpp' in the OASIS project.  
This experiment can be used for using this script. Most 
of the configuration has been automated.  After swapping 
the experiment in, do the following:

    %> sudo bash /proj/OASIS/exp/pinpp/bin/install_packages.sh
    %> sudo chown -R [userid]:OASIS /opt
    %> . /proj/OASIS/exp/pinpp/bin/deploy.sh

At this time, all dependencies for PIN should be successfully 
installed.  You will need to build the native pintools manually.

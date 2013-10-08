OASIS
=====

Open-source Architecture for Software Instrumentation of Systems

Building from Sources
---------------------

1. Install [Python3](http://www.activestate.com/activepython/downloads) on your machine. (Python 2.x will not work)
1. Install [Perl](http://www.activestate.com/activeperl) on your machine.
1. Install [GIT] (http://git-scm.com/downloads)
1. Checkout our custom Python3 build scripts from the Git repo.

    %> git clone git@github.iu.edu/SEDS/bczar.git`

1. Lastly, execute the **download** and **build** commands using the build scripts 
   from the **developer command prompt**

    %> python3 bczar.py --include=OASIS --prefix=[target directory] [command]`

The script will **download** all required source files, **build** them, 
and install them in their correct location within the **target directory**. 
The script will also generate a file named **configure.[bat|sh]**, which needs 
to be executed each time you start a new console shell. This script file 
will initialize the correct environment variables.

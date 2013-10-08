OASIS
=====

The _Open-source Architecture for Software Instrumentation of Systems (OASIS)_ 
is a R&D framework for exploring and understanding the challenges 
associated with instrumenting software systems in real-time.

Frameworks & Technologies
-------------------------

The following frameworks and technologies are contained within
the OASIS project:

* Pin ++

Building from Sources
---------------------

We assume you have the following already installed on your machine:

* [Python3](http://www.activestate.com/activepython/downloads) (Python 2.x will not work)
* [Perl](http://www.activestate.com/activeperl)
* [GIT] (http://git-scm.com/downloads)

Checkout our custom Python3 build scripts from the Git repo:

    %> git clone git@github.iu.edu/SEDS/bczar.git

Execute the **download** and **build** commands using the build scripts 
from the **developer command prompt**:

    %> python3 bczar.py --include=OASIS --prefix=[target directory] download
    %> python3 bczar.py --include=OASIS --prefix=[target directory] build

The script will **download** all required source files, **build** them, 
and install them in their correct location within the **target directory**. 
The script will also generate a file named **configure.[bat|sh]**, which needs 
to be executed each time you start a new console shell. This script file 
will initialize the correct environment variables.

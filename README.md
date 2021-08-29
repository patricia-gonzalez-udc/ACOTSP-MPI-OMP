# ACOTSP-MPI-OMP

This software package provides a hybrid parallel implementation, 
distributed multi-colony with shared-memory parallelization in each colony, using 
MPI for cooperation between colonies and OpenMP to parallelize “for loops” 
within each colony. The software tries to provide an efficient 
parallel implementation  while at the same time aiming for readability 
and understandability of the code.

This software package was developed on the basis of the 
software package ACOTSP by Thomas Stuetzle, that can be
found in: www.aco-metaheuristic.org/aco-code/public-software.html 

This software package is freely available subject to the 
GNU General Public Licence.

If you use ACOTSP-MPI-OMP in your research, I would appreciate a 
citation in your publication(s). 

# CONTENTS

The main control routines, main:

acotsp.c

Procedures to implement the ants behaviour:

ants.c

ants.h

Procedures related to MPI communications:

parallel.c

parallel.h

Input / output / statistics routines:

InOut.c

InOut.h

Procedures specific to the TSP:

TSP.c

TSP.h

Local search procedures:

ls.c

ls.h

Additional useful / helping procedure:

utilities.c

utilities.h

Command line parser:

parse.c

parse.h

Time measurement:

timer.h 

dos_timer.c  : default timer implementation based on clock()

unix_timer.c : in case you want to use rusage() instead, edit the
               Makefile to use this one or compile with 'make TIMER=unix'

An example of makefile:

Makefile 

  This makefile assumes the use of intel compilers
  and libraries for C and MPI. The code is written 
  in ANSI C and MPI 2.0. Hence, the code should be
  reasonable portable. It was also tested with 
  gcc compilers and OpenMPI library. You have to 
  adapt the makefile for your own testbed. 

Instances: lin318.tsp and pr2392.tsp. 

  Other TSP instances are available from TSPLIB
  (http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/index.html),
  the webpage for the 8th DIMACS Implementation Challenge on the TSP
  (http://dimacs.rutgers.edu/Challenges/TSP/) or the webpage on "The
  Traveling Salesman Problem"
  (http://www.math.uwaterloo.ca/tsp/index.html)



# USAGE

Given the large number of ACO algorithms, also the number of command
line options is relatively large.

The default parameter settings are such, that MAX-MIN Ant System will
be run using a 3-opt local search, using alpha = 1, beta = 2, rho =
0.5 for a maximum of 10 seconds per each trial for 10 independent
trials.

The executable 'acotsp' provides the following command line options
(given are the short and the long options):

-r, --tries          # number of independent trials

-s, --tours          # number of steps in each trial

-t, --time           # maximum time for each trial

    --seed           # seed for the random number generator 
    
-i, --tsplibfile     f inputfile (TSPLIB format necessary)

-o, --optimum        # stop if tour better or equal optimum is found

-m, --ants           # number of ants

-g, --nnants         # nearest neighbours in tour construction

-a, --alpha          # alpha (influence of pheromone trails)

-b, --beta           # beta (influence of heuristic information)

-e, --rho            # rho: pheromone trail evaporation

-q, --q0             # q_0: prob. of best choice in tour construction

-c, --elitistants    # number of elitist ants

-f, --rasranks       # number of ranks in rank-based Ant System

-k, --nnls           # No. of nearest neighbors for local search

-l, --localsearch    0: no local search   1: 2-opt   2: 2.5-opt   3: 3-opt

-d, --dlb            1 use don't look bits in local search

-u, --as               apply basic Ant System

-v, --eas              apply elitist Ant System

-w, --ras              apply rank-based version of Ant System

-x, --mmas             apply MAX-MIN ant system

-y, --bwas             apply best-worst ant system

-h, --help             display the help text and exit


Options -u --as, -v --eas, -w --ras, -x --mmas, -y --bwas, 
-h, --help don't need arguments, while all the others do.  

A Mandatory option is only the option "-i, --tsplibfile". Here, mandatory
means that without specifying this option, the program won't work,
since there is no input file. 

All the other options take some default values. 
The default settings imply that as default MAX-MIN Ant System is run
using a 3-opt local search procedure. Please note that these default
values do not really make sense for some of the algorithms (e.g.,
typically an evaporation of 0.2 is recommended vor MAX-MIN Ant
System); that is, for some of the algorithms the default parameter
settings lead to poor performance. Hence, when you
use any of the ACO algorithms, make sure you set the appropriate
parameter values. Typically, one may want to adjust the parameters

-t, --time

-o, --optimum

-m, --ants

-b, --beta

-e, --rho 

-q, --q0

-l, --localsearch

Note that only one option among -u --as, -v --eas, -w --ras,
-x --mmas, -y --bwas, is to be specified.

Examples for running an experiments are:

./acotsp -i lin318.tsp -v -t 60. -o 42029 -m 50 -b 5


# OUTPUT

Every experiment produces two main files. These files are: 

summary.tsplibfilename.threads.numberThreads.mpi.numberColonies

cc.tsplibfilename.threads.numberThreads.mpi.numberColonies

where tsplibfilename is the instance identifier of the instance under
solution, numberThreads is the number of threads used and numberColonies
the number of colonies for the experiment.

The file “summary.tsplibfilename.threads.numberThreads.mpi.numberColonies” 
Contains a summary of the main information on the development of the
solution. For each trial information is placed in one line of this file,
reporting the best solution found, the iteration where it has been found, 
the branching factor, the time where the best solution has been found, 
the total time of the experiment, and the colony that has found the best solution.

The file “cc.tsplibfilename.threads.numberThreads.mpi.numberColonies” 
Contains information to draw the convergence curves. Each section for a trial 
starts with

begin try <trial_number> …

then, each time the algorithm finds a new best solution a line with the pair
<best-solution-found>  <time>
is added.


Additionally, the following three files can also be produced (see commented lines
in the “InOut.c” file).

best.tsplibfilename.threads.numberThreads.mpi.Colony
  
cmp.tsplibfilename.threads.numberThreads.mpi.Colony
  
stat.tsplibfilename.threads.numberThreads.mpi.Colony

These files provide more information for each specific colony 
(one file per colony) in the experiment.

The most important of these is the file "cmp.tsplibfilename". This
file starts with a specification of the parameter settings used to run
the experiment. The section with the comprehensive experimental data
starts with

begin problem tsplibfilename

Next the random number seed for the next trial is given

Then, for each trial statistical information on the development of the
best-so-far solution is given. Each section for a trial starts with

begin try <trial_number>

Then, each time the algorithm finds a new best solution a line 

best <number>	 iteration <number>	 tours <number>	 time <number>

is added, where "best" is the tour length of the best-so-far solution;
iteration is the iteration number in which this solution is found;
tours is the number of solutions constructed so far (typically this is
simple iteration X n_ants); and time is the time at which a new
best-so-far solution is found

Each trial is ended by 

end try <trial_number>

Once all trials are run the line 

end problem tsplibfilename

is added to end the file. 

The file  best.tsplibfilename

collects the information about parameter settings, the best solution
found in each trial, and some additional statistical information.

The file stat.tsplibfilename 

may be used for the output of statistical information on a trial as
generated by the procedure population_statistics(); in InOut.c.

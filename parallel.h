/*
 
  AAAA    CCCC   OOOO   TTTTTT   SSSSS  PPPPP
 AA  AA  CC     OO  OO    TT    SS      PP  PP
 AAAAAA  CC     OO  OO    TT     SSSS   PPPPP
 AA  AA  CC     OO  OO    TT        SS  PP
 AA  AA   CCCC   OOOO     TT    SSSSS   PP
 
 
 MM   MM  PPPPP   IIIIII
 MMMMMMM  PP  PP    II
 MM M MM  PPPPP     II
 MM   MM  PP        II
 MM   MM  PP      IIIIII
 
 
  OOOO    MM   MM  PPPPP
 OO  OO   MMMMMMM  PP  PP
 OO  OO   MM M MM  PPPPP
 OO  OO   MM   MM  PP
  OOOO    MM   MM  PP
 
 
 
 ######################################################
 ##########    MPI+OMP PARALLEL              ##########
 ##########    ACO algorithms for the TSP    ##########
 ######################################################
 
 */


extern MPI_Request request[50][100];
extern MPI_Request Prequest;
extern MPI_Request Rrequest;
extern MPI_Request SPrequest;
extern MPI_Request SRrequest;
extern MPI_Request Srequest;
extern MPI_Status status;
extern MPI_Status Sstatus;
extern MPI_Errhandler errh;
extern int mpi_id;
extern int NPROC;
extern int stopColonies;

void parallel_init(void);

void sendBestSolutionToColonies(void);

void startCommColoniesTour(void);

void listenTours(void);

void foreign_solution_update_pheromone (long int *ft);

void foreign_solution_update_pheromone_weighted(long int *ft, long int w);

void write_mpi_report();

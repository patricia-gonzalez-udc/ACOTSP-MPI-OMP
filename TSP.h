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

#define RRR            6378.388
#ifndef PI             /* as in stroustrup */
#define PI             3.14159265358979323846
#endif

struct point {
  double x;
  double y;
};

struct problem{
  char          name[LINE_BUF_LEN];      	 /* instance name */
  char          edge_weight_type[LINE_BUF_LEN];  /* selfexplanatory */
  long int      optimum;                /* optimal tour length if known, otherwise a bound */
  long int      n;                      /* number of cities */
  long int      n_near;                 /* number of nearest neighbors */
  struct point  *nodeptr;               /* array of structs containing coordinates of nodes */
  long int      **distance;	        /* distance matrix: distance[i][j] gives distance 
					   between city i und j */
  long int      **nn_list;              /* nearest neighbor list; contains for each node i a
                                           sorted list of n_near nearest neighbors */
};

extern struct problem instance;

long int n;          /* number of cities in the instance to be solved */

long int  (*distance)(long int, long int);  /* pointer to function returning distance */

long int round_distance (long int i, long int j);

long int ceil_distance (long int i, long int j);

long int geo_distance (long int i, long int j);

long int att_distance (long int i, long int j);

long int compute_tour_length( long int *t );

long int **compute_distances(void);

long int ** compute_nn_lists ( void );

int tsp_check_tour(const long int *t);

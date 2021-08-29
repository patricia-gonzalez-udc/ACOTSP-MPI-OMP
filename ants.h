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


#define HEURISTIC(m,n)     (1.0 / ((double) instance.distance[m][n] + 0.1))
/* add a small constant to avoid division by zero if a distance is 
zero */

#define EPSILON            0.00000000000000000000000000000001

#define MAX_ANTS       3000    /* max no. of ants */
#define MAX_NEIGHBOURS 512     /* max. no. of nearest neighbours in candidate set */

/* Note that *tour needs to be allocated for length n+1 since the first city of 
a tour (at position 0) is repeated at position n. This is done to make the 
computation of the tour length easier 
*/
typedef struct {
  long int  *tour;
  char      *visited;
  long int  tour_length;
} ant_struct;

extern ant_struct *ant;      /* this (array of) struct will hold the colony */
extern ant_struct *best_so_far_ant;   /* struct that contains the best-so-far ant */
extern ant_struct *restart_best_ant;  /* struct that contains the restart-best ant */

extern long int *best_global_tour; /* best tour from foreign colonies */
extern long int **global_tour; /* recv tour from foreign colonies */
extern long int best_global_tour_length;

extern double   **pheromone; /* pheromone matrix, one entry for each arc */
extern double   **total;     /* combination of pheromone times heuristic information */

extern double   *prob_of_selection;


extern long int n_ants;      /* number of ants */
extern long int nn_ants;     /* length of nearest neighbor lists for the ants'
                                solution construction */

extern double rho;           /* parameter for evaporation */
extern double alpha;         /* importance of trail */
extern double beta;          /* importance of heuristic evaluate */
extern double q_0;           /* probability of best choice in tour construction */


extern long int as_flag;     /* = 1, run ant system */
extern long int eas_flag;    /* = 1, run elitist ant system */
extern long int ras_flag;    /* = 1, run rank-based version of ant system */
extern long int mmas_flag;   /* = 1, run MAX-MIN ant system */
extern long int bwas_flag;   /* = 1, run best-worst ant system */

extern long int elitist_ants;    /* additional parameter for elitist ant system, 
				    it defines the number of elitist ants */

extern long int ras_ranks;       /* additional parameter for rank-based version of ant
				    system */

extern double   trail_max;       /* maximum pheromone trail in MMAS */
extern double   trail_min;       /* minimum pheromone trail in MMAS */
extern long int u_gb;            /* every u_gb iterations update with best-so-far ant;
				    parameter used by MMAS for scheduling best-so-far update
				 */

extern double   trail_0;         /* initial pheromone trail level in BWAS */

/* Pheromone manipulation etc. */

void init_pheromone_trails ( double initial_trail );

void evaporation ( void );

void evaporation_nn_list ( void );

void global_update_pheromone ( ant_struct *a );

void global_update_pheromone_weighted ( ant_struct *a, long int weight );

void compute_total_information( void );

void compute_nn_list_total_information( void );

/* Ants' solution construction */

void ant_empty_memory( ant_struct *a );

void place_ant( ant_struct *a , long int phase );

void choose_best_next( ant_struct *a, long int phase );

void neighbour_choose_best_next( ant_struct *a, long int phase );

void choose_closest_next( ant_struct *a, long int phase );

void neighbour_choose_and_move_to_next( ant_struct *a , long int phase );

/* Auxiliary procedures related to ants */

long int find_best ( void );

long int find_worst( void );

void copy_from_to(ant_struct *a1, ant_struct *a2);

void allocate_ants ( void );

long int nn_tour( void );

long int distance_between_ants( ant_struct *a1, ant_struct *a2);

/* Procedures specific to MAX-MIN Ant System */

void mmas_evaporation_nn_list( void );

void check_nn_list_pheromone_trail_limits( void );

void check_pheromone_trail_limits( void );

/* Procedures specific to Best Worst Ant System */

void bwas_worst_ant_update( ant_struct *a1, ant_struct *a2);

void bwas_pheromone_mutation( void );

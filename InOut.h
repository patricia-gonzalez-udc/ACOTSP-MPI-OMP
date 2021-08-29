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

#define PROG_ID_STR      "\nACO algorithms for the TSP, v1.03\n"
#define CALL_SYNTAX_STR  "call syntax:  acotsp <param-list>\n"

#define LINE_BUF_LEN     255

struct point * read_etsp(const char *tsp_file_name);

extern long int *best_in_try;
extern long int *best_found_at;
extern double   *time_best_found;
extern double   *time_total_run;   

extern long int n_try;        /* number of try */
extern long int n_tours;      /* number of constructed tours */
extern long int iteration;    /* iteration counter */
extern long int restart_iteration;    /* iteration counter */
extern double   restart_time; /* remember when restart was done if any */

extern long int max_tries;    /* maximum number of independent tries */
extern long int max_tours;    /* maximum number of tour constructions in one try */
extern long int max_iters;    /* maximum number of iterations in one try */

extern double   lambda;       /* Parameter to determine branching factor */
extern double   branch_fac;   /* If branching factor < branch_fac => update trails */

extern double   max_time;     /* maximal allowed run time of a try  */
extern double   time_used;    /* time used until some given event */
extern double   time_passed;  /* time passed until some moment*/
extern long int optimal;      /* optimal solution value or bound to find */

extern double mean_ants;      /* average tour length */
extern double stddev_ants;    /* stddev of tour lengths */
extern double branching_factor; /* average node branching factor when searching */
extern double found_branching;  /* branching factor when best solution is found */

extern long int found_best;         /* iteration in which best solution is found */
extern long int restart_found_best; /* iteration in which restart-best solution is found */

extern FILE *cc_report, *summary, *parallel, *report, *comp_report, *stat_report;

extern char name_buf[LINE_BUF_LEN];
extern int  opt;
extern long int quiet_flag;

void write_report( void );

void print_default_parameters();

void set_default_as_parameters(void);
void set_default_eas_parameters(void);
void set_default_ras_parameters(void);
void set_default_mmas_parameters(void);
void set_default_bwas_parameters(void);
void set_default_ls_parameters(void);

void set_default_parameters();

void init_try( long int ntry );

void output_solution( void );

void exit_try( long int ntry );

void exit_program( void );

void init_program( long int argc, char *argv[] );

void printDist(void);

void printHeur(void);

void printTrail(void);

void printTotal(void);

void printProbabilities(void);

void printTour( long int *t );

void printTourFile( long int *t );

void checkTour( long int *t );

void population_statistics ( void );

double node_branching(double l);

void write_params ( void );

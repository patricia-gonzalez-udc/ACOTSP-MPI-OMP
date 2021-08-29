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


#define INFTY                 LONG_MAX
#define MAXIMUM_NO_TRIES      100

#define TRUE  1
#define FALSE 0

/* general macros */

#define MAX(x,y)        ((x)>=(y)?(x):(y))
#define MIN(x,y)        ((x)<=(y)?(x):(y))

#define DEBUG( x )

#define TRACE( x )

/* constants for a random number generator, for details see numerical recipes in C */

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

extern long int seed;

double mean ( long int *values, long int max);

double meanr ( double *values, long int max );

double std_deviation ( long int *values, long int i, double mean );

double std_deviationr ( double *values, long int i, double mean );

long int best_of_vector ( long int *values, long int i );

long int worst_of_vector ( long int *values, long int i );

void swap ( long int v[], long int i, long int j );

void sort ( long int v[], long int left, long int right );

double quantil ( long int vector[], double q, long int numbers );

void swap2(long int v[], long int v2[], long int i, long int j);

void sort2(long int v[], long int v2[], long int left, long int right);

double ran01 ( long *idum );

long int random_number ( long *idum );

long int ** generate_int_matrix( long int n, long int m);

double ** generate_double_matrix( long int n, long int m);

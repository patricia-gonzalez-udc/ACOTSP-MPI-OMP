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

        Version: 1.0
        File:    TSP.c
        Purpose: TSP related procedures
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

#include "InOut.h"
#include "TSP.h"
#include "ants.h"
#include "ls.h"
#include "utilities.h"

#define M_PI 3.14159265358979323846264

long int n;          /* number of cities in the instance to be solved */

struct problem instance;

static double dtrunc (double x)
{
    int k;

    k = (int) x;
    x = (double) k;
    return x;
}

long int  (*distance)(long int, long int);  /* function pointer */

/*    
      FUNCTION: the following four functions implement different ways of 
                computing distances for TSPLIB instances
      INPUT:    two node indices
      OUTPUT:   distance between the two nodes
*/

long int round_distance (long int i, long int j) 
/*    
      FUNCTION: compute Euclidean distances between two nodes rounded to next 
                integer for TSPLIB instances
      INPUT:    two node indices
      OUTPUT:   distance between the two nodes
      COMMENTS: for the definition of how to compute this distance see TSPLIB
*/
{
    double xd = instance.nodeptr[i].x - instance.nodeptr[j].x;
    double yd = instance.nodeptr[i].y - instance.nodeptr[j].y;
    double r  = sqrt(xd*xd + yd*yd) + 0.5;

    return (long int) r;
}

long int ceil_distance (long int i, long int j) 
/*    
      FUNCTION: compute ceiling distance between two nodes rounded to next 
                integer for TSPLIB instances
      INPUT:    two node indices
      OUTPUT:   distance between the two nodes
      COMMENTS: for the definition of how to compute this distance see TSPLIB
*/
{
    double xd = instance.nodeptr[i].x - instance.nodeptr[j].x;
    double yd = instance.nodeptr[i].y - instance.nodeptr[j].y;
    double r  = sqrt(xd*xd + yd*yd);

    return (long int)(ceil (r));
}

long int geo_distance (long int i, long int j) 
/*    
      FUNCTION: compute geometric distance between two nodes rounded to next 
                integer for TSPLIB instances
      INPUT:    two node indices
      OUTPUT:   distance between the two nodes
      COMMENTS: adapted from concorde code
                for the definition of how to compute this distance see TSPLIB
*/
{
    double deg, min;
    double lati, latj, longi, longj;
    double q1, q2, q3;
    long int dd;
    double x1 = instance.nodeptr[i].x, x2 = instance.nodeptr[j].x, 
	y1 = instance.nodeptr[i].y, y2 = instance.nodeptr[j].y;

    deg = dtrunc (x1);
    min = x1 - deg;
    lati = M_PI * (deg + 5.0 * min / 3.0) / 180.0;
    deg = dtrunc (x2);
    min = x2 - deg;
    latj = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

    deg = dtrunc (y1);
    min = y1 - deg;
    longi = M_PI * (deg + 5.0 * min / 3.0) / 180.0;
    deg = dtrunc (y2);
    min = y2 - deg;
    longj = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

    q1 = cos (longi - longj);
    q2 = cos (lati - latj);
    q3 = cos (lati + latj);
    dd = (int) (6378.388 * acos (0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
    return dd;

}

long int att_distance (long int i, long int j) 
/*    
      FUNCTION: compute ATT distance between two nodes rounded to next 
                integer for TSPLIB instances
      INPUT:    two node indices
      OUTPUT:   distance between the two nodes
      COMMENTS: for the definition of how to compute this distance see TSPLIB
*/
{
    double xd = instance.nodeptr[i].x - instance.nodeptr[j].x;
    double yd = instance.nodeptr[i].y - instance.nodeptr[j].y;
    double rij = sqrt ((xd * xd + yd * yd) / 10.0);
    double tij = dtrunc (rij);
    long int dij;

    if (tij < rij)
        dij = (int) tij + 1;
    else
        dij = (int) tij;
    return dij;
}



long int ** compute_distances(void)
/*    
      FUNCTION: computes the matrix of all intercity distances
      INPUT:    none
      OUTPUT:   pointer to distance matrix, has to be freed when program stops
*/
{
    long int     i, j;
    long int     **matrix;

    if((matrix = malloc(sizeof(long int) * n * n +
			sizeof(long int *) * n	 )) == NULL){
	fprintf(stderr,"Out of memory, exit.");
	exit(1);
    }
    for ( i = 0 ; i < n ; i++ ) {
	matrix[i] = (long int *)(matrix + n) + i*n;
	for ( j = 0  ; j < n ; j++ ) {
	    matrix[i][j] = distance(i, j);
	}
    }
    return matrix;
}



long int ** compute_nn_lists( void )
/*    
      FUNCTION: computes nearest neighbor lists of depth nn for each city
      INPUT:    none
      OUTPUT:   pointer to the nearest neighbor lists
*/
{
    long int i, node, nn;
    long int *distance_vector;
    long int *help_vector;
    long int **m_nnear;
 
    TRACE ( printf("\n computing nearest neighbor lists, "); )

    nn = MAX(nn_ls,nn_ants);
    if ( nn >= n ) 
	nn = n - 1;
    DEBUG ( assert( n > nn ); )
    
    TRACE ( printf("nn = %ld ... \n",nn); ) 

    if((m_nnear = malloc(sizeof(long int) * n * nn
			     + n * sizeof(long int *))) == NULL){
	exit(EXIT_FAILURE);
    }

    {
    distance_vector = calloc(n, sizeof(long int));
    help_vector = calloc(n, sizeof(long int));

    for ( node = 0 ; node < n ; node++ ) {  /* compute cnd-sets for all node */
	m_nnear[node] = (long int *)(m_nnear + n) + node * nn;

	for ( i = 0 ; i < n ; i++ ) {  /* Copy distances from nodes to the others */
	    distance_vector[i] = instance.distance[node][i];
	    help_vector[i] = i;
	}
	distance_vector[node] = LONG_MAX;  /* city is not nearest neighbour */
	sort2(distance_vector, help_vector, 0, n-1);
	for ( i = 0 ; i < nn ; i++ ) {
	    m_nnear[node][i] = help_vector[i];
	}
    }
    free(distance_vector);
    free(help_vector);
    }
    
    TRACE ( printf("\n    .. done\n"); )
    return m_nnear;
}



long int compute_tour_length( long int *t ) 
/*    
      FUNCTION: compute the tour length of tour t
      INPUT:    pointer to tour t
      OUTPUT:   tour length of tour t
*/
{
    int      i;
    long int tour_length = 0;
  
    for ( i = 0 ; i < n ; i++ ) {
	tour_length += instance.distance[t[i]][t[i+1]];
    }
    return tour_length;
}


int tsp_check_tour(const long int *t)
{
    int i;
    int * used;
    const int size = n;

    used = calloc (size, sizeof(int));

    if (t == NULL) {
        fprintf (stderr,"\n%s:error: permutation is not initialized!", __FUNCTION__);
        exit(1);
    }

    for (i = 0; i < size; i++) {
        if (used[t[i]]) {
            fprintf(stderr,"\n%s:error: solution vector has two times the value %ld (last position: %d)", __FUNCTION__, t[i], i);
            goto error;
        }
        else
            used[t[i]] = TRUE;
    }

    for (i = 0; i < size; i++) {
        if (!used[i]) {
            fprintf(stderr,"\n%s:error: vector position %d not occupied", __FUNCTION__, i);
            goto error;
        }
    }

    if (t[0] != t[size]) {
        fprintf(stderr,"\n%s:error: permutation is not a closed tour.", __FUNCTION__);
        goto error;
    }
    free (used);
    return TRUE;

error:
    fprintf(stderr,"\n%s:error: solution_vector:", __FUNCTION__);
    for (i = 0; i < size; i++)
        fprintf(stderr, " %ld", t[i]);
    fprintf(stderr,"\n");
    free(used);
    return FALSE;
}

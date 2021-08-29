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


typedef enum type_timer {REAL, VIRTUAL} TIMER_TYPE;

void start_timers(void);
double elapsed_time(TIMER_TYPE type);

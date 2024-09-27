#include "drandom.h"

static long MULTIPLIER  = 1366;
static long ADDEND      = 150889;
static long PMOD        = 714025;

long random_last = 0;
double random_low, random_hi;

#pragma omp threadprivate(random_last)

double drandom() {
    long random_next;
    double ret_val;
    random_next = (MULTIPLIER  * random_last + ADDEND)% PMOD;
    random_last = random_next;
    ret_val = ((double)random_next/(double)PMOD)*(random_hi-random_low)+random_low;
    return ret_val;
}

void seed(double low_in, double hi_in) {
   if(low_in < hi_in) { 
      random_low = low_in;
      random_hi  = hi_in;
   } else {
      random_low = hi_in;
      random_hi  = low_in;
   }
   random_last = PMOD/ADDEND;  // just pick something
}


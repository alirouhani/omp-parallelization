#include <iostream>
#include <omp.h>

static long num_steps = 1000000000;
double step;
#define PAD 8
#define NUM_THREADS 16
int main (){
    int i, nthreads;
    double sum[NUM_THREADS][PAD];
    double pi, start_time, run_time;
    step = 1.0/(double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;
        for (i = id, sum[id][0] = 0.0; i < num_steps; i=i+nthrds) {
            x = (i+0.5)*step;
            sum[id][0] += 4.0/(1.0+x*x);
        }
    }
    run_time = omp_get_wtime() - start_time;
    for (i = 0, pi = 0.0; i < nthreads; ++i) pi += sum[i][0]*step;
    printf("pi: %f\n",pi);
    printf("run time: %f",run_time);
    return 0;
}

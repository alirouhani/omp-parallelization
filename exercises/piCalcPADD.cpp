#include <iostream>
#include <omp.h>

static long num_steps = 2000000000;
double step;
#define PAD 8
#define NUM_THREADS 4
int main (){
    double sum[NUM_THREADS][PAD];
    double pi, start_time, run_time;
    step = 1.0/(double) num_steps;
    int i, nthreads = NUM_THREADS;
    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        double x;
        int i, id = omp_get_thread_num();
        for (i = id*(num_steps/nthreads); i < (id+1)*(num_steps/nthreads); ++i) {
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

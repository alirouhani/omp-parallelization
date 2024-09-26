#include <iostream>
#include <omp.h>

static long num_steps = 2000000000;
double step;
#define NUM_THREADS 4
int main (){
    double sum = 0.0;
    double pi, start_time, run_time;
    step = 1.0/(double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    int nthreads = NUM_THREADS;
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        double x, sumT = 0.0;
        int id = omp_get_thread_num();
        for (int i = id*(num_steps/nthreads); i < (id+1)*(num_steps/nthreads); ++i) {
            x = (i+0.5)*step;
            sumT += 4.0/(1.0+x*x);
        }
        sum += sumT;
    }
    run_time = omp_get_wtime() - start_time;
    pi = step*sum;
    printf("pi: %f\n",pi);
    printf("run time: %f",run_time);
    return 0;
}

#include <iostream>
#include <omp.h>

static long num_steps = 2000000000;
double step;
#define NUM_THREADS 4
int main (){
    double pi, x, sum, start_time, run_time;
    step = 1.0/(double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    #pragma omp parallel for private(x) reduction (+:sum)
    for (int i = 0; i < num_steps; ++i) {
        x = (i+0.5)*step;
        sum += 4.0/(1.0+x*x);
    }
    pi += step*sum;
    run_time = omp_get_wtime() - start_time;
    printf("pi: %f\n",pi);
    printf("run time: %f",run_time);
    return 0;
}

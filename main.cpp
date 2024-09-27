#include <iostream>
#include <omp.h>
#include <vector>

#define NUM_THREADS 8
#define N        32
#define SEED       2531
#define RAND_MULT  1366
#define RAND_ADD   150889
#define RAND_MOD   714025
int randy = SEED;

/* function to fill an array with random numbers */
void fill_rand(int length, std::vector<double*> a);
/* function to sum the elements of an array */
double Sum_array(int length, std::vector<double*> a);

int main() {
    double sum, runtime;
    std::vector<double*> A(N);
    int flag = 0;
    omp_set_num_threads(NUM_THREADS);

    // Allocate memory for each element
    for (int i = 0; i < N; ++i) {
        A[i] = new double;  // Allocate a new double for each element
    }

    runtime = omp_get_wtime();
#pragma omp parallel
    {
    fill_rand(N, A);        // Producer: fill an array of data
    sum = Sum_array(N, A);  // Consumer: sum the array
    }
    runtime = omp_get_wtime() - runtime;
    std::cout << "In " << runtime << " seconds, The sum is " << sum << std::endl;
}

void fill_rand(int length, std::vector<double*> a) {
    for (int i = 0; i < length; ++i) {
        randy = (RAND_MULT * randy + RAND_ADD) % RAND_MOD;
        *(a[i]) = ((double) randy)/((double) RAND_MOD);
    }   
}

double Sum_array(int length, std::vector<double*> a) {
    double sum = 0.0;
    for (int i = 0; i < length; ++i) sum += *(a[i]);  
    return sum; 
}


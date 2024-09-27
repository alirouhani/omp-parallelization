#include <omp.h>
#include <iostream>
#include <vector>

#define NUM_THREADS 16
#define N 12
#define FS 38 

struct node {
    int data;
    int fibdata;
    node* next;
};

int fib(int n);
void processwork(node* p);
std::vector<node*> init_list();
void display(std::string text) {std::cout << text << std::endl;}

int main() {
    int i = 0;
    double start, end;
    omp_set_num_threads(NUM_THREADS);

    printf("Process linked list\n");
    printf("  Each linked list node will be processed by function 'processwork()'\n");
    printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N+1,FS); 

    std::vector<node*> parr = init_list();
    start = omp_get_wtime();
    {
#pragma omp parallel firstprivate(i) 
        {
            int id = omp_get_thread_num();
            i += id;
            while (i <= N) {
                processwork(parr[i]);
                i += NUM_THREADS;
            }
        }
    }

    end = omp_get_wtime();
    i = 0;
    while (parr[i] != NULL) {
        printf("%d : %d\n",parr[i]->data, parr[i]->fibdata);
        free (parr[i]);
        i += 1;
    }  

    printf("Compute Time: %f seconds\n", end - start);
    return 0;
}

std::vector<node*> init_list() {
    node *p = new node();
    std::vector<node*> parr(N+1, new node());

    p->data = FS;
    p->fibdata = 0;
    parr[0] = p;
#pragma omp parallel for schedule(static,1)
    for (int i = 0; i < N; ++i) {
        p = new node();
        p->data = FS + i + 1;
        p->fibdata = i + 1;
        parr[i]->next = p;
        if (parr[i+1]->next != nullptr) p->next = parr[i+1]->next;
        parr[i+1] = p;
    }
    parr[parr.size()-1]->next = NULL;
    return parr;
}

int fib(int n) {
    int x, y;
    if (n < 2) {
        return (n);
    } else {
        x = fib(n - 1);
        y = fib(n - 2);
        return (x + y);
    }
}

void processwork(struct node* p) {
    int n;
    n = p->data;
    p->fibdata = fib(n);
}


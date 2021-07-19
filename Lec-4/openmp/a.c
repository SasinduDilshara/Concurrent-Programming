
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int n = 100;


int counter = new Counter(1);
    
void count() {
  long j = 0;
  while (j < 1010) {
    j = counter.getAndIncrement();
    A[j] = j * (j+1) / 2
}


int main(int argc, char* argv[]) {
    int*[n] A;
    int thread_count = strtol(argv[1], NULL, 10);

    # pragma omp parallel num_threads(thread_count)
    count();
    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void count();

void count() {
     while (j < num_of_tosses) {
        x = random number between 1 and -1
        y = random number between 1 and -1
        ds= x*x + y*y;
        if (ds <=1 ) number_in_count ++
    }
}

int main(int argc, char* argv[]) {
    double pi= 0.0;
    int number_in_count =0;
    int num_of_tosses  = strtol(argv[1], NULL, 10); // take the num of threads as user argument

    # pragma omp parallel num_threads(num_of_tosses)
    count();
    pi = 4*number_in_count / ((double) numbr_of_tosses);
    printf("Result %.2e\n", pi);
    return 0;
}


// gcc -g -Wall -fopenmp -o omp_out count-pi.c

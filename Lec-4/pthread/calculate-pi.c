
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define n 100000000

double sum = 0.0;
int thread_count;

void *calculate_pi(void* rank) {
    long my_rank = (long) rank;
    double factor;
    double long i;
    double local_sum = 0.0;
    double long my_n = n / thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_n + my_first_i;

    if (my_first_i % 2 == 0) {
        factor = 1.0;
    } else {
        factor = -1.0;
    }

    for (i = my_first_i; i<= my_last_i; i++, factor = -factor) {
        local_sum += factor / ((2 * i) + 1);
    }
    sum += local_sum;
    return NULL;
}

int main(int argc, char* argv[]) {
    long thread;
    pthread_t* thread_handles;
    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc (thread_count*sizeof(pthread_t));
    
    for (thread = 0; thread < thread_count; thread++) 
        pthread_create(&thread_handles[thread], NULL, calculate_pi, (void*) thread);

    
    printf("\nThis is main thread\n");
    for (thread = 0; thread < thread_count; thread++) 
        pthread_join(thread_handles[thread], NULL);

    printf("Sum - %f", 4 * (sum));
    
    free(thread_handles);
    return 0;
}
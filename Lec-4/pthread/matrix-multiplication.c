
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

# define m 2
#define n 3
# define t 2

// const int A[m][n] = {{1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}};
// const int x[n][t] = {{1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}};

//const int A[m][n] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
//const int x[n][t] = {{1, 1}, {1, 1}, {1, 1}};

const int A[m][n] = {{1, 2, 3}, {4, 5, 6}};
const int x[n][t] = {{7, 8}, {9, 10}, {11, 12}};

int thread_count;
int y[m][t];

void *Pth_mat_vect(void* rank) {
    long my_rank = (long) rank;
    int i,j,k;
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;
    printf("This is thread %ld of %d and its count from %d to %d\n", my_rank, thread_count, my_first_row, my_last_row);

    for (i = my_first_row; i<= my_last_row; i++) {
        for (k = 0; k < t; k++) {
          y[i][k] = 0.0;
          for (j = 0; j < n; j++) {
            y[i][k] += A[i][j] * x[j][k];
          }
        }
    }
    return NULL;
}

void print_matrix();

void print_matrix() {
    int i, j;
    for(i=0; i<m; i++) {
        for(j=0; j<t; j++) {
          printf("%d | ", y[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    long thread;
    pthread_t* thread_handles;
    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc (thread_count*sizeof(pthread_t));
    
    for (thread = 0; thread < thread_count; thread++) 
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void*) thread);

    
    printf("\nThis is main thread\n");
    for (thread = 0; thread < thread_count; thread++) 
        pthread_join(thread_handles[thread], NULL);

    print_matrix();
    
    free(thread_handles);
    return 0;
}
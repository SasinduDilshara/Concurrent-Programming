#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 65635

int number_of_thread;
int m;
double m_fraction;
double i_fraction;
double d_fraction;
struct node* root;

struct node {
    int data;
    struct node *next;
};

int Member(int value, struct node *linked_list) {
    struct node *current = linked_list;

    while (current != NULL && current->data < value) {
        current = current->next;
    }

    if (current == NULL || current->data >value) {
        return 0;
    } else {
        return 1;
    }
}

int Insert(int value, struct node **linked_list) {
    struct node *current_node = *linked_list;
    struct node *pred_p = NULL;
    struct node *temp_p;

    while (current_node != NULL && current_node->data < value) {
        pred_p = current_node;
        current_node = current_node->next;
    }

    if (current_node == NULL || current_node->data > value) {
        temp_p = (struct node*) malloc(sizeof(struct node));
        temp_p->data = value;
        temp_p->next = current_node;

        if (pred_p == NULL) {
            *linked_list = temp_p;
        } else {
            pred_p->next = temp_p;
        }
        return 1;
    } else {
        return 0;
    }
}

int Delete(int value, struct node **linked_list) {
    struct node *current = *linked_list;
    struct node *pred_p = NULL;

    while (current != NULL && current->data < value) {
        pred_p = current;
        current = current->next;
    }

    if (current != NULL && current->data == value) {
        if (pred_p == NULL) {
            *linked_list = current->next;
            free(current);
        } else {
            pred_p->next = current->next;
            free(current);
        }
        return 1;
    } else {
        return 0;
    }

}

void shuffle(int* array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = (rand() * rand()) % (n - 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void execute(double m_fraction, double i_fraction, double d_fraction, struct node *root, int *n) {
    int insert_count = (*n) * i_fraction;
    int member_count = (*n) * m_fraction;
    int delete_count = (*n) * d_fraction;
    int opers[insert_count + member_count + delete_count];
    int loop;
    // int total = insert_count + member_count + delete_count;
    printf("insert_count - %d\n", insert_count);
    printf("member_count - %d\n", member_count);
    printf("delete_count - %d\n", delete_count);

    for(int i = 0; i < insert_count + member_count + delete_count; i++) {
        if (i < insert_count) {
            opers[i] = 0;
        } else if (i >= insert_count && i < insert_count + member_count) {
            opers[i] = 1;
        } else {
            opers[i] = 2;
        } 
        // printf("%d ", opers[i]);
    }

    for(loop = 0; loop < 10; loop++)
      printf("%d ", opers[loop]);

    printf("\n");

    shuffle(opers, insert_count + member_count + delete_count);

   for(loop = 0; loop < 10; loop++)
      printf("%d ", opers[loop]);

    printf("\n");


}

void Print(struct node *root) {
    struct node *current = root;

    while(current->next !=NULL) {
        printf("(%d)\n |\n\\/\n",current->data);
        current = current->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    long thread;
    printf("Sequential Linked List Testing\n");
    pthread_t* thread_handles;
    number_of_thread = strtol(argv[1], NULL, 10);
    thread_handles = malloc (number_of_thread*sizeof(pthread_t));

    int n = atoi(argv[2]);
    m = atoi(argv[3]);

    m_fraction = atof(argv[4]);
    i_fraction = atof(argv[5]);
    d_fraction = atof(argv[6]);

    int random = rand() % MAX;
    root = (struct node*) malloc(sizeof(struct node));
    root->data = random;

    int i = 1;
    srand(time(NULL));
    while(i < n-1) {
        random = rand() % MAX; 
        if (Insert(random, &root) == 1) {
            i++;
        }
        // printf("i%d\n", i);
    }

    for (thread = 0; thread < number_of_thread; thread++) 
        pthread_create(&thread_handles[thread], NULL, execute, (void*) thread, m_fraction, i_fraction, d_fraction, root, &n);
    // execute(m_fraction, i_fraction, d_fraction, root, &n);
    // Print(root);
    return 0;
}


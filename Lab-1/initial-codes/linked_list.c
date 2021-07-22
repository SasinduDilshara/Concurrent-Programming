#include <stdio.h>
#include <stdlib.h>

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

void Print(struct node *root) {
    struct node *current = root;

    while(current->next !=NULL) {
        printf("(%d)\n |\n\\/\n",current->data);
        current = current->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

    printf("Sequential Linked List Testing\n");
    
    int iter = atoi(argv[1]);
    long max = strtol(argv[2], NULL, 10);

    struct node *root;
    int random = rand() % max;
    root = (struct node*) malloc(sizeof(struct node));
    root->data = random;

    for (int i=0; i < iter; i++) {
        int random = rand() % max;
        Insert(random, &root);
    }

    Print(root);
    
}
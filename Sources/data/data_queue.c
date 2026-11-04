#include "data_queue.h"

void grow_queue(queue* p) {
    CHECK_NULL(2, p, "The queue", p->array, "The array in the queue");
    int n = p->size_array;
    p->size_array = n * 2;
    REALLOC(p->array, p->size_array);
    if (p->right <= p->left && !(p->empty)) {
        int i;
        for (i = 0;i < p->right;i++) {
            p->array[n + i] = p->array[i];
        }
        p->right = n + p->right;
    }
}

static void reverse_array(int* array, int l, int r)
{
    int i, j;
    for (i = l, j = r; i < j; i++, j--)
    {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void shrink_queue(queue* p) {
    CHECK_NULL(2, p, "The queue", p->array, "The array in the queue");
    if (p->size_array == 1) {
        return;
    }

    int size = getsize_queue(p);

    // Rotation du tableau pour mettre la valeur gauche du tuyau
    // dans la case 0

    if (p->left != 0) {
        reverse_array(p->array, 0, p->left - 1);
        reverse_array(p->array, p->left, p->size_array - 1);
        reverse_array(p->array, 0, p->size_array - 1);

    }

    // Mise à jour des informations
    p->size_array = p->size_array / 2;
    p->left = 0;
    if (size <= p->size_array) {
        p->right = size;
    }
    else {
        p->right = p->size_array;
    }

    // Réallocation

    REALLOC(p->array, p->size_array);
}


queue* create_queue(void) {
    queue* new;
    MALLOC(new, 1);
    MALLOC(new->array, 1);
    new->size_array = 1;
    new->left = 0;
    new->right = 0;
    new->empty = true;
    return new;
}


void delete_queue(queue* p) {
    CHECK_NULL(1, p, "The queue");
    free(p->array);
    free(p);
}


bool is_empty_queue(queue* p) {
    return p->empty;
}



int getsize_queue(queue* p) {

    if (p->empty) {
        return 0;
    }
    else if (p->left < p->right) {
        return p->right - p->left;
    }
    else {
        return (p->size_array - p->left) + p->right;

    }


}


int read_queue(queue* p, int i) {
    if (getsize_queue(p) - 1 < i) {
        fprintf(stderr, "Error, the queue is not large enough %d, %d\n", getsize_queue(p), i);
        exit(EXIT_FAILURE);
    }
    return p->array[(p->left + i) % p->size_array];
}




void enqueue(int val, queue* p) {
    if (p->right <= p->left && !(p->empty)) {
        grow_queue(p);
    }
    if (p->left == 0) {
        p->left = p->size_array - 1;
    }
    else {
        p->left--;
    }
    p->array[p->left] = val;
    p->empty = false;
}




int dequeue(queue* p) {
    if (p->right == 0) {
        p->right = p->size_array - 1;
    }
    else {
        p->right--;
    }
    if (p->left == p->right) {
        p->empty = true;

    }
    if (p->size_array >= 2 && getsize_queue(p) <= p->size_array / 4) {
        shrink_queue(p);
    }
    return p->array[p->right];


}

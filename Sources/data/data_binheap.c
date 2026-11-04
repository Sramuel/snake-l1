#include "data_binheap.h"

int left_binheap(int i) {
    return 2 * i + 1;
}
int right_binheap(int i) {
    return 2 * i + 2;
}
int parent_binheap(int i) {
    return (i - 1) / 2;
}
bool isvalid_binheap(binheap* p, int i) {
    return i < p->size_heap;
}

void grow_binheap(binheap* p) {
    CHECK_NULL(2, p, "The binary heap", p->array, "The array used to implement the binary heap");
    p->size_array = p->size_array * 2;
    REALLOC(p->array, p->size_array);
}
void shrink_binheap(binheap* p) {
    CHECK_NULL(2, p, "The binary heap", p->array, "The array used to implement the binary heap");
    if (p->size_array == 1) {
        return;
    }
    p->size_array = p->size_array / 2;
    REALLOC(p->array, p->size_array);
}


binheap* create_binheap(int (*fc) (void*, void*)) {
    binheap* new;
    MALLOC(new, 1);
    MALLOC(new->array, 1);
    new->size_array = 1;
    new->size_heap = 0;
    new->fc = fc;
    return new;
}

void delete_binheap(binheap* p) {
    CHECK_NULL(1, p, "The binary heap");
    free(p->array);
    free(p);
}

bool isempty_binheap(binheap* p) {
    return p->size_heap == 0;
}

int getsize_binheap(binheap* p) {
    return p->size_heap;
}

static void void_swap(void** a, void** b) {
    CHECK_NULL(2, a, "Le premier entier à échanger", b, "Le second entier à échanger");
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}

static void percup_binheap(binheap* p, int i) {
    CHECK_NULL(2, p, "The binary heap", p->array, "The array used to implement the binary heap");
    while (i != 0 && (*p->fc)(p->array[i], p->array[parent_binheap(i)]) > 0) {
        void_swap(p->array + i, p->array + parent_binheap(i));
        i = parent_binheap(i);
    }
}

void push_binheap(binheap* p, void* val) {
    CHECK_NULL(2, p, "The binary heap", p->array, "The array used to implement the binary heap");
    if (p->size_array == p->size_heap) {
        grow_binheap(p);
    }
    p->array[p->size_heap] = val;
    percup_binheap(p, p->size_heap);
    p->size_heap++;
}

void* peekmin_binheap(binheap* p) {
    CHECK_NULL(2, p, "The binary heap", p->array, "The array used to implement the binary heap");
    return p->array[0];
}

static void percdown_binheap(binheap* p, int i) {
    CHECK_NULL(2, p, "The binary heap", p->array, "The array used to implement the binary heap");
    int left = left_binheap(i);
    int right = right_binheap(i);

    while ((isvalid_binheap(p, left) && (*p->fc)(p->array[left], p->array[i]) > 0) || (isvalid_binheap(p, right) && (*p->fc)(p->array[right], p->array[i]) > 0)) {
        if (!isvalid_binheap(p, right) || (*p->fc)(p->array[left], p->array[right]) > 0) {
            void_swap(p->array + i, p->array + left);
            i = left;
            left = left_binheap(i);
            right = right_binheap(i);
        }
        else {
            void_swap(p->array + i, p->array + right);
            i = right;
            left = left_binheap(i);
            right = right_binheap(i);
        }
    }


}


void* popmin_binheap(binheap* p) {
    CHECK_NULL(2, p, "The binary heap", p->array, "The array used to implement the binary heap");
    void* res = p->array[0];
    p->size_heap--;
    p->array[0] = p->array[p->size_heap];
    percdown_binheap(p, 0);
    if (p->size_array > 1 && p->size_heap <= p->size_array / 4) {
        shrink_binheap(p);
    }
    return res;
}

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector {
    size_t size, capacity;
    int *arr;
} vector;

/// Geometrically increase capacity
size_t calc_new_capacity(size_t old_capacity, size_t new_size) {
    if (old_capacity > SIZE_MAX - old_capacity / 2) return SIZE_MAX;
    const size_t new_capacity = old_capacity + old_capacity / 2;
    if (new_capacity < new_size) return new_size;
    return new_capacity;
}

/// Add an element at the end
void push_back(vector *self, int x) {
    if (self->size == self->capacity) {
        const size_t new_capacity = calc_new_capacity(self->capacity, self->size + 1);
        int *new_arr = malloc(sizeof(int) * new_capacity);
        memcpy(new_arr, self->arr, sizeof(int) * self->size);
        free(self->arr);
        self->arr = new_arr;
        self->capacity = new_capacity;
    }
    self->arr[self->size++] = x;
}

/// Remove and element from the end
void pop_back(vector *self) {
    assert(self->size && "pop element on empty array!");
    self->size--;
}

/// Reserve more capacity to git rid of reallocation when `push_back`
void reserve(vector *self, size_t new_capacity) {
    if (new_capacity <= self->capacity) return; // `reserve` never shrinks

    int *new_arr = malloc(sizeof(int) * new_capacity);
    memcpy(new_arr, self->arr, sizeof(int) * self->size);
    free(self->arr);
    self->arr = new_arr;
    self->capacity = new_capacity;
}

#define vector_init() ((vector){.size = 0, .capacity = 0, .arr = NULL})
#define vector_destroy(v) free((v).arr)

int main(int argc, const char *argv[]) {
    vector v;
    v = vector_init(); // ctor

    reserve(&v, 1000);

    for (int i = 0; i < 1000; ++i) push_back(&v, i);
    for (int i = 0; i < v.size; ++i) printf("%d ", v.arr[i]);
    for (int i = 0; i < 300; ++i) pop_back(&v);

    printf("\nsize: %zu, capacity: %zu\n", v.size, v.capacity);

    vector_destroy(v); // dtor
}
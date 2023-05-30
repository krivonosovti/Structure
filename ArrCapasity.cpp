#include <iostream>
using namespace std;

#define ARRAY_MIN_CAPACITY 10

size_t array_capacity_fr(size_t count)
{
    return 2 * count;
}

size_t array_capacity_fs(size_t count)
{
    return 4 * count;
}

typedef size_t(*array_capacity_f) (size_t);

typedef struct arr
{
    void* data;
    size_t size;         /*size of elem*/
    size_t capacity;     
    size_t min;          /* min capacity*/
    size_t count;        /* number of element*/
    array_capacity_f fr; //installed capacity according to the size of the arr
    array_capacity_f fs; /* maximum capacity by arr size*/
}arr;

int array_set_capacity(arr* a, size_t capacity)
{
    void* n = realloc(a->data, capacity * a->size);
    if (!n) return -1;
    a->capacity = capacity;
    a->data = n;
    if (a->count > capacity) a->count = capacity;
    return 0;
}
int array_adjust_capacity(arr* a)
{
    size_t capacity = a->fr(a->count);
    if (capacity < a->min) capacity = a->min;
    return array_set_capacity(a, capacity);
}
void array_free(arr* a)
{
    free(a->data);
    free(a);
}
arr* array_alloc(size_t size, size_t min, array_capacity_f fr, array_capacity_f fs)
{
    arr* a = (arr*) malloc(sizeof * a);
    if (!a) return NULL;
    if (!min) min = ARRAY_MIN_CAPACITY;
    if (!fr)  fr = array_capacity_fr;
    if (!fs)  fs = array_capacity_fs;
    a->count = 0;
    a->size = size;
    a->data = NULL;
    a->min = min;
    a->capacity = min;
    a->fr = fr;
    a->fs = fs;
    array_adjust_capacity(a);
    return a;
}
arr* array_copy(const arr* a)
{
    arr* b = array_alloc(a->size, a->min, a->fr, a->fs);
    if (!b) return NULL;
    if (array_resize(b, a->count))
    {
        array_free(b);
        return NULL;
    }
    memcpy(b->data, a->data, a->count * b->size);
    return b;
}
int array_set_min_capacity(arr* a, size_t min)
{
    arr b = *a;
    if (!min) min = ARRAY_MIN_CAPACITY;
    b.min = min;
    if (array_adjust_capacity(&b)) return -1;
    *a = b;
    return 0;
}
int array_set_capacity_fr(arr* a, array_capacity_f fr)
{
    arr b = *a;
    if (!fr) fr = array_capacity_fr;
    b.fr = fr;
    if (array_adjust_capacity(&b)) return -1;
    *a = b;
    return 0;
}
int array_set_capacity_fs(arr* a, array_capacity_f fs)
{
    arr b = *a;
    if (!fs) fs = array_capacity_fs;
    b.fs = fs;
    if (array_adjust_capacity(&b)) return -1;
    *a = b;
    return 0;
}
int array_resize(arr* a, size_t count)
{
    arr b = *a;
    b.count = count;
    if (((count > a->count && count > b.capacity) ||
        (count < a->count && a->fs(count) < b.capacity)
        ) && array_adjust_capacity(&b)
        ) return -1;
    *a = b;
    return 0;
}


// obxod arr dla vsex vidov
typedef void (*array_icallback_f) (void* e, size_t i, size_t n, void* data);
typedef void (*array_icallback_f_const) (const void* e, size_t i, size_t n, void* data);
void array_iforeach(arr* a, array_icallback_f f, void* data)
{
    size_t i = 0;
    for (; i < a->count; ++i) f(array_ptr(a, i), i, a->count, data);
}
void array_iforeach_const(const arr* a, array_icallback_f_const f, void* data)
{
    size_t i = 0;
    for (; i < a->count; ++i) f(array_ptr_const(a, i), i, a->count, data);
}
void print_int(const void* e, size_t i, size_t n, void* data)
{
    printf("%i%s", *(int*)e, i == n - 1 ? "" : ", ");
}
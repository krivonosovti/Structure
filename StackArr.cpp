#include<iostream>
#include"Arr.h"

using namespace std;

stack* stack_alloc()
{
    return array_alloc(0);
}

stack* stack_clone(const stack* s)
{
    return array_clone(s);
}
void    stack_free(stack* s)
{
    array_free(s);
}

int stack_is_empty(const stack* s)
{
    return array_get_size(s) == 0;
}
int stack_is_full(const stack* s)
{
    size_t max_size = array_max_size(s);
    return max_size != 0 && max_size == array_get_size(s);
}

int stack_push(stack* s, element_t  e)
{
    size_t size = array_get_size(s),
        new_size = size + 1;
    if (array_resize(s, new_size)) return 1;
    *array_ptr(s, size) = e;
    return 0;
}
int stack_pop(stack* s, element_t* e)
{
    size_t size = array_get_size(s),
        new_size = size - 1;
    if (size == 0) return 1;
    if (e) *e = *array_ptr_const(s, new_size);
    if (array_resize(s, new_size)) return 1;
    return 0;
}
const element_t * stack_get_front(const stack * s)
{
    size_t size = array_get_size(s);
    if (size == 0) return NULL;
    return array_ptr_const(s, size - 1);
}
#include <iostream>
using namespace std;

typedef struct node node;
struct stack
{
    node* top;
};
stack* stack_alloc()
{
    stack* s = malloc(sizeof(*s));
    if (!s) return NULL;
    s->top = NULL;
    return s;
}
int stack_is_empty(const stack* s)
{
    return s->top == NULL;
}
int stack_is_full(const stack* s)
{
    return 0;
}
int stack_push(stack* s, element_t  e)
{
    node* n = malloc(sizeof(*n));
    if (!n) return 1;
    n->data = e;
    n->next = s->top;
    s->top = n;
    return 0;
}
int stack_pop(stack* s, element_t* e)
{
    node* t = s->top;
    if (s->top == NULL) return 1;
    s->top = t->next;
    if (e) *e = t->data;
    free(t);
    return 0;
}
const element_t* stack_get_front(const stack* s)
{
    return s->top == NULL ? NULL : &(s->top->data);
}
void    stack_free(stack* s)
{
    while (!stack_pop(s, NULL));
    free(s);
}
void    stack_free(stack* s)
{
    node* t = s->top;
    while (t != NULL)
    {
        s->top = t->next;
        free(t);
        t = s->top;
    }
    free(s);
}
stack* stack_clone(const stack* s)
{
    stack* r, * t, ** n;
    *r = malloc(sizeof(*r));
    if (!r) return NULL;
    *t = s->top;
    node** n = &(r->top);
    while (t != NULL)
    {
        *n = malloc(sizeof(**n));
        if (!*n)
        {
            stack_free(r);
            return NULL;
        }
        (*n)->data = t->data;
        (*n)->next = NULL;
        n = &((*n)->next);
        t = t->next;
    }
    return r;
}
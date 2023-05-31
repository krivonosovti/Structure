#include <iostream>
using namespace std; 
typedef int element_t;

typedef struct node
{
    element_t data;
    node* next;
};

typedef struct loop_list
{
    node* current;
} loop_list;

loop_list* loop_init() 
{
    loop_list* l = (loop_list*)malloc(sizeof(*l));
    if (!l)
        return NULL;
    l->current = NULL;
    return l;
}
void loop_free(loop_list* l)
{
    free(l->current->next);
    free(l->current);
    free(l);
}

int loop_is_empty(loop_list* l)
{
    return l->current == NULL;
}


const element_t* loop_get_current_const(const loop_list* l)
{
    return l->current == NULL ? NULL : &(l->current->data);
}
element_t* loop_get_current(loop_list* l)
{
    return l->current == NULL ? NULL : &(l->current->data);
}
int loop_go_next(loop_list* l)
{
    if (l->current == NULL) return 1;
    l->current = l->current->next;
    return 0;
}

int loop_insert_after(loop_list* l, element_t e)
{
    node* n = (node*) malloc(sizeof(*n));
    if (!n) return 1;
    n->data = e;
    if (l->current == NULL)
    {
        n->next = n;
        l->current = n;
    }
    else
    {
        n->next = l->current->next;
        l->current->next = n;
    }
    return 0;
}
int loop_delete_next(loop_list* l, element_t* e)
{
    node* t;
    if (l->current == NULL) return 1;
    t = l->current->next;
    if (t->next == t)
        l->current = NULL;
    else
        l->current->next = t->next;
    if (e) *e = t->data;
    free(t);
    return 0;
}
loop_list* loop_copy(const loop_list* l)
{
    loop_list* r = loop_init();
    if (!r) return NULL;
    if (l->current == NULL) return r;

    node* n = l->current, * i = l->current;
    do
    {
        if (loop_insert_after(r, i->data))
        {
           
            loop_free(r);
            return NULL;
        }
        
        r->current = r->current->next;
        i = i->next;
    } while (i != n);
    return r;
}
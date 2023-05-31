#include <iostream>
using namespace std;
typedef int element_t;

//decreasing heap
struct node 
{
	element_t key;
	node* sibling;
	node* child;
};

struct heap
{
	node* root;
};

heap* heap_init()
{
	heap* H = (heap*)malloc(sizeof(heap));
	if (!H)
		return NULL;
	H->root = NULL;
	return H;
}

const node* pheap_min(heap* h)
{
	return h->root;
}

node* pheap_add_child(node* h, node* n)
{
	n->sibling = h->child;
	h->child = n;
	return h;
}

node* pheap_merge(node* a,node* b)
{
	if (!a) return b;
	if (!b) return a;
	if (a->key < b->key)
		return pheap_add_child(a, b);
	else
		return pheap_add_child(b, a);
}

int pheap_insert(heap* h, element_t key)
{
	node* n = (node*)malloc(sizeof(node));
	if (!n) return -1;
	n->key = key;
	n->child = NULL;
	n->sibling = NULL;
	h->root = pheap_merge(h->root, n);
	return 0;
}
node* pheap_heapify(node* n)
{
	if (!n || !n->sibling) return n;
	node* a = n, * b = n->sibling, * c = n->sibling->sibling;
	a->sibling = NULL;
	b->sibling = NULL;
	return pheap_merge(pheap_merge(a, b), pheap_heapify(c));
}
int pheap_pop(heap* h)
{
	if (!h->root) return -1;
	node* t = h->root;
	h->root = pheap_heapify(h->root->child);
	free(t);
	return 0;
}
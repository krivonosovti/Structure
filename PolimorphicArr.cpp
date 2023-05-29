#include <iostream>

using namespace std;

typedef struct arr
{
	void* data;
	size_t size;
	size_t count;
}arr;

arr* array_alloc(size_t count, size_t size)
{

	arr* Array = (arr*)malloc(sizeof(arr));
	if (!Array)
		return NULL;

	if (!count)
		Array->data = NULL;


	else if (!(Array->data = (void*)malloc(count * size)))
	{
		free(Array);
		return NULL;
	}
	Array->size = size;
	Array->count = count;
	return Array;
}

void* array_free(arr* a)
{
	free(a->data);
	free(a);
}
arr* array_clone(const arr* Dst)
{
	arr* r = array_alloc(Dst->count, Dst->size);
	if (!r)
		return NULL;
	memcpy(Dst->data, r->data, Dst->count * Dst->size);
	return r;
}

int array_resize(arr* a, size_t newSize)
{
	if (newSize == a->size)
		return 0;
	if (newSize)
	{
		void* n = (void*)realloc(a->data, newSize * a->size);// почему у Ћов€ги int*?
		if (!n) return 1;
		a->data = n;
	}
	else
	{
		free(a->data);
		a->data = NULL;
	}
	a->count = newSize;
	return 0;
}
void* array_ptr(arr* a, size_t i)
{
	return (char*)a->data + i * a->size;
}
const void* array_ptr_const	(const arr* a, size_t i)
{
	return (char*)a->data + i * a->size;
}
int array_set(arr* a, size_t i, void* e)
{
	if (i < a->size)
	{
		memcpy(array_ptr(a, i), e, a->size);
		return 0;
	}
	return 1;
}
int array_get(const arr* a, size_t i, void* e)
{
	if (i < a->size)
	{
		memcpy(e, array_ptr_const(a, i) a->size;
		return 0;
	}
	return 1;
}
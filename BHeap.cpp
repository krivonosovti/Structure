#include <iostream>
using namespace std;

typedef int key_t ;

struct  bheap
{
	size_t size; 
	key_t *data;
};
bheap* bheap_init() 
{
	bheap* h = (bheap*) malloc(sizeof(h));
	if (!h)
		return NULL;
	h->size = 0;
	h->data = NULL;
	return h;
}
void bheap_free(bheap* h)
{
	free(h->data);
	free(h);
}

const key_t* bheap_min(const bheap* h)
{
	return h->size ? h->data : NULL;
}

size_t bheap_parent(size_t i)
{
	return (i - 1) / 2;
}
size_t bheap_left(size_t i)
{
	return 2 * i + 1;
}

int bheap_insert(bheap* h, key_t e)
{
	size_t i = 0, parent;
	if (!h)
		return -1;

	key_t* data = (key_t*) realloc(h->data, (h->size + 1) * sizeof(key_t)); // увеличиваем кучу (делаем коряво что-бы не испортить дерево при невыполнении функции)
	if (!data) return -1;
	h->data = data;
	for (i = h->size; i; i = parent)
	{
		parent = bheap_parent(i);
		if (h->data[parent] < e) break;
		h->data[i] = h->data[parent];
	}
	++h->size;
	h->data[i] = e;
	return 0;
}
int bheap_pop(bheap* h) // удаление корня
{
    size_t i, left, right, swap;
    key_t x, * data;
    if (h->size == 0) 
        return -1;
    if (h->size == 1) /* Если удаляется последний элемент */
    {
       bheap_free(h);
        return 0;
    }
    x = h->data[h->size - 1];  // последний элемент 
    data = (key_t*) realloc(h->data, sizeof(key_t) * h->size);
        
    if (!data) return -1;

    --h->size;
    h->data = data;

    /*Цикл от вершины со спуском влево или вправо - индекс swap */
    for (i = 0; 1; i = swap)
    {
        left = bheap_left(i);
        /* Остановка если дочерних элементов нет*/
        if (left >= h->size) break;

        right = left + 1;
        /* Выбираем спуск вправо если пр */
        if (right < h->size && h->data[right] < h->data[left])
            swap = right;
        else swap = left;

        /* Остановка если изъятый жлемент меньше всех дочерних*/
        if (x < h->data[swap]) break;
        /*поднимаем выбранный элемент */
        h->data[i] = h->data[swap];
    }
    /*Вставляем изъятый последний элемент*/
    h->data[i] = x;
    return 0;
}

int bheap_sort(key_t* data, size_t size) // хуйня какая-то
{
    bheap* h = bheap_init();
    if (!h) return -1;
    size_t i;
    for (i = 0; i < size; ++i)
    {
        if (bheap_insert(h, data[i]))
        {
            bheap_free(h);
            return -1;
        }
    }
    for (i = 0; i < size; ++i)
    {
        data[i] = *bheap_min(h);
        if (bheap_pop(h)) return -1;
    }
    bheap_free(h);
    return 0;
}
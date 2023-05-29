#include<iostream>
using namespace std;

typedef int (*comp_func) (void*, void*); // какая-то функция сравнения определенного тип


/* сотирует массив array
 * n - число элементов массива 
 * m - размер массива
 * cmp - функция сраавнения
 */
void sort_select(void* arr, size_t n, size_t m, comp_func cmp)
{
	size_t i, j, n1 = n - 1;
	void* t = (void*) malloc(m);
	char* a = (char*)arr;

	for (i = 0; i < n1; ++i)
	{
		size_t k = i; 
		for (j = i + 1; j < n; ++j)
			if (cmp(a + k * m, a + j * m))
				k = j;
		if (k != i)
		{
			memcpy(t, a + k * m, m);
			memcpy(a + k * m, a + i * m, m);
			memcpy(a + i * m, t, m);

		}
	}
	free(t);
}
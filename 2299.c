#include <stdio.h>
#include <stdlib.h>

//given at most 500,000 numbers, so the number of swap operations is less than 500000*499999/2
long g_swap_count;

void merge(int *a, int s, int m, int e)
{
	int p1 = s;
	int p2 = m + 1;
	 int * merged = (int*)malloc(sizeof(int) * (e - s + 1));
	 int p = 0;
	while(p1 < m + 1 && p2 < e + 1)
	{
		if(a[p1] > a[p2])
		{
			 merged[p] = a[p2];
			p2++;
			g_swap_count += (m + 1 - p1);
		}
		else
		{
			 merged[p] = a[p1];
			p1++;
		}
	 	p++;
	}

	 while(p1 < m + 1)
	 {
	 	merged[p++] = a[p1++];
	 }

	 while(p2 < e + 1)
	 	merged[p++] = a[p2++];

	 int i;
	 for(i = 0;i < (e -s+1); i++)
	 {
	 	a[s + i] = merged[i];
	 }

	 free(merged);
}

void merge_sort(int *a, int s, int e)
{
	if(s < e)
	{
		int mid = (s + e) / 2;
		merge_sort(a, s, mid);
		merge_sort(a, mid + 1, e);
		merge(a, s, mid, e);
	}
}

int main()
{
	int size;
	while(1)
	{
		scanf("%d", &size);
		if(size > 0)
		{
			g_swap_count = 0;
			int *array = (int *)malloc(sizeof(int) * size);
			int i;
			for(i = 0; i < size; ++i)
				scanf("%d", &array[i]);

			merge_sort(array, 0, size - 1);
			free(array);
			printf("%ld\n", g_swap_count);
		}
		else
			break;
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))

//given at most 1000 numbers, so the number of swap operations is less than 1000*999/2, type int is big enough
int g_swap_count;

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

void merge_sort(int *a, int n)
{
	int width;
	for(width = 1; width < n; width = 2 * width)
	{
		int i;
		for(i = 0; i < n; i = i + 2 * width)
		{
			merge(a, i, min(i + width - 1, n - 1), min(i + 2 * width - 1, n - 1) );
		}
	}
}

int main()
{
	int cases;
	scanf("%d", &cases);
	int i;
	for(i = 1; i <= cases; ++i)
	{
		int length;
		scanf("%d", &length);
		int *array = (int *)malloc(sizeof(int) * length);
		int j;
		for(j = 0; j < length; ++j)
		{
			scanf("%d", &array[j]);
		}
		g_swap_count = 0;
		merge_sort(array, length);
		printf("Scenario #%d:\n%d\n\n", i, g_swap_count);
		free(array);
	}

	return 0;
}
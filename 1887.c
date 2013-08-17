#include <stdio.h>
#include <stdlib.h>

#define NMAX 10240

/**
* the array isn't strictly descending,
* return the index of the first element that's less than the target element
* case: 7 5 7 6
**/
int binary_search(int *a, int value, int start, int end)
{
	while(start <= end)
	{
		int mid = (start + end) / 2;
		if(a[mid] >= value)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}

	return start;
}

int LDS(int *a, int size)
{
	int i;
	int *M = (int *)malloc(sizeof(int) * size);
	M[0] = a[0];
	int len = 0;
	for(i = 1; i < size; ++i)
	{
		if(a[i] <= M[len])
		{
			M[++len] = a[i];
		}
		else
		{
			int pos = binary_search(M, a[i], 0, len);
			M[pos] = a[i];
		}

	}
	free(M);
	return len + 1;
}

int main()
{
	int heights[NMAX];
	int test_number = 0;
	int size;
	while(scanf("%d", &heights[0]), heights[0] != -1)
	{
		size = 1;
		test_number++;
		while(scanf("%d", &heights[size]), heights[size++] != -1);
		printf("Test #%d:\n  maximum possible interceptions: %d\n\n", test_number, LDS(heights, size - 1) );
	}

	return 0;
};

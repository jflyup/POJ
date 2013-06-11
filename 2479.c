#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_subarray(int * arr, int size)
{
	int max_sum = arr[0];
	int max_so_far = arr[0];
	int i;
	for(i = 1; i < size; ++i)
	{
		max_so_far = (max_so_far + arr[i]) > arr[i] ? (max_so_far + arr[i]) : arr[i];
		if(max_so_far > max_sum)
			max_sum = max_so_far;
	}
	return max_sum;
}

int main()
{
	int cases;
	scanf("%d", &cases);
	int i;
	for(i = 0; i < cases; ++i)
	{
		int size;
		scanf("%d", &size);
		int *array = (int*)malloc(size * sizeof(int));
		int j;
		for(j = 0; j < size; ++j)
		{
			scanf("%d", &array[j]);
		}

		int maximum_sum = INT_MIN;
		for(j = 1; j < size; ++j)
		{
			int sum = max_subarray(array, j) + max_subarray(array + j, size - j);
			if(sum > maximum_sum)
				maximum_sum = sum;
		}
		printf("%d\n", maximum_sum);
		free(array);
	}
	return 0;
}


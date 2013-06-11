#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LOG_MAX 16

int max(int a, int b)
{
	return a > b ? a : b;
}

/*
 * max_ending_here[i] represent the maximum subarray ending at i
 * max_ending_here[i] = max(max_ending_here[i - 1] + a[i], a[i])
 */
void max_subarray(int * arr, int size, int * max_ending_here)
{
	max_ending_here[0] = arr[0];
	int i;
	for(i = 1; i < size; ++i)
	{
		max_ending_here[i] = max(max_ending_here[i - 1] + arr[i], arr[i]);
	}
}

void reverse_array(int *a, int size)
{
	int i;
	for(i = 0; i < size / 2; ++i)
	{
		//In most practical scenarios, the trivial swap algorithm using a temporary register is more efficient than the XOR swapping.
		int temp = a[i];
		a[i] = a[size - 1 - i];
		a[size - 1 - i] = temp;
	}
}

/*
 * RMQ: Range Minimum/Maximum Query
 * dp[i][j] represent the min/max value in the subarray starting at i haveing length 2^j.
 * dp[i][0] = a[i]
 * dp[i][j] = max(dp[i][j - 1], dp[i + 2 ^ (j - 1)][j - 1])
 */

void init_rmq(int *a, int len, int **dp)
{
	int i, j;
	for(i = 0; i < len; ++i)
	{
		dp[i][0] = a[i];
	}
	for(j = 1; (1<<j) <= len; ++j)
		for(i = 0; i + (1 << j) - 1 < len; i++)
		{
			dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
		}
}

int rmq(int **dp, int begin, int end)
{
	int distance = end - begin;
	int i;
	for(i = 0; (1 << i) < distance; ++i);
	if(i)
		--i;
	return max(dp[begin][i], dp[end - (1 << i) + 1][i]);

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
		int *max_ending_here = (int*)malloc(size * sizeof(int));
		max_subarray(array, size, max_ending_here);

		reverse_array(array, size);
		int *reverse_max_ending_here =(int*)malloc(size * sizeof(int)); 
		max_subarray(array, size, reverse_max_ending_here);

		int **dp = (int **)malloc(sizeof(int*) * size);
		for(j = 0; j < size; ++j)
			dp[j] = (int*)malloc(sizeof(int) * LOG_MAX);

		init_rmq(reverse_max_ending_here, size, dp);

		int maximum_sum = INT_MIN;
		int first_max_subarray = max_ending_here[0];
		for(j = 0; j < size - 1; ++j)
		{
			if(max_ending_here[j] > first_max_subarray)
				first_max_subarray = max_ending_here[j];
			int sum = first_max_subarray + rmq(dp, 0, size - j - 2);
			if(sum > maximum_sum)
				maximum_sum = sum;
		}
		printf("%d\n", maximum_sum);
		free(array);
		free(max_ending_here);
		free(reverse_max_ending_here);
		for(j = 0; j < size; ++j)
			free(dp[j]);
		free(dp);
	}
	return 0;
}


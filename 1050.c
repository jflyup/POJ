#include <stdio.h>
#include <limits.h>

int max(int a, int b)
{
	return a > b ? a : b;
}

int max_sum(int *array, int size)
{
	int i;
	int maximum = INT_MIN;
	int sum = 0;
	for(i = 0; i < size; ++i)
	{
		sum = max(sum + array[i], array[i]);
		if(sum > maximum)
			maximum = sum;
	}

	return maximum;
}

int main()
{
	int N;
	scanf("%d", &N);
	int matrix[100][100];
	int i, j, k, l;
	for(i = 0; i < N * N; ++i)
	{
		scanf("%d", &matrix[i / N][i % N]);
	}

	int max_sub_rect = INT_MIN;
	for(i = 0; i < N; ++i)
		for(j = i; j < N; ++j)
		{
			int column_sum[100] = {0};
			for(k = 0; k <= j - i; ++k)
				for(l = 0; l < N; ++l)
				{
					column_sum[l] += matrix[i + k][l];
				}
			max_sub_rect = max(max_sum(column_sum, N), max_sub_rect);
		}
	printf("%d", max_sub_rect);
	return 0;
};
#include <stdio.h>
#include <stdlib.h>

int binary_search(int *arr, int size, int x)
{
	int left = 0;
	int right = size - 1;
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if(arr[mid] <= x)
			left = mid + 1;
		else if(arr[mid] > x)
			right = mid - 1;
	}
	return left;
}

int LIS(int* a, int size)
{
	//M[j] stores the value of the smallest value a[k] such that there is an increasing subsequence of length j ending at a[k] on the range
	int* M = (int*)calloc(sizeof(int), size);
	M[0] = a[0];
	int len = 1;
	int i;
	for(i = 1; i < size; ++i)
	{
		if(a[i] > M[len - 1])
		{
			M[len++] = a[i];
		}
		else
		{
			int pos = binary_search(M, len, a[i]);
			M[pos] = a[i];
		}
	}
	free(M);
	return len;
}

int main()
{
	int size;
	scanf("%d", &size);
	int *sequence = (int*)malloc(sizeof(int) * size);
	int i;
	for(i = 0; i < size; ++i)
		scanf("%d", &sequence[i]);
	printf("%d\n", LIS(sequence, size) );
	free(sequence);
	return 0;
}
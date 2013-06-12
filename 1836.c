#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define EPSILON 0.00001
 
int binary_search(float *arr, int size, float x)
{
	int left = 0;
	int right = size - 1;
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if(fabs(arr[mid] - x) < EPSILON)
			return mid;
		else if(arr[mid] < x)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return left;
}

int LIS(float* a, int size, int* V)
{
	//M[j] stores the value of the smallest value a[k] such that there is an increasing subsequence of length j ending at a[k] on the range
	//V[j] stores the length of the longest subsequence ending at a[j]
	float* M = (float*)malloc(sizeof(int) * size);
	M[0] = a[0];
	V[0] = 1;
	int len = 1;
	int i;
	for(i = 1; i < size; ++i)
	{
		//Comparing for greater/smaller is not really a problem unless the float numbers are right at the edge of the float/double precision limit.
		if(a[i] > M[len - 1])
		{
			M[len++] = a[i];
			V[i] = len;
		}
		else
		{
			int pos = binary_search(M, len, a[i]);
			M[pos] = a[i];
			V[i] = pos + 1;
		}
	}
	free(M);
	return len;
}

int main()
{
	int size;
 	scanf("%d", &size);
 	float * heights = (float*)malloc(size * sizeof(float));
 
 	int i;
 	for(i = 0; i < size; ++i)
 	{
 		scanf("%f", &heights[i]);
 	}
 
	int * asc = (int*)malloc(size * sizeof(int));
	LIS(heights, size, asc);

	float * reverse_heights= (float*)malloc(size * sizeof(float));

	for(i = 0; i < size; ++i)
	{
		reverse_heights[i] = heights[size - 1 - i];
	}

	int * desc = (int*)malloc(size * sizeof(int));
	LIS(reverse_heights, size, desc);

	//for(i = 0; i < size; ++i)
	//{
	//	printf("%d\t", asc[i]);
	//}
	//printf("\n");
	//for(i = 0; i < size; ++i)
	//{
	//	printf("%d\t", desc[i]);
	//}
	//printf("\n");

	int max = INT_MIN;
	int j;
	for(i = 0; i < size - 1; ++i)
	{
		for(j = size - 2 - i; j >= 0; --j)
		{
			if(asc[i] + desc[j] > max)
			{
				max = asc[i] + desc[j];
			}
		}
	}

 	printf("%d\n", size - max);

	free(asc);
	free(desc);
	free(heights);
	free(reverse_heights);
 	return 0;
 }

#include <stdlib.h>
#include <stdio.h>

struct stick{
	int length;
	int weight;
};
typedef struct stick STICK;

int compar(const void *x, const void *y)
{
	STICK *a = (STICK*)x;
	STICK *b = (STICK*)y;
	if(a->length != b->length)
		return a->length - b->length;
	else
		return a->weight - b->weight;
}

//return the index of the first element that's not less than the target element
int binary_search(int * array, int size, int key)
{
	int low  = 0;
	int high = size - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2; // Or a fancy way to avoid int overflow
		// use "<=" if we want to find the the first element that's greater than the target element
		if(array[mid] < key)
			low  = mid + 1;
		else
			high = mid - 1;
	}
	return low ;
}

//Dilworth's theorem: in any finite partially ordered set, the maximum number of elements in any antichain 
//equals the minimum number of chains in any partition of the set into chains.
//according to this theorem, to solve this problem, we need get the maximum number of elements in any antichain
int longest_antichain(STICK* sticks, int size)
{
	int * max_vector = (int*)malloc(sizeof(int) * size);
	max_vector[0] = sticks[size - 1].weight;
	int inc_length = 1;
	int i;
	for(i = size - 2; i >= 0; --i)
	{
		if(sticks[i].weight > max_vector[inc_length - 1])
		{
			max_vector[inc_length++] = sticks[i].weight;
		}
		else
		{
			// or we can do the binary search by calling lower_bound() or upper_bound() provided by stl
			max_vector[binary_search(max_vector, inc_length, sticks[i].weight)] = sticks[i].weight;
		}
	}

	free(max_vector);
	return inc_length;
}

void process_input(void)
{
	int cases;
	scanf("%d", &cases);
	int i, j; 
	for(i = 0; i < cases; ++i)
	{
		int n_sticks;
		scanf("%d", &n_sticks);
		STICK* sticks = (STICK*)malloc(sizeof(STICK) * n_sticks);
		for(j = 0; j < n_sticks; ++j)
		{
			scanf("%d", &sticks[j].length);
			scanf("%d", &sticks[j].weight);
		}
		qsort(sticks, n_sticks, sizeof(STICK), compar);
		int setup_time = longest_antichain(sticks, n_sticks);
		free(sticks);
		printf("%d\n", setup_time);
	}

}

int main()
{
	process_input();
	return 0;
}
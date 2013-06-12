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

//Dilworth's theorem: in any finite partially ordered set, the maximum number of elements in any antichain 
//equals the minimum number of chains in any partition of the set into chains.
//according to this theorem, to solve this problem, we need get the maximun number of elements in any antichain
int longest_antichain(STICK* sticks, int length)
{
	int *value = (int*)malloc(sizeof(int) * length);
	int i, j;
	for(i = 0; i < length; ++i)
		value[i] = 1;
	for(i = 1; i < length; ++i)
	{
		for(j = 0; j < i; ++j) 
		{
			if(sticks[j].weight > sticks[i].weight)
			{
				int temp = value[j] + 1;
				if(temp > value[i])
					value[i] = temp;
			}
		}
	}

	int max = value[0];
	for(i = 0; i < length; ++i)
	{
		if(value[i] > max)
			max = value[i];
	}

	return max;
}

process_input()
{
	int cases;
	scanf("%d", &cases);
	int i, j; 
	for(i = 0; i < cases; ++i)
	{
		int pairs;
		scanf("%d", &pairs);
		STICK* sticks = (STICK*)malloc(sizeof(STICK) * pairs);
		for(j = 0; j < pairs; ++j)
		{
			scanf("%d", &sticks[j].length);
			scanf("%d", &sticks[j].weight);
		}
		qsort(sticks, pairs, sizeof(STICK), compar);
		int setup_count = longest_antichain(sticks, pairs);
		free(sticks);
		printf("%d\n", setup_count);
	}

}
int main()
{
	process_input();
	return 0;
}

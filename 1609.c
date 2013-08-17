#include <stdlib.h>
#include <stdio.h>

struct block{
	int l;
	int m;
};
typedef struct block BLOCK;

int compar(const void *x, const void *y)
{
	BLOCK *a = (BLOCK*)x;
	BLOCK *b = (BLOCK*)y;
	if(a->l != b->l)
		return a->l - b->l;
	else
		return a->m - b->m;
}

// the array isn't strictly increasing.
// return the index of the first element that's greater than the target element
int binary_search(int * array, int size, int key)
{
	int low  = 0;
	int high = size - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2; // Or a fancy way to avoid int overflow
		if(array[mid] <= key)
			low  = mid + 1;
		else
			high = mid - 1;
	}
	return low ;
}

int lis(BLOCK* blocks, int size)
{
	int * max_vector = (int*)malloc(sizeof(int) * size);
	max_vector[0] = blocks[0].m;
	int length = 1;
	int i;
	for(i = 1; i < size; ++i)
	{
		if(blocks[i].m >= max_vector[length - 1])
		{
			max_vector[length++] = blocks[i].m;
		}
		else
		{
			// or we can do the binary search by calling lower_bound() or upper_bound() provided by stl
			max_vector[binary_search(max_vector, length, blocks[i].m)] = blocks[i].m;
		}
	}

	free(max_vector);
	return length;
}

int main()
{
	int n_blocks;
	while(scanf("%d", &n_blocks), n_blocks != 0)
	{
		BLOCK* blocks= (BLOCK*)malloc(sizeof(BLOCK) * n_blocks);
		int i;
		for(i = 0; i < n_blocks; ++i)
		{
			scanf("%d", &blocks[i].l);
			scanf("%d", &blocks[i].m);
		}
		qsort(blocks, n_blocks, sizeof(BLOCK), compar);
		printf("%d\n", lis(blocks, n_blocks) );
		free(blocks);
	}
	printf("*");
	return 0;
}

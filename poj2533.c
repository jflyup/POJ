#include <stdio.h>
#include <stdlib.h>

int LOS(int* a, int size)
{
	int* value_arr = (int*)calloc(sizeof(int), size);

	int i, j;
	for(i = 1; i < size; ++i)
	{
		for(j = i - 1; j >= 0 ; --j)
			if(a[i] > a[j])
			{
				int temp = value_arr[j] + 1;
				if(temp > value_arr[i])
					value_arr[i] = temp;
			}

	}
	int result = value_arr[0];
	for(i = 1; i < size; ++i)
		if(value_arr[i] > result)
			result = value_arr[i];
	free(value_arr);
	return result + 1;
}

int main()
{
	int size;
	scanf("%d", &size);
	int *sequence = (int*)malloc(sizeof(int) * size);
	int i;
	for(i = 0; i < size; ++i)
		scanf("%d", &sequence[i]);
	printf("%d\n", LOS(sequence, size) );
	free(sequence);
	return 0;
}

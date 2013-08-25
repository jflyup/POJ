#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int g_inversions;

void reverse(char* arr, int size)
{
	int i;
	for(i = 0; i < size / 2; ++i)
	{
		int temp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = temp;
	}
}

void rotate(char* arr, int middle, int last)
{
	reverse(arr, middle);
	reverse(arr + middle, last);
	reverse(arr, middle + last);
}

//in-place merge.
void merge(char *a, int s, int m, int e)
{
	int p1 = s;
	int p2 = m + 1;

	while(p1 < p2 && p2 < e + 1)
	{
		while(p1 < p2 && a[p1] <= a[p2])
		{
			p1++;
		}
		int index = p2;
		while(a[p1] > a[p2] && p2 < e + 1)
		{
			p2++;
		}

		g_inversions += (index - p1) * (p2 - index);
		rotate(a + p1, index - p1, p2 - index);
		p1 += p2 - index;
	}
}

void merge_sort(char *a, int s, int e)
{
	if(s < e)
	{
		int mid = (s + e) / 2;
		merge_sort(a, s, mid);
		merge_sort(a, mid + 1, e);
		merge(a, s, mid, e);
	}
}

int calc_inversions(const char* sequence)
{
	//the original sequence will be modified after the mergesort, so duplicate the sequence
	int length = strlen(sequence);
	char * array = (char*)malloc(sizeof(char) * length + 1);
	strcpy(array, sequence);

	g_inversions = 0;
	merge_sort(array, 0, length - 1);

	free(array);
	return g_inversions;
}

int comp(const void* a, const void* b)
{

	return calc_inversions(*(const char **) a) - calc_inversions(*(const char **) b);
}

int main()
{
	int length, n_strings;
	scanf("%d %d", &length, &n_strings);
	//allocate an array of pointers.
	char **strings = (char **)malloc(sizeof(char *) * n_strings);
	int i;
	for(i = 0; i < n_strings; ++i)
	{
		strings[i] = (char *)malloc(sizeof(char) * (length + 1) );
	}

	for(i = 0; i < n_strings; ++i)
		scanf("%s", strings[i]);//A terminating null character is automatically added at the end of the stored sequence

	//is the qsort() stable? But it works.
	qsort(strings, n_strings, sizeof(char*), comp);

	for(i = 0; i < n_strings; ++i)
		printf("%s\n", strings[i]);
	for(i = 0; i < n_strings; ++i)
	{
		free(strings[i]);
	}
	free(strings);
	return 0;
}

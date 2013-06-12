#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calc_inversions(const char* sequence)
{
	int length = strlen(sequence);
	int inversions = 0;
	int i, j;
	for(i = 0; i < length; ++i)
	{
		if(sequence[i] != 'A')
		{
			for(j = i + 1; j < length; ++j)
				if(sequence[i] > sequence[j])
					inversions++;
		}
	}
	return inversions;
}

int comp(const void* a, const void* b)
{
	return calc_inversions((const char *) a) - calc_inversions((const char *) b);
}

int main()
{
	char sequences[100][51];
	int length, nr_of_strings;
	scanf("%d %d", &length, &nr_of_strings);
	int i;
	for(i = 0; i < nr_of_strings; ++i)
		scanf("%s", &sequences[i]);
	//is the qsort() stable?
	qsort(sequences, nr_of_strings, sizeof(char[51]), comp);
	for(i = 0; i < nr_of_strings; ++i)
		printf("%s\n", sequences[i]);
}
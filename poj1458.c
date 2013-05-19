#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

int max(int m, int n)
{
	return m > n ? m : n;
}

int lcs(const char* a, const char* b)
{
	int row = strlen(a)+ 1;
	int column = strlen(b) + 1;
	int **matrix = (int**)malloc(sizeof(int*) * row);
	int i, j;
	for(i = 0; i < row; ++i)
		matrix[i] = (int*)calloc(sizeof(int), column);

	for(i = 1; i < row; ++i)
	{
		for(j = 1; j < column; ++j)
		{
			if(a[i - 1] == b[j - 1])
				matrix[i][j] = matrix[i -1][j - 1] + 1;
			else
				matrix[i][j] = max(matrix[i][j - 1], matrix[i - 1][j]);
		}
	}
	int result = matrix[row - 1][column -1];
	for(i = 0; i < row; ++i)
		free(matrix[i]);
	free(matrix);
	return result;
}

int main()
{
	char buf1[MAX_LENGTH], buf2[MAX_LENGTH];
	while(scanf("%s %s", buf1, buf2) != EOF)
	{
		printf("%d\n", lcs(buf1, buf2) );
	}
	return 0;
}

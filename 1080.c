#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int value_table[5][5] = {
	{5,-1,-2,-1,-3},
	{-1,5,-3,-2,-4},
	{-2,-3,5,-2,-2},
	{-1,-2,-2,5,-1},
	{-3,-4,-2,-1,0}
};

int string2arr(char* arr)
{
	int size = strlen(arr);
	int i;
	for(i = 0; i < size; ++i)
	{
		switch(arr[i])
		{
		case 'A':
			arr[i] = 0;
			break;
		case 'C':
			arr[i] = 1;
			break;
		case 'G':
			arr[i] = 2;
			break;
		case 'T':
			arr[i] = 3;
			break;
		default:
			return -1;
		}
	}
	return 0;
};

//maximum of 3 numbers
int max(int a, int b, int c)
{
	int max = (a < b) ? b : a;
	return (max < c) ? c : max;
}

int align(char* sequence_A, int size_A, char* sequence_B, int size_B)
{

	//O(size_A * size_B) space is lavish, but it's simpler like that
	//in this case, note that the 2-d array don't allocate a contiguous region of memory
	int **score = (int**)malloc(sizeof(int*) * (size_B + 1));
	int i;
	for(i = 0; i < size_B + 1; ++i)
	{
		score[i] = (int*)malloc(sizeof(int) * (size_A + 1));
		memset(score[i], 0, sizeof(int) * (size_A + 1));
	}
	
	//initial status

	//sequence_A matches spaces
	for(i = 1; i <= size_A; ++i)
	{
		for(int j = 0; j < i; ++j)
		{
			score[0][i] += value_table[sequence_A[j]][4];
		}
	}
	//sequence_B matches spaces
	for(i = 1; i <= size_B; ++i)
	{
		for(int j = 0; j < i; ++j)
		{
			score[i][0] += value_table[sequence_B[j]][4];
		}
	}

	for(i = 1; i <= size_B; ++i)
	{
		for(int j = 1; j <= size_A; ++j)
		{
			score[i][j] = max(score[i - 1][j - 1] + value_table[sequence_B[i - 1]][sequence_A[j-1]], 
				score[i - 1][j] + value_table[sequence_B[i - 1]][4], score[i][j - 1] + value_table[sequence_A[j - 1]][4]);
		}
	}

	int reslut =  score[size_B][size_A];
	//free the 2D matrix
	for(i = 0; i < size_B + 1; ++i)
		free(score[i]);
	free(score);

	return reslut;
}

void process_input()
{
	int cases;
	scanf("%d", &cases);
	int i; //C99 allow to declare variables in the middle of a block, C89 do not
	for(i = 0; i < cases; ++i)
	{
		int length_A, length_B;
		scanf("%d", &length_A);
		char sequence_A[101];
		scanf("%s", sequence_A);

		scanf("%d", &length_B);
		char sequence_B[101];
		scanf("%s", sequence_B);
		
		string2arr(sequence_A);
		string2arr(sequence_B);
		int result = align(sequence_A, length_A, sequence_B, length_B);

		printf("%d\n", result);
	}
}
int main()
{
	process_input();
	return 0;
};




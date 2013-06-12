#include <stdio.h>
#include <string.h>

char A[201], B[201], C[401];

int fun(int a, int b)
{
	int auxiliary_space[201][201] = {0};
	auxiliary_space[0][0] = 1;
	int i, j;
	for(i = 0; i <= a; ++i)
		for(j = 0; j <= b; ++j)
		{
			if(i > 0 && C[i + j - 1] == A[i - 1] && auxiliary_space[i - 1][j] == 1)
				auxiliary_space[i][j] = 1;
			if(j > 0 && C[i + j - 1] == B[j - 1] && auxiliary_space[i][j - 1] == 1)
				auxiliary_space[i][j] = 1;
		}
	return auxiliary_space[a][b];
}

int main()
{
	int test_cases;
	scanf("%d", &test_cases);
	int i;
	for(i = 0; i < test_cases; ++i)
	{
		scanf("%s %s %s", A, B, C);
		printf("Data set %d: ", i + 1);
		fun(strlen(A), strlen(B) ) == 1 ? printf("yes\n") : printf("no\n");
	}
	return 0;
};
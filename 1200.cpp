#include <cstdio>
#include <cstring>
#include <bitset>

#define NMAX 20000000

char str[NMAX];
std::bitset<NMAX> mark;
char value[128] = {0};

int main()
{
	int substr_len;
	//use the number of unique characters as number base
	int base;
	scanf("%d %d", &substr_len, &base);
	scanf("%s", str);
	int length = strlen(str);

	if(length < substr_len)
	{
		printf("0\n");
		return 0;
	}

	int unique_character = 0;
	int index = 0;
	while(unique_character < base)
	{
		if(value[str[index]] == 0)
			value[str[index]] = unique_character++;
		index++;
	}

	long rolling_hash = 0;
	for(int i = 0; i < substr_len; ++i)
		rolling_hash =  rolling_hash * base + value[str[i]];
	mark[rolling_hash] = 1;

	// Calculate hash value for next window of text: Remove leading digit, add trailing digit
	// hash(s[i+1 ... i+m] ) = base *(hash(s[i .. s+i-1]) – s[i] * (b^(m-1) ) )+ s[i + m] 

	//h = pow(base, substr_len - 1)
	int h = 1;
	for (int i = 0; i < substr_len - 1; i++)
		h *=  base; //int overflow?

	for(int i = 0; i < length - substr_len; i++)
	{
		rolling_hash = base *(rolling_hash - value[str[i]] * h) + value[str[i + substr_len]];
		mark[rolling_hash] = 1;
	}

	printf("%ld\n", mark.count());
	return 0;
};

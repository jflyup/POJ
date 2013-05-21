#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

//Dynamic Programming Algorithm for Edit-Distance is too slow for this scenario
/*int edit_distance(std::string & a, std::string & b)
{
	int row = a.size() + 1;
	int column = b.size() + 1;
	int **matrix = (int**)malloc(sizeof(int*) * row);
	for(int i = 0; i < row; ++i)
		matrix[i] = (int*)calloc(sizeof(int), column);

	for(int i = 1; i < row; ++i)
		matrix[i][0] = 1;
	for(int i = 1; i < column; ++i)
		matrix[0][i] = 1;
	for(int i = 1; i < row; ++i)
		for(int j = 1; j < column; ++j)
		{
			if(a[i - 1] == b[j - 1])
				matrix[i][j] = matrix[i -1][j - 1];
			else
				matrix[i][j] = std::min(matrix[i][j - 1] + 1, std::min(matrix[i - 1][j] + 1, matrix[i - 1][j - 1] + 1) );
		}
	int result = matrix[row - 1][column -1];
	for(int i = 0; i < row; ++i)
		free(matrix[i]);
	free(matrix);
	return result;
}*/

int similarity(const char * a, const char * b)
{
	int la = strlen(a);
	int lb = strlen(b);
	while(*a == *b )
	{
		a++;
		b++;
	}

	if(la == lb)
	{
		return strcmp(a + 1, b + 1);
	}
	else if(la < lb)
	{
		return strcmp(a, b + 1);
	}
	else
	{
		return strcmp(a + 1, b);
	}
}

struct ITEM
{
	bool operator<(const ITEM & rhs) const {return m_word.size() < rhs.m_word.size();}
	std::string m_word;
	int m_sequence_num;
};

bool comp(const ITEM & a, const ITEM & b)
{
	return a.m_sequence_num < b.m_sequence_num;
}

int main()
{
	//if the compiler supports c++ 2011 standard, std::unordered_set container is perfect for this scenario due to  
	// the requirement that the replacements should be written in the order of their appearance in the dictionary
	std::vector<ITEM> dict;
	int sequence;
	//A terminating null character is automatically added at the end of the stored sequence.
	char word[16];
	while(1)
	{
		scanf("%s", word);
		sequence++;
		if(word[0] != '#')
		{
			ITEM tmp_item;
			tmp_item.m_word = word;
			tmp_item.m_sequence_num = sequence;
			dict.push_back(tmp_item);
		}
		else
			break;
	}

	std::sort(dict.begin(), dict.end());
	while(1)
	{
		scanf("%s", word);
		if(word[0] != '#')
		{
			printf("%s", word);
			bool is_correct = false;
			ITEM equal_item;
			equal_item.m_word = word;
			std::pair<std::vector<ITEM>::iterator,std::vector<ITEM>::iterator> bounds = std::equal_range(dict.begin(), dict.end(), equal_item);
			for(std::vector<ITEM>::iterator equal = bounds.first; equal != bounds.second; ++equal)
			{
				if(equal->m_word == word )
				{
					printf(" is correct");
					is_correct = true;
					break;
				}
			}
			if(!is_correct)
			{
				printf(":");
				std::string lower_str(strlen(word) -1, 'x');
				std::string upper_str(strlen(word) +1, 'x');
				ITEM lower_item, upper_item;
				lower_item.m_word = lower_str;
				upper_item.m_word = upper_str;
				std::vector<ITEM>::iterator low, up;
				low = std::lower_bound(dict.begin(), dict.end(), lower_item);
				up = std::upper_bound(dict.begin(), dict.end(), upper_item);

				std::vector<ITEM> similar_words;
				for(low; low != up; ++low)
				{
					if(!similarity(low->m_word.c_str(), word) )
						similar_words.push_back(*low);
				}
				std::sort(similar_words.begin(), similar_words.end(), comp);
				for(int i = 0; i < similar_words.size(); ++i)
					printf(" %s", similar_words[i].m_word.c_str());
			}
			printf("\n");
		}
		else
			break;
	}
	return 0;
}

#include <cstdio>
#include <vector>
#include <string>
#include <set>
#include <cstring>
#include <algorithm>

int edit_distance(std::string & a, std::string & b)
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
}

bool similarity(std::string a, std::string b)
{
	int diff = 0;
	if(a.size() == b.size())
	{
		for(int i = 0; i < a.size(); ++i)
		{
			if(a[i] != b[i])
				diff++;
			if(diff > 1)
				return false;
		}
	}
	else
	{
		if(a.size() > b.size() )
			swap(a, b);
		if(!strstr(a.c_str(), b.c_str() ) )
			return false;
	}
	return true;
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
	//std::set<std::string> dict_set;
	std::vector<ITEM> dict;
	int sequence;
	while(1)
	{
		char word[16];
		scanf("%s", word);
		sequence++;
		if(word[0] != '#')
		{
			//dict_set.insert(word);
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
		char word[16];
		scanf("%s", word);
		if(word[0] != '#')
		{
			printf("%s", word);
			//if(dict_set.find(word) != dict_set.end() )
				//printf(" is correct");
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
					std::string temp_str(word);
					if(similarity(low->m_word, temp_str) )
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

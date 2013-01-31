#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>

std::string big_multiply(const char* a, const char* b)
{
	size_t len_of_a = strlen(a);
	size_t len_of_b = strlen(b);
	int i, j;
	std::vector < int > result(len_of_a + len_of_b, 0);

	for(i = len_of_a - 1; i >= 0; --i)
	{
		for(j = len_of_b - 1; j >= 0; --j)
		{
			result[i + j + 1] += ( (a[i] - '0') * (b[j] - '0') );
		}

	}

 	for(i = result.size() - 1; i > 0; --i)
	{
		int temp = result[i];
		result[i] = temp % 10;
		result[i - 1] += temp / 10;
	}

	//find the position of the first nonzero num in the vector
	unsigned int nonzero_pos;
	for(nonzero_pos = 0; nonzero_pos < result.size(); ++nonzero_pos)
	{
		if(result[nonzero_pos] != 0)
			break;
	}
	std::string str_result;
	for(; nonzero_pos < result.size(); ++nonzero_pos)
	{
		str_result.push_back(result[nonzero_pos] + '0');
	}
	return str_result;
}


std::string big_pow(std::string num, int power)
{
	std::string temp = "1";
	while(power > 1)
	{
		if(power % 2 == 1)
		{
			temp = big_multiply(num.c_str(), temp.c_str());
		}

		num = big_multiply(num.c_str(), num.c_str() );
		power = power / 2;
	}
	return big_multiply(temp.c_str(), num.c_str());
}

//remove the dot. return the offset of the dot, offset is counted from the rightmost
int remove_dot(char* str)
{
	char *src, *dst;
	int offset = 0;
	int count = 0;
	for (src = dst = str; *src != '\0'; src++)
	{
		*dst = *src;
		if(*dst != '.')
		{
			dst++;
			count++;
		}
		else
		{
			offset = count;
		}
	}
	*dst = '\0';

	return count - offset;
}

int main()
{
	char num[8];
	int power;
	while( (scanf("%s%d", num, &power) ) == 2)
	{
		int dot_pos = remove_dot(num);
		std::string str_result = big_pow(num, power);
		
		if(str_result.size() < dot_pos * power)
		{
			//add zero(s) before the dot
			str_result.insert(str_result.begin(), dot_pos * power -str_result.size(), '0');
		}

		if(str_result.size() == dot_pos * power)
		{
			str_result.insert(str_result.begin(), '.');
		}
		else
		{
			str_result.insert(str_result.end() - (dot_pos * power), '.');
		}
		
		//find the position of '.'
		std::string::iterator it_dot = str_result.begin();
		while(*it_dot != '.')
		{
			it_dot++;
		}

		//remove insignificant trailing zeros
		for(std::string::iterator iter = str_result.end() - 1; iter >= it_dot; --iter)
		{
			if (*iter != '0')
			{
				if(*iter == '.') //if the result is an integer
					str_result.erase(iter, str_result.end());
				else
					str_result.erase(iter + 1, str_result.end());
				break;
			}
			
		}

		printf("%s\n", str_result.c_str());
	}
	return 0;
}
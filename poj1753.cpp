#include <stdio.h>
#include <bitset>
#include <queue>

#define N 4
std::bitset< (2 << 15) > status_set;
unsigned long path[2 << 15] = {0};

short move[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
//short board[N][N] = {{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {0, 0, 1, 1}};

//short board[N][N] = {{1, 0, 0, 1}, {1, 1, 0 ,1}, {1, 0, 0, 1}, {1, 0, 0, 0}};

std::queue < unsigned long> stat_queue;

void load_board(void)
{
	int i, j;
	char ch;
	std::bitset< 16 > stat;
	std::string str_stat;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j <= N; ++j)
		{
			ch = getchar();
			if(ch != '\n')
				str_stat += ch;
			
		}
	}
	for(i = 0; i < str_stat.size(); ++i)
	{
		if(str_stat[i] == 'b')
			stat.set(i);
	}
	unsigned long s = stat.to_ulong();
	stat_queue.push(s);
	status_set.set(s);
	return;
}

bool is_legal_position(int xPos, int yPos)
{
	return (xPos >= 0 && xPos < N  && yPos >= 0 && yPos < N);
}

bool finished(unsigned long stat)
{
	return (stat == 0 || stat == 0xffff);
}

int flip()
{
	int loop_count = 0;

	while(!stat_queue.empty())
	{
		loop_count++;
		unsigned long stat = stat_queue.front();
		stat_queue.pop();
		if(finished(stat))
		{
			int steps = 0;
			while(path[stat] != 0)
			{
				++steps;
				stat = path[stat];
			}
			printf("%d", steps);
			return 0;
		}
		int xPos, yPos;
		for(xPos = 0; xPos < N; ++xPos)
		{
			for(yPos = 0; yPos < N; ++yPos)
			{
				int i;
				std::bitset < 16 > next_stat(stat);
				for(i = 0; i < 5; ++i)
				{
					if(is_legal_position(xPos + move[i][0], yPos + move[i][1]) )
					{
						next_stat.flip((xPos + move[i][0]) * N + (yPos + move[i][1]) );
					}

				}

				//printf("%d\n", next_stat.to_ulong());
				unsigned long num_status = next_stat.to_ulong();
				if(!status_set.test(num_status))
				{
					status_set.set(num_status);
					path[num_status] = stat;
					stat_queue.push(num_status);
				}
			}
		}
	}
	printf("Impossible");
	return -1;
}

int main()
{
	load_board();
	flip();

	return 0;
}
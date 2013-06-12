#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//find the positon of the minimum unused vertext in the array
int min_pos(int * arr, char* visited_mark, int size)
{
	int min = INT_MAX;
	int i, pos;
	for(i = 0; i < size; ++i)
	{
		if(arr[i] <= min && visited_mark[i] == 0)
		{
			min = arr[i];
			pos = i;
		}
	}
	return pos;
}

int max(int * arr, int size)
{
	int max = arr[0];
	int i;
	for(i = 1; i < size; ++i)
	{
		if(arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

int completed(char* arr, int size)
{
	int i;
	for(i = 0; i < size; ++i)
	{
		if(arr[i] == 0)
			return 0;
	}
	return 1;
}

void Dijkstra(int ** matrix, int vertexs, int source_vertex, int* max_edge)
{
	int * distance = (int*)malloc(sizeof(int) * vertexs);
	int k;
	for(k = 0; k < vertexs; ++k)
		distance[k] = INT_MAX;
	char* visited_mark = (char*)malloc(sizeof(char) * vertexs);
	memset(visited_mark, 0, sizeof(char) * vertexs);
	distance[source_vertex] = 0;

	while(!completed(visited_mark, vertexs))
	{
		int start_vertex = min_pos(distance, visited_mark, vertexs);
		visited_mark[start_vertex] = 1;
		int i;
		for(i = 0; i < vertexs; ++i)
		{
			if(i != source_vertex && visited_mark[i] == 0)
			{
				if(matrix[start_vertex][i] != INT_MAX)
				{
					if(distance[start_vertex] + matrix[start_vertex][i] < distance[i])
					{
						distance[i] = distance[start_vertex] + matrix[start_vertex][i];
					}
				}
			}
		}
	}
	*max_edge = max(distance, vertexs);
}

int shortest_way(int ** matrix, int vertexs, int * start)
{
	int i;
	int min_time = INT_MAX;
	for(i = 0; i < vertexs; ++i)
	{
		int max_edge = 0;
		Dijkstra(matrix, vertexs, i, &max_edge);
		if(max_edge < min_time)
		{
			min_time = max_edge;
			*start = i;
		}
	}
	return min_time;
}

void process_input()
{
	int total_brokers;
	while(scanf("%d", &total_brokers) != EOF)
	{
		if(total_brokers != 0)
		{
			int ** brokers_matrix = (int**)malloc(sizeof(int*) * total_brokers );
			int i, j;
			for(i = 0; i < total_brokers; ++i)
				brokers_matrix[i] = (int*)malloc(total_brokers * sizeof(int));
			for(i = 0; i < total_brokers; ++i)
				for(j = 0; j < total_brokers; ++j)
				{
					brokers_matrix[i][j] = INT_MAX;
				}
			for(i = 0; i < total_brokers; ++i)
			{
				int pairs;
				scanf("%d", &pairs);
				int j, borker_num, time;
				for(j = 0; j < pairs; ++j)
				{
					scanf("%d", &borker_num);
					scanf("%d", &time);
					brokers_matrix[i][borker_num - 1] = time;
				}
			}
			int start_point = -1;
			int min_time = shortest_way(brokers_matrix, total_brokers, &start_point);
			if(min_time == INT_MAX)
				printf("disjoint\n");
			else
				printf("%d %d\n", start_point + 1, min_time);
		}
		else
		{
			return;
		}
	}
}

int main()
{
	process_input();
	return 0;
}

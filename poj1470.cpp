#include <cstdio>
#include <cstdlib>
#include <climits>
#include <map>
#include <vector>
#define MAX_NODES 10000
std::vector<int> euler_tour;
std::vector<int> depth_tour;
std::multimap<int, int> tree;

void dfs(int root, int depth)
{
	std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> ret;
	ret = tree.equal_range(root);
	for(std::multimap<int,int>::iterator it=ret.first; it!=ret.second; ++it)
	{	
		euler_tour.push_back(it->second);
		depth++;
		depth_tour.push_back(depth);
		dfs(it->second, depth);
		depth--;
		euler_tour.push_back(root);
		depth_tour.push_back(depth);
	}
	return;
}

//proprocess for RMQ
{
	int i, j;
}

//reduction from LCA to RMQ
int nearest_common_ancestor(int node1, int node2)
{
	// index of the first occurrence of node i in depth_tour[]
	int index_of_node1, index_of_node2;
	int i;
	for(i = 0; i < euler_tour.size(); ++i)
	{
		if(euler_tour[i] == (node1))
		{
			index_of_node1 = i;
			break;
		}
	}
	for(i = 0; i < euler_tour.size(); ++i)
	{
		if(euler_tour[i] == node2)
		{
			index_of_node2 = i;
			break;
		}
	}

	if(index_node1 > index_node2)
	{
		index_node1 ^= index_node2;
		index_node2 ^= index_node1;
		index_node1 ^= index_node2;
	}

	int min = INT_MAX;
	int pos;
	for(i = index_node1; i <= index_node2; i++)
	{
		if(depth_tour[i] < min)
		{
			min = depth_tour[i];
			pos = i;
		}
	}

	return euler_tour[pos] + 1;
}

void process_input(void)
{
	int nr_of_vertices;
	scanf("%d", &nr_of_vertices);

	int i;
	for(i = 0; i < nr_of_vertices; ++i)
	{
		int parent, nr_of_child;
		scanf("%d:(%d)", &parent, &nr_of_child);
		for(i = 0; i < nr_of_child; ++i)
		{
			int child;
			scanf("%d", &child);
			tree.insert(std::pair<int, int>(parent, child));
		}
	}
		euler_tour.clear();
		depth_tour.clear();
		//start from root
		euler_tour.push_back(root);
		depth_tour.push_back(0);
		dfs(root, 0);
		int cases;
		scanf("%d", &cases);
		for(i = 0; i < cases; ++i)
		{
		int node1, node2;
		scanf("(%d %d)", &node1, &node2);
		nearest_common_ancestor(node1, node2);
		}
		

		printf("%d\n", nearest_common_ancestor(node1, node2) );
	}
	return;
}

int main()
{
	process_input();
	return 0;
};

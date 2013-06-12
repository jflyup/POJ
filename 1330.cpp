#include <cstdio>
#include <cstdlib>
#include <climits>
#include <map>
#include <vector>
#define MAX_NODES 10000
std::vector<int> euler_tour;
std::vector<int> depth_tour;
std::multimap<int, int> tree;
//std::vector< std::bitset<MAX_NODES> > bit_matrix;

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

//only one query, RMQ algorithm has no advantage
int nearest_common_ancestor(int node1, int node2)
{
	// index of the first occurrence of node i in depth_tour[]
	int index_node1, index_node2;
	int i;
	for(i = 0; i < euler_tour.size(); ++i)
	{
		if(euler_tour[i] == (node1 - 1))
		{
			index_node1 = i;
			break;
		}
	}
	for(i = 0; i < euler_tour.size(); ++i)
	{
		if(euler_tour[i] == (node2 - 1))
		{
			index_node2 = i;
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
	int cases;
	scanf("%d", &cases);
	for(int j = 0; j < cases; ++j)
	{
		int nodes;
		scanf("%d", &nodes);
// 		unsigned char ** matrix = (unsigned char **)malloc(sizeof(unsigned char *) * nodes);
// 		int i;
// 		for(i = 0; i < nodes; ++i)
// 		{
// 			matrix[i] = (unsigned char*)calloc(nodes, sizeof(unsigned char));
// 		}
		int * mark = (int*)calloc(nodes, sizeof(int));

// 		bit_matrix.clear();
// 		int i;
// 		for(i = 0; i < nodes; ++i)
// 		{
// 			std::bitset<MAX_NODES> bit_array;
// 			bit_matrix.push_back(bit_array);
// 		}
		tree.clear();
		int i;
		for(i = 0; i < nodes - 1; ++i)
		{
			int parent, child;
			scanf("%d %d", &parent, &child);
			tree.insert(std::pair<int, int>(parent -1, child -1));
			//bit_matrix[parent - 1].set(child -1);
			mark[child - 1] = 1;
		}
		int node1, node2;
		scanf("%d %d", &node1, &node2);

		//find root node
		int root;
		for(i = 0; i < nodes; ++i)
		{
			if(mark[i] == 0)
			{
				root = i;
				break;
			}
		}
		
		euler_tour.clear();
		depth_tour.clear();
		//begin with root
		euler_tour.push_back(root);
		depth_tour.push_back(0);
		dfs(root, 0);

		free(mark);
		printf("%d\n", nearest_common_ancestor(node1, node2) );
	}
	return;
}

int main()
{
	process_input();
	return 0;
};
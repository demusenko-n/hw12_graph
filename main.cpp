#include <iostream>
#include <fstream>

#include "graph_stream_reader.h"


int main()
{
	std::ifstream fs("input.txt");

	graph_stream_reader reader(fs);
	graph::oriented_graph graph = reader.read();

	std::cout << std::boolalpha << graph.bfs(0, 9) << std::endl;
	std::cout << std::boolalpha << graph.dfs(0, 9) << std::endl;

	std::vector<size_t> vec = graph.dijkstra(0);

	for (size_t val : vec)
	{
		std::cout << val << std::endl;
	}

	return 0;
}
#include "oriented_graph.h"
#include <queue>
#include <stack>
//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

graph::oriented_graph::oriented_graph(int nodes_number)
{
	nodes_count_ = nodes_number;
}

graph::oriented_graph::oriented_graph()
{
	nodes_count_ = 0;
}

void graph::oriented_graph::add_arc(const arc& arc)
{
	nodes_count_ = std::max(std::max(nodes_count_, 1 + arc.end), 1 + arc.start);

	arcs_.push_back(arc);
}

void graph::oriented_graph::add_node()
{
	++nodes_count_;
}

size_t graph::oriented_graph::nodes_count() const
{
	return nodes_count_;
}

size_t graph::oriented_graph::arcs_count() const
{
	return arcs_.size();
}

bool graph::oriented_graph::bfs(size_t start, size_t goal) const
{
	if (start >= nodes_count_ || goal >= nodes_count_ || start < 0 || goal < 0)
	{
		return false;
	}

	const auto visited = new bool[nodes_count_];
	for (size_t i = 0; i < nodes_count_; ++i)
	{
		visited[i] = false;
	}

	std::queue<size_t> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		start = q.front();

#ifdef DEBUG
		std::cout << start << " ";
#endif
		if (start == goal)
		{
#ifdef DEBUG
			std::cout << std::endl;
#endif
			delete[] visited;
			return true;
		}

		q.pop();

		for (const arc& arc : arcs_)
		{
			if (arc.start == start && !visited[arc.end])
			{
				visited[arc.end] = true;
				q.push(arc.end);
			}
		}


	}
#ifdef DEBUG
	std::cout << std::endl;
#endif
	delete[] visited;
	return false;
}

bool graph::oriented_graph::dfs(size_t start, size_t goal) const
{
	if (start >= nodes_count_ || goal >= nodes_count_ || start < 0 || goal < 0)
	{
		return false;
	}

	const auto visited = new bool[nodes_count_];
	for (size_t i = 0; i < nodes_count_; ++i)
	{
		visited[i] = false;
	}

	std::stack<size_t> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		start = q.top();

#ifdef DEBUG
		std::cout << start << " ";
#endif
		if (start == goal)
		{
#ifdef DEBUG
			std::cout << std::endl;
#endif
			delete[] visited;
			return true;
		}

		q.pop();

		for(const arc& arc : arcs_)
		{
			if (arc.start == start && !visited[arc.end])
			{
				visited[arc.end] = true;
				q.push(arc.end);
			}
		}

	}
#ifdef DEBUG
	std::cout << std::endl;
#endif
	delete[] visited;
	return false;
}

std::vector<size_t> graph::oriented_graph::dijkstra(size_t start) const
{
	std::vector<size_t> result(nodes_count_, SIZE_MAX);
	std::vector<bool> is_final_result(nodes_count_, false);
	result[start] = 0;
			
	for (size_t cycle = 0; cycle < nodes_count_; ++cycle)
	{
		is_final_result[start] = true;

		for (const arc& arc : arcs_)
		{
			if (arc.start == start && !is_final_result[arc.end])
			{
				result[arc.end] = std::min(result[arc.end], start + arc.weight);
			}
		}

		const size_t result_size = result.size();
		size_t index_min = 0, i;
		for (i = 0; i < result_size; ++i)
		{
			if (!is_final_result[i])
			{
				index_min = i;
				break;
			}
		}
		++i;
		for (; i < result_size; ++i)
		{
			if (!is_final_result[i] && result[i] < result[index_min])
			{
				index_min = i;
			}
		}
		is_final_result[index_min] = true;
		start = index_min;
#ifdef DEBUG
				for (size_t res : result)
				{
					std::cout << res << '\t';
				}
				std::cout << std::endl;
				for (bool res : is_final_result)
				{
					std::cout <<std::boolalpha<< res << '\t';
				}
				std::cout << std::endl;
#endif
	}

	return result;
}

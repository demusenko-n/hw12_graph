#pragma once
#include <vector>

namespace graph
{
	class oriented_graph
	{
	public:
		class arc
		{
		public:
			size_t start;
			size_t end;
			size_t weight;
		};

		oriented_graph(int nodes_number);

		oriented_graph();

		//move operation is the same as copy, so no need to create void add_arc(arc&& arc)

		void add_arc(const arc& arc);

		void add_node();

		size_t nodes_count()const;

		size_t arcs_count()const;

		bool bfs(size_t start, size_t goal) const;

		bool dfs(size_t start, size_t goal) const;

		std::vector<size_t> dijkstra(size_t start) const;
	private:
		size_t nodes_count_;
		std::vector<arc> arcs_;
	};

}

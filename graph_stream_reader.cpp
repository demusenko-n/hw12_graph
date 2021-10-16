#include "graph_stream_reader.h"

graph_stream_reader::graph_stream_reader(std::istream& stream): stream_(stream)
{}

graph::oriented_graph graph_stream_reader::read() const
{
	int nodes_count;
	stream_ >> nodes_count;
	graph::oriented_graph new_graph(nodes_count);

	int edges_count;
	stream_ >> edges_count;
	for (int i = 0; i < edges_count; ++i)
	{
		graph::oriented_graph::arc new_arc{};
		stream_ >> new_arc.start >> new_arc.end >> new_arc.weight;
		new_graph.add_arc(new_arc);
	}
	return new_graph;
}

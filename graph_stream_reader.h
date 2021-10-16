#pragma once
#include <istream>
#include "oriented_graph.h"

class graph_stream_reader
{
	std::istream& stream_;
public:
	graph_stream_reader(std::istream& stream);

	graph::oriented_graph read()const;
};

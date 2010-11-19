/**
 * @file EdgeListReader.cpp
 * @date 06.10.2010
 * @author gerd
 */

#include "EdgeListReader.h"
#include "../base/Graph.h"
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <boost/foreach.hpp>

using namespace std;

namespace largenet
{

namespace io
{

Graph* EdgeListReader::createFromStream(std::istream& strm, Graph& graphToFill)
{
	if (!strm)
		return &graphToFill;

	typedef pair<node_id_t, node_id_t> edge;
	typedef vector<edge> edge_v;
	node_id_t maxNodeID = 0;
	edge_v edges;
	string line;
	stringstream ss;
	while (getline(strm, line))
	{
		node_id_t n1, n2;
		line += " ";
		ss.str(line);
		ss >> n1 >> n2;
		if (ss.fail())
			throw std::runtime_error("Cannot read input file");

		if (n1 > maxNodeID)
			maxNodeID = n1;
		if (n2 > maxNodeID)
			maxNodeID = n2;

		edges.push_back(edge(n1, n2));
	}

	graphToFill.clear();
	while (graphToFill.numberOfNodes() < maxNodeID + 1)
		graphToFill.addNode();

	BOOST_FOREACH(edge e, edges)
	{
		graphToFill.addEdge(e.first, e.second, true);
	}
	return &graphToFill;
}

Graph* EdgeListReader::createFromStream(istream& strm)
{
	if (!strm)
		return 0;
	Graph* g = new Graph(1, 1); // TODO honor state

	return createFromStream(strm, *g);
}

}

}

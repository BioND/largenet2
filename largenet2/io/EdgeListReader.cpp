/**
 * @file EdgeListReader.cpp
 * @date 06.10.2010
 * @author gerd
 */

#include "EdgeListReader.h"
#include <largenet2/base/Graph.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <boost/foreach.hpp>

using namespace std;

namespace largenet
{

namespace io
{

Graph* EdgeListReader::createFromStream(std::istream& strm)
{
	if (!strm)
		return 0;

	typedef map<node_id_t, node_state_t> node_states_m;
	typedef pair<node_id_t, node_id_t> edge;
	typedef vector<edge> edge_v;
	node_id_t maxNodeID = 0;
	edge_v edges;
	node_states_m node_states;
	node_state_size_t numNodeStates = 1;
	string line;
	stringstream ss;
	while (getline(strm, line))
	{
		node_id_t n1, n2;
		line += " ";
		ss.str(line);
		ss >> n1 >> n2;
		if (readStates_ && (!ss.fail()))
		{
			node_state_t n1_state = 0, n2_state = 0;
			if (!(ss >> n1_state))
				throw std::runtime_error(
						"Failed to read node state at input position "
								<< strm.tellg() << "\n");
			if (!(ss >> n2_state))
				throw std::runtime_error(
						"Failed to read node state at input position "
								<< strm.tellg() << "\n");
			if (n1_state >= numNodeStates)
				numNodeStates = n1_state + 1;
			if (n2_state >= numNodeStates)
				numNodeStates = n2_state + 1;
			node_states.insert(make_pair(n1, n1_state));
			node_states.insert(make_pair(n2, n2_state));
		}

		if (n1 > maxNodeID)
			maxNodeID = n1;
		if (n2 > maxNodeID)
			maxNodeID = n2;

		edges.push_back(edge(n1, n2));
	}

	Graph* graph = new Graph(numNodeStates, numNodeStates * numNodeStates);
	while (graph->numberOfNodes() < maxNodeID + 1)
	{
		node_id_t id = graph->addNode();
		node_state_t state = node_states[id];	// should default-construct state=0 if not in map?
	}

	BOOST_FOREACH(edge e, edges)
			{
				graph->addEdge(e.first, e.second, true);
			}
	return graph;
}

}

}

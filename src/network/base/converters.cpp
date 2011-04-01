/*
 * converters.cpp
 *
 *  Created on: 28.03.2011
 *      Author: gerd
 */

#include "converters.h"
#include <boost/foreach.hpp>
#include <vector>
#include <stdexcept>

using namespace std;

namespace largenet
{
namespace converters
{

void toUndirected(Graph& g)
{
	vector<edge_id_t> directed_edges;
	directed_edges.reserve(g.numberOfEdges());
	BOOST_FOREACH(Edge& e, g.edges())
	{
		if (e.isDirected())
			directed_edges.push_back(e.id());
	}
	BOOST_FOREACH(edge_id_t eid, directed_edges)
	{
		node_id_t a = g.edge(eid)->source()->id(), b = g.edge(eid)->target()->id();
		g.removeEdge(eid);
		g.addEdge(a, b, false);
	}
}

void toDirected(Graph& g)
{
	vector<edge_id_t> undirected_edges;
	undirected_edges.reserve(g.numberOfEdges());
	BOOST_FOREACH(Edge& e, g.edges())
	{
		if (!e.isDirected())
			undirected_edges.push_back(e.id());
	}
	BOOST_FOREACH(edge_id_t eid, undirected_edges)
	{
		node_id_t a = g.edge(eid)->source()->id(), b = g.edge(eid)->target()->id();
		g.removeEdge(eid);
		g.addEdge(a, b, true);
		g.addEdge(b, a, true);
	}
}


}
}

/**
 * @file generators.h
 * @date 12.10.2010
 * @author gerd
 */

#ifndef GENERATORS_H_
#define GENERATORS_H_

#include "../largenet.h"
#include <boost/unordered_set.hpp>
#include <cassert>
#include <cmath>

namespace largenet
{

namespace generators
{

template<class RandomGen>
void randomGnm(Graph& g, node_size_t numNodes, edge_size_t numEdges,
		RandomGen& rng, bool directed = false)
{
	g.clear();
	typedef std::pair<node_id_t, node_id_t> edge_t;
	// hash table for edges
	typedef boost::unordered_set<edge_t> edge_set;

	while (g.numberOfNodes() < numNodes)
		g.addNode();

	if (numNodes < 1)
		return;
	node_size_t max_edges = numNodes * (numNodes - 1) / 2; // undirected
	assert(numEdges <= max_edges);

	/*
	 * efficient G(n,m) from Phys. Rev. E 71, 036113 (2005)
	 */
	edge_set edges;
	edge_t current_edge;
	for (edge_size_t i = 0; i < numEdges; ++i)
	{
		while (true)
		{
			int edge_index = rng.IntFromTo(0, max_edges - 1);
			current_edge.first = 1 + static_cast<node_id_t> (std::floor(
					std::sqrt(0.25 + 2.0 * edge_index) - 0.5));
			current_edge.second = static_cast<node_id_t> (edge_index
					- current_edge.first * (current_edge.first - 1) / 2);
			if (current_edge.first == current_edge.second)	// disallow self-loops
				continue;
			if (edges.find(current_edge) == edges.end())
			{
				edges.insert(current_edge);
				g.addEdge(current_edge.first, current_edge.second, directed);
				break;
			}
		}
	}
}

/**
 * Create a random Erdos-Renyi network with link probability @p p.
 *
 * Links are created with probability @p p in such a way that the expected (average)
 * number of links is @f$ \frac{p}{2} N(N-1) @f$.
 * @param[out] g Graph object to store network (will be cleared first)
 * @param[in] p Link creation probability.
 */
template<class RandomGen>
void randomGnp(Graph& g, node_size_t numNodes, double edgeProb, RandomGen& rng)
{
	// FIXME this seems broken
	throw ("Not yet implented");
	/*
	 * efficient G(n,p) from Phys. Rev. E 71, 036113 (2005)
	 */
	//	assert(edgeProb > 0.0);
	//	assert(edgeProb < 1.0);
	//
	//	g.clear();
	//	while (g.numberOfNodes() < numNodes)
	//		g.addNode();
	//
	//	long int w = -1;
	//	Graph::NodeIteratorRange iters = g.nodes();
	//	for (Graph::NodeIterator v = iters.first; v != iters.second; ++v)
	//	{
	//		double r = rng.Uniform01();
	//		w = 1 + w + static_cast<long int> (std::floor(std::log(1.0 - r)
	//				/ std::log(1.0 - edgeProb)));
	//		while ((w >= v->id()) && (v != iters.second))
	//		{
	//			w -= v->id();
	//			++v;
	//		}
	//		if (v != iters.second)
	//			g.addEdge(v->id(), w, false); // undirected
	//	}
}

/**
 * Barabási-Albert preferential attachment
 * @param g Graph object to hold BA graph, must be empty
 * @param numNodes Total number of nodes of final graph
 * @param m Number of edges attached to each new node
 * @param rng Random number generator providing uniform IntFromTo(int low, int high)
 */
template<class RandomGen>
void randomBA(Graph& g, node_size_t numNodes, edge_size_t m, RandomGen& rng)
{
	/*
	 * efficient BA(n,m) from Phys. Rev. E 71, 036113 (2005)
	 */
	if (g.numberOfNodes() != 0)
		throw("Need empty graph in randomBA");

	typedef std::vector<node_id_t> node_id_v;
	node_id_v nodes(2 * numNodes * m, 0);

	for (node_id_t v = 0; v < numNodes; ++v)
	{
		for (node_id_t i = 0; i < m; ++i)
		{
			size_t ind = 2 * (v * m + i);
			nodes[ind] = v;
			int r = rng.IntFromTo(0, ind);
			nodes[ind + 1] = nodes[r];
		}
	}

	while (g.numberOfNodes() < numNodes) // this relies on an freshly initialized graph!
		g.addNode();

	for (size_t i = 0; i < numNodes * m; ++i)
		g.addEdge(nodes[2 * i], nodes[2 * i + 1], false); // undirected
}

}
}

#endif /* GENERATORS_H_ */

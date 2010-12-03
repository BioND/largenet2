/**
 * @file generators.h
 * @date 12.10.2010
 * @author gerd
 */

#ifndef GENERATORS_H_
#define GENERATORS_H_

#include "../largenet.h"
#include <boost/unordered_set.hpp>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <utility>

#ifndef NDEBUG
#include <iostream>
#include <stdexcept>
#endif

namespace largenet
{

namespace generators
{

namespace util
{

template<class U, class V, class RandomGen>
U& random_from(V& container, RandomGen& rng)
{
	int i = rng.IntFromTo(0, container.size() - 1);
	return container[i];
}

template<class _Iter, class RandomGen>
_Iter random_from(_Iter begin, _Iter end, RandomGen& rng)
{
	if (begin == end)
		return end;
	int i = rng.IntFromTo(0, std::distance(begin, end) - 1);
	std::advance(begin, i);
	assert(begin != end);
	return begin;
}

template<class _Iter, class RandomGen>
_Iter random_from(std::pair<_Iter, _Iter> range, RandomGen& rng)
{
	return random_from(range.first, range.second, rng);
}
}

template<class RandomGen>
void randomGnmSlow(Graph& g, node_size_t numNodes, edge_size_t numEdges,
		RandomGen& rng, bool directed = false)
{
	node_size_t max_edges = directed ? numNodes * (numNodes - 1) : numNodes * (numNodes - 1) / 2;
	if (numEdges > max_edges)
		throw std::runtime_error("Cannot create graph with more than O(N^2) edges");
	g.clear();
	while (g.numberOfNodes() < numNodes)
		g.addNode();
	while (g.numberOfEdges() < numEdges)
	{
		Graph::NodeIterator n1 = random_from(g.nodes()), n2 = random_from(g.nodes());
		if (n1.id() == n2.id())
			continue;
		if (g.isEdge(n1.id(), n2.id()))
			continue;
		else
			g.addEdge(n1.id(), n2.id(), directed);
	}
}

template<class RandomGen>
void randomGnm(Graph& g, node_size_t numNodes, edge_size_t numEdges,
		RandomGen& rng, bool directed = false)
{
	if (directed)
	{
		randomGnmSlow(g, numNodes, numEdges, rng, directed);
		return;
	}
	g.clear();
	typedef std::pair<node_id_t, node_id_t> edge_t;
	// hash table for edges
	typedef boost::unordered_set<edge_t> edge_set;

	while (g.numberOfNodes() < numNodes)
		g.addNode();

	if (numNodes < 1)
		return;
	// FIXME this algorithm does not do what it is expected to do when creating directed edges??
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
			if (current_edge.first == current_edge.second) // disallow self-loops
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
	throw("Not yet implented");
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

/**
 * Create directed graph with power law out-degree distribution with exponent @p exponent
 * and Poisson in-degree distribution.
 * @param g Graph object to hold graph, must be empty
 * @param numNodes Total number of nodes of final graph
 * @param exponent power law exponent in out-degree distribution @f$ p(k) = k^(-exponent) @f$
 * @param rng Random number generator providing uniform IntFromTo(int low, int high)
 */
template<class RandomGen>
void randomOutDegreePowerlaw(Graph& g, node_size_t numNodes, double exponent,
		RandomGen& rng)
{
	if (g.numberOfNodes() != 0)
		throw("Need empty graph in randomOutDegreePowerlaw");

	double normalization = 0;
	for (int i = numNodes; i >= 1; --i)
	{
		normalization += pow(i, -exponent);
	}
	normalization = 1.0 / normalization;

	std::vector<node_size_t> degdist(numNodes + 1, 0);
	double remain = 0;
	for (size_t i = numNodes; i >= 1; --i)
	{
		degdist[i] = 0;
		remain += numNodes * normalization * pow(i, -exponent);
		degdist[i] = static_cast<node_size_t> (floor(remain));
		remain -= degdist[i];
	}
	degdist[0] = static_cast<node_size_t>(round(remain));

#ifndef NDEBUG
	node_size_t degsum = 0;
	double mdeg = 0;
	for (size_t k = 0; k < degdist.size(); ++k)
	{
		degsum += degdist[k];
		mdeg += k*degdist[k];
	}
	std::cout << "Sum of N[k] is " << degsum << "\n";
	std::cout << "Mean degree is " << mdeg/degsum << "\n";
#endif

	while (g.numberOfNodes() < numNodes)
		g.addNode();

	std::vector<node_id_t> nodes(numNodes, 0);
	Graph::NodeIteratorRange nd = g.nodes();
	std::transform(nd.first, nd.second, nodes.begin(), mem_fun_ref(&Node::id));

	for (size_t i = numNodes; i > 0; --i)
	{
		for (node_size_t n = degdist[i]; n > 0; --n)
		{
			node_id_t cur_id = nodes.back();
			nodes.pop_back();
			for (node_size_t k = 0; k < i; ++k)
			{
				Graph::NodeIterator nit = util::random_from(g.nodes(), rng);
				while (g.isEdge(cur_id, nit.id()))
					nit = util::random_from(g.nodes(), rng);
				g.addEdge(cur_id, nit.id(), true);
			}
		}
	}
}

}
}

#endif /* GENERATORS_H_ */

/**
 * @file counts.cpp
 * @date 19.11.2010
 * @author gerd
 */

#include "counts.h"
#include <boost/foreach.hpp>
#include <cassert>

namespace largenet
{
namespace measures
{

size_t triples(const Graph& net)
{
	size_t t = 0;
	BOOST_FOREACH(const Node& n, net.nodes())
	{
		const degree_t d = n.degree();
		if (d > 1)
			t += d * (d - 1);
	}
	return t / 2;
}

size_t outTriples(const Graph& net)
{
	size_t t = 0;
	BOOST_FOREACH(const Node& n, net.nodes())
	{
		const degree_t d = n.outDegree();
		if (d > 1)
			t += d * (d - 1);
	}
	return t / 2;
}

size_t inTriples(const Graph& net)
{
	size_t t = 0;
	BOOST_FOREACH(const Node& n, net.nodes())
	{
		const degree_t d = n.inDegree();
		if (d > 1)
			t += d * (d - 1);
	}
	return t / 2;
}

size_t triples_undirected(const Graph& net, const motifs::TripleMotif& t)
{
	assert(!t.isDirected());
	size_t ret = 0;

	// we cannot loop over links if we do not have access to the link state calculator
	return ret;


	// loop over all a-b links
//	typename network_traits<_Network>::LinkStateIteratorRange iters =
//			net.links(net.linkStateCalculator()(t.left(), t.center()));
//	for (typename network_traits<_Network>::LinkStateIterator& it = iters.first; it
//			!= iters.second; ++it)
//	{
//		node_id_t left, right;
//		if (net.nodeState(net.source(*it)) == t.left())
//		{
//			left = net.source(*it);
//			right = net.target(*it);
//		}
//		else
//		{
//			left = net.target(*it);
//			right = net.source(*it);
//		}
//
//		// count all c-neighbors of the b node
//		typename network_traits<_Network>::NeighborIteratorRange niters =
//				net.neighbors(right);
//		for (typename network_traits<_Network>::NeighborIterator& nit =
//				niters.first; nit != niters.second; ++nit)
//		{
//			if (net.nodeState(*nit) == t.right())
//				++ret;
//		}
//
//		// exclude left a in an a-b-a triple
//		if (t.isSymmetric())
//			--ret;
//
//		// in an a-a-c triple, do the same thing for the left a node
//		if (t.left() == t.center())
//		{
//			// count all c-neighbors of the left node
//			typename network_traits<_Network>::NeighborIteratorRange niters =
//					net.neighbors(left);
//			for (typename network_traits<_Network>::NeighborIterator & nit =
//					niters.first; nit != niters.second; ++nit)
//			{
//				if (net.nodeState(*nit) == t.right())
//					++ret;
//			}
//
//			// exclude left a in an a-b-a triple
//			if (t.isSymmetric())
//				--ret;
//		}
//	}
//
//	if (t.isSymmetric())
//		ret /= 2;
//	return ret;
}

size_t triples(const Graph& net, const motifs::TripleMotif& t)
{
	throw std::runtime_error("Triple motif counting not yet implemented");
	if (!t.isDirected())
		return triples_undirected(net, t);
//	size_t ret = 0;

//	// loop over all a-b links
//	typename network_traits<_Network>::LinkStateIteratorRange iters =
//			net.links(net.linkStateCalculator()(t.left(), t.center()));
//	for (typename network_traits<_Network>::LinkStateIterator& it = iters.first; it
//			!= iters.second; ++it)
//	{
//		node_id_t left, right;
//		if (net.nodeState(net.source(*it)) == t.left())
//		{
//			left = net.source(*it);
//			right = net.target(*it);
//		}
//		else
//		{
//			left = net.target(*it);
//			right = net.source(*it);
//		}
//
//		// count all c-neighbors of the b node
//		typename network_traits<_Network>::NeighborIteratorRange niters =
//				net.neighbors(right);
//		for (typename network_traits<_Network>::NeighborIterator& nit =
//				niters.first; nit != niters.second; ++nit)
//		{
//			if (net.nodeState(*nit) == t.right())
//				++ret;
//		}
//
//		// exclude left a in an a-b-a triple
//		if (t.isSymmetric())
//			--ret;
//
//		// in an a-a-c triple, do the same thing for the left a node
//		if (t.left() == t.center())
//		{
//			// count all c-neighbors of the left node
//			typename network_traits<_Network>::NeighborIteratorRange niters =
//					net.neighbors(left);
//			for (typename network_traits<_Network>::NeighborIterator & nit =
//					niters.first; nit != niters.second; ++nit)
//			{
//				if (net.nodeState(*nit) == t.right())
//					++ret;
//			}
//
//			// exclude left a in an a-b-a triple
//			if (t.isSymmetric())
//				--ret;
//		}
//	}
//
//	if (t.isSymmetric())
//		ret /= 2;
//	return ret;
}

}
}

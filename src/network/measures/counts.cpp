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
	BOOST_FOREACH(const Node& n, net.nodes(t.center()))
	{
		BOOST_FOREACH(const Node& nb1, n.undirectedNeighbors())
		{
			if (net.nodeState(nb1.id()) != t.left())
				continue;
			BOOST_FOREACH(const Node& nb2, n.undirectedNeighbors())
			{
				if (nb1.id() == nb2.id())
					continue;
				if (net.nodeState(nb2.id()) == t.right())
					++ret;
			}
		}
	}

	if (t.isSymmetric())
		return ret / 2;
	else
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
	if (!t.isDirected())
		return triples_undirected(net, t);

	size_t ret = 0;
	BOOST_FOREACH(const Node& n, net.nodes(t.center()))
	{
		switch (t.dir())
		{
			case motifs::TripleMotif::LCR:   // one in-link to left, one out-link to right
				BOOST_FOREACH(const Node& lnb, n.inNeighbors())
				{
					if (net.nodeState(lnb.id()) != t.left())
						continue;

					BOOST_FOREACH(const Node& rnb, n.outNeighbors())
					{
						if (lnb.id() == rnb.id())	// TODO should we consider melons as triples?
							continue;
						if (net.nodeState(rnb.id()) == t.right())
							++ret;
					}
				}
				break;

			case motifs::TripleMotif::RCL:	// one in-link to right, one out-link to left
				BOOST_FOREACH(const Node& rnb, n.inNeighbors())
				{
					if (net.nodeState(rnb.id()) != t.right())
						continue;

					BOOST_FOREACH(const Node& lnb, n.outNeighbors())
					{
						if (lnb.id() == rnb.id())	// TODO should we consider melons as triples?
							continue;
						if (net.nodeState(lnb.id()) == t.left())
							++ret;
					}
				}
				break;

			case motifs::TripleMotif::CLR:	// two out-links
				BOOST_FOREACH(const Node& lnb, n.outNeighbors())
				{
					if (net.nodeState(lnb.id()) != t.left())
						continue;

					BOOST_FOREACH(const Node& rnb, n.outNeighbors())
					{
						if (lnb.id() == rnb.id())	// TODO should we consider double links as triples?
							continue;
						if (net.nodeState(rnb.id()) == t.right())
							++ret;
					}
				}
				break;
			case motifs::TripleMotif::LRC: // two in-links
				BOOST_FOREACH(const Node& lnb, n.inNeighbors())
				{
					if (net.nodeState(lnb.id()) != t.left())
						continue;

					BOOST_FOREACH(const Node& rnb, n.inNeighbors())
					{
						if (lnb.id() == rnb.id())	// TODO should we consider double links as triples?
							continue;
						if (net.nodeState(rnb.id()) == t.right())
							++ret;
					}
				}
				break;
			default:
				break;
		}
	}
	if (t.isSymmetric())
		return ret / 2;
	else
		return ret;

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

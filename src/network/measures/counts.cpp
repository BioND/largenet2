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
			t += d * (d - 1) - 2*n.mutualDegree();	// do not count 2-loops as triples
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
			t += d * (d - 1);	// FIXME will count multi-out-edges as triples for MultiNodes
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
			t += d * (d - 1);	// FIXME will count multi-in-edges as triples for MultiNodes
	}
	return t / 2;
}

size_t inOutTriples(const Graph& net)
{
	size_t t = 0;
	BOOST_FOREACH(const Node& n, net.nodes())
	{
		const degree_t d_in = n.inDegree(), d_out = n.outDegree();
		t += d_in * d_out - n.mutualDegree();
	}
	return t;
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
				if (net.nodeState(nb2.id())
						== t.right())
					++ret;
			}
		}
	}

	if (t.isSymmetric())
		return ret / 2;
	else
		return ret;
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
		case motifs::TripleMotif::LCR: // one in-link to left, one out-link to right
			BOOST_FOREACH(const Node& lnb, n.inNeighbors())
			{
				if (net.nodeState(lnb.id()) != t.left())
					continue;

				BOOST_FOREACH(const Node& rnb, n.outNeighbors())
				{
					if (lnb.id() == rnb.id()) // TODO should we consider double links as triples?
						continue;
					if (net.nodeState(rnb.id()) == t.right())
						++ret;
				}
			}
			break;

		case motifs::TripleMotif::RCL: // one in-link to right, one out-link to left
			BOOST_FOREACH(const Node& rnb, n.inNeighbors())
			{
				if (net.nodeState(rnb.id()) != t.right())
					continue;

				BOOST_FOREACH(const Node& lnb, n.outNeighbors())
				{
					if (lnb.id() == rnb.id()) // TODO should we consider double links as triples?
						continue;
					if (net.nodeState(lnb.id()) == t.left())
						++ret;
				}
			}
			break;

		case motifs::TripleMotif::CLR: // two out-links
			BOOST_FOREACH(const Node& lnb, n.outNeighbors())
			{
				if (net.nodeState(lnb.id()) != t.left())
					continue;

				BOOST_FOREACH(const Node& rnb, n.outNeighbors())
				{
					if (lnb.id() == rnb.id()) // TODO should we consider double links as triples?
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
					if (lnb.id() == rnb.id()) // TODO should we consider double links as triples?
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
}

size_t quadStars(const Graph& net)
{
	size_t t = 0;
	BOOST_FOREACH(const Node& n, net.nodes())
	{
		const degree_t d = n.degree(), m = n.mutualDegree();
		if (d > 2)
			t += 2 * d - 3 * d * d + d * d * d + 8 * m
					- 6 * d * m + 6 * m * m - 2 * m * m * m;
	}
	return t / 6;
}

size_t outQuadStars(const Graph& net)
{
	size_t t = 0;
	BOOST_FOREACH(const Node& n, net.nodes())
	{
		const degree_t d = n.outDegree();
		if (d > 2)
			t += d * (d - 1) * (d - 2);
	}
	return t / 6;
}

size_t inQuadStars(const Graph& net)
{
	size_t t = 0;
	BOOST_FOREACH(const Node& n, net.nodes())
	{
		const degree_t d = n.inDegree();
		if (d > 2)
			t += d * (d - 1) * (d - 2);
	}
	return t / 6;
}

size_t quad_stars_undirected(const Graph& net, const motifs::QuadStarMotif& q)
{
	assert(!q.isDirected());
	size_t ret = 0;

	// we cannot loop over links if we do not have access to the link state calculator
	BOOST_FOREACH(const Node& n, net.nodes(q.center()))
	{
		BOOST_FOREACH(const Node& nb1, n.undirectedNeighbors())
		{
			if (net.nodeState(nb1.id()) != q.a())
				continue;
			BOOST_FOREACH(const Node& nb2, n.undirectedNeighbors())
			{
				if (nb1.id() == nb2.id())
					continue;
				if (net.nodeState(nb2.id())
						!= q.b())
					continue;
				BOOST_FOREACH(const Node& nb3, n.undirectedNeighbors())
				{
					if (nb3.id() == nb2.id() || nb3.id() == nb1.id())
						continue;
					if (net.nodeState(nb3.id()) == q.c())
						++ret;
				}
			}
		}
	}

	if (q.isSymmetric())
		return ret / 6;		// FIXME are these factors correct?
	else if (q.isMirrorSymmetric())
		return ret / 2;
	else
		return ret;
}
size_t quadStars(const Graph& net, const motifs::QuadStarMotif& q)
{
	if (!q.isDirected())
		return quad_stars_undirected(net, q);
	size_t ret = 0;
	switch (q.dir())
	{
	case motifs::QuadStarMotif::ALL_OUT:
		BOOST_FOREACH(const Node& n, net.nodes(q.center()))
		{
			size_t a_neighbors = 0, b_neighbors = 0, c_neighbors = 0;
			BOOST_FOREACH(const Node& nb, n.outNeighbors())
			{
				node_state_t s = net.nodeState(nb.id());
				if (s == q.a())
					++a_neighbors;
				else if (s == q.b())
					++b_neighbors;
				else if (s == q.c())
					++c_neighbors;
			}
			if (q.isSymmetric())
			{
				ret += a_neighbors * (a_neighbors - 1) * (a_neighbors - 2);
			} else if (q.isMirrorSymmetric())
			{
				if (q.a() == q.b())
					ret += a_neighbors * (a_neighbors - 1) * c_neighbors;
				else if (q.a() == q.c())
					ret += a_neighbors * (a_neighbors - 1) * b_neighbors;
				else
					ret += b_neighbors * (b_neighbors - 1) * a_neighbors;
			} else
				ret += a_neighbors * b_neighbors * c_neighbors;
		}
		break;
	case motifs::QuadStarMotif::ALL_IN:
		BOOST_FOREACH(const Node& n, net.nodes(q.center()))
		{
			size_t a_neighbors = 0, b_neighbors = 0, c_neighbors = 0;
			BOOST_FOREACH(const Node& nb, n.inNeighbors())
			{
				node_state_t s = net.nodeState(nb.id());
				if (s == q.a())
					++a_neighbors;
				else if (s == q.b())
					++b_neighbors;
				else if (s == q.c())
					++c_neighbors;
			}
			if (q.isSymmetric())
			{
				ret += a_neighbors * (a_neighbors - 1) * (a_neighbors - 2);
			} else if (q.isMirrorSymmetric())
			{
				if (q.a() == q.b())
					ret += a_neighbors * (a_neighbors - 1) * c_neighbors;
				else if (q.a() == q.c())
					ret += a_neighbors * (a_neighbors - 1) * b_neighbors;
				else
					ret += b_neighbors * (b_neighbors - 1) * a_neighbors;
			} else
				ret += a_neighbors * b_neighbors * c_neighbors;
		}
		break;
	case motifs::QuadStarMotif::A_OUT:
		BOOST_FOREACH(const Node& n, net.nodes(q.center()))
		{
			BOOST_FOREACH(const Node& onb, n.outNeighbors())
			{
				if (net.nodeState(onb.id()) != q.a())
					continue;
				BOOST_FOREACH(const Node& inb1, n.inNeighbors())
				{
					if (inb1.id() == onb.id())
						continue;
					if (net.nodeState(inb1.id()) != q.b())
						continue;
					BOOST_FOREACH(const Node& inb2, n.inNeighbors())
					{
						if (inb2.id() == inb1.id())
							continue;
						if (inb2.id() == onb.id())
							continue;
						if (net.nodeState(inb2.id()) == q.c())
							++ret;
					}
				}
			}
		}
		break;
	case motifs::QuadStarMotif::B_OUT:
		BOOST_FOREACH(const Node& n, net.nodes(q.center()))
		{
			BOOST_FOREACH(const Node& onb, n.outNeighbors())
			{
				if (net.nodeState(onb.id()) != q.b())
					continue;
				BOOST_FOREACH(const Node& inb1, n.inNeighbors())
				{
					if (inb1.id() == onb.id())
						continue;
					if (net.nodeState(inb1.id()) != q.a())
						continue;
					BOOST_FOREACH(const Node& inb2, n.inNeighbors())
					{
						if (inb2.id() == inb1.id())
							continue;
						if (inb2.id() == onb.id())
							continue;
						if (net.nodeState(inb2.id()) == q.c())
							++ret;
					}
				}
			}
		}
		break;
	case motifs::QuadStarMotif::C_OUT:
		BOOST_FOREACH(const Node& n, net.nodes(q.center()))
		{
			BOOST_FOREACH(const Node& onb, n.outNeighbors())
			{
				if (net.nodeState(onb.id()) != q.c())
					continue;
				BOOST_FOREACH(const Node& inb1, n.inNeighbors())
				{
					if (inb1.id() == onb.id())
						continue;
					if (net.nodeState(inb1.id()) != q.b())
						continue;
					BOOST_FOREACH(const Node& inb2, n.inNeighbors())
					{
						if (inb2.id() == inb1.id())
							continue;
						if (inb2.id() == onb.id())
							continue;
						if (net.nodeState(inb2.id()) == q.a())
							++ret;
					}
				}
			}
		}
		break;
	case motifs::QuadStarMotif::AB_OUT:
		BOOST_FOREACH(const Node& n, net.nodes(q.center()))
		{
			BOOST_FOREACH(const Node& onb1, n.outNeighbors())
			{
				if (net.nodeState(onb1.id()) != q.a())
					continue;
				BOOST_FOREACH(const Node& onb2, n.outNeighbors())
				{
					if (onb2.id() == onb1.id())
						continue;
					if (net.nodeState(onb2.id() != q.b()))
						continue;
					BOOST_FOREACH(const Node& inb, n.inNeighbors())
					{
						if (inb.id() == onb1.id())
							continue;
						if (inb.id() == onb2.id())
							continue;
						if (net.nodeState(inb.id()) == q.c())
							++ret;
					}
				}
			}
		}
		break;
	case motifs::QuadStarMotif::AC_OUT:
		BOOST_FOREACH(const Node& n, net.nodes(q.center()))
		{
			BOOST_FOREACH(const Node& onb1, n.outNeighbors())
			{
				if (net.nodeState(onb1.id()) != q.a())
					continue;
				BOOST_FOREACH(const Node& onb2, n.outNeighbors())
				{
					if (onb2.id() == onb1.id())
						continue;
					if (net.nodeState(onb2.id() != q.c()))
						continue;
					BOOST_FOREACH(const Node& inb, n.inNeighbors())
					{
						if (inb.id() == onb1.id())
							continue;
						if (inb.id() == onb2.id())
							continue;
						if (net.nodeState(inb.id()) == q.b())
							++ret;
					}
				}
			}
		}
		break;
	case motifs::QuadStarMotif::BC_OUT:
		BOOST_FOREACH(const Node& n, net.nodes(q.center()))
		{
			BOOST_FOREACH(const Node& onb1, n.outNeighbors())
			{
				if (net.nodeState(onb1.id()) != q.b())
					continue;
				BOOST_FOREACH(const Node& onb2, n.outNeighbors())
				{
					if (onb2.id() == onb1.id())
						continue;
					if (net.nodeState(onb2.id() != q.c()))
						continue;
					BOOST_FOREACH(const Node& inb, n.inNeighbors())
					{
						if (inb.id() == onb1.id())
							continue;
						if (inb.id() == onb2.id())
							continue;
						if (net.nodeState(inb.id()) == q.a())
							++ret;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	if (q.isSymmetric())
		return ret / 6;
	else if (q.isMirrorSymmetric())
		return ret / 2;
	else
		return ret;
}

}
}

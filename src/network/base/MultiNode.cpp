/**
 * @file MultiNode.cpp
 * @date 01.09.2009
 * @author gerd
 */

#include "MultiNode.h"
#include "Edge.h"
#include "exceptions.h"
#include <boost/foreach.hpp>

namespace largenet
{

bool MultiNode::hasEdgeTo(const Node* n) const
{
	BOOST_FOREACH(Edge* e, outEdges_)
				{
					if (e->to(*n))
						return true;
				}
	return false;
}

Edge* MultiNode::edgeTo(const Node* n) const
{
	BOOST_FOREACH(Edge* e, outEdges_)
				{
					if (e->to(*n))
						return e;
				}
	throw(NotAdjacentException("Node has no edge to given node."));
}

bool MultiNode::hasEdgeFrom(const Node* n) const
{
	BOOST_FOREACH(Edge* e, inEdges_)
				{
					if (e->from(*n))
						return true;
				}
	return false;
}

Edge* MultiNode::edgeFrom(const Node* n) const
{
	BOOST_FOREACH(Edge* e, inEdges_)
				{
					if (e->from(*n))
						return e;
				}
	throw(NotAdjacentException("Node has no edge from given node."));
}

bool MultiNode::hasUndirectedEdgeTo(const Node* n) const
{
	BOOST_FOREACH(Edge* e, unEdges_)
				{
					if (e->from(*n) || e->to(*n))
						return true;
				}
	return false;
}

Edge* MultiNode::undirectedEdgeTo(const Node* n) const
{
	BOOST_FOREACH(Edge* e, unEdges_)
				{
					if (e->from(*n) || e->to(*n))
						return e;
				}
	throw(NotAdjacentException("Node has no undirected edge to given node."));
}

void MultiNode::registerEdge(const Edge* e)
{
	if (hasEdge(e))
		return;

	if ((e->source() != this) && (e->target() != this)) // neither target nor source point to this node
		throw(NotAdjacentException(
				"Cannot register edge that does not connect to this node."));

	if (e->source() == this)
	{
		if (e->isDirected())
		{
			outEdges_.insert(const_cast<Edge*> (e));
			if (e->isLoop())
			{
				inEdges_.insert(const_cast<Edge*> (e));
				return;
			}
		}
		else
		{
			unEdges_.insert(const_cast<Edge*> (e));
			return;
		}
	}

	if (e->target() == this)
	{
		if (e->isDirected())
		{
			inEdges_.insert(const_cast<Edge*> (e));
			if (e->isLoop())
				outEdges_.insert(const_cast<Edge*> (e));
		}
		else
			unEdges_.insert(const_cast<Edge*> (e));
	}
}

void MultiNode::unregisterEdge(const Edge* e)
{
	edge_set::iterator i = inEdges_.find(const_cast<Edge*> (e)); // here be dragons
	if (i != inEdges_.end())
		inEdges_.erase(i);

	i = outEdges_.find(const_cast<Edge*> (e)); // here be dragons;
	if (i != outEdges_.end())
		outEdges_.erase(i);

	i = unEdges_.find(const_cast<Edge*> (e)); // here be dragons;
	if (i != unEdges_.end())
		unEdges_.erase(i);
}

}

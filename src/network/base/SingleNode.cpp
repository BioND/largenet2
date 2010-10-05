/**
 * @file SingleNode.cpp
 * @date 01.09.2009
 * @author gerd
 */

#include "SingleNode.h"
#include "Edge.h"
#include "exceptions.h"
#include <boost/foreach.hpp>

namespace largenet
{

bool SingleNode::hasEdgeTo(const Node* n) const
{
	BOOST_FOREACH(Edge* e, outEdges_)
				{
					if (e->to(*n))
						return true;
				}
	return false;
}

Edge* SingleNode::edgeTo(const Node* n) const
{
	BOOST_FOREACH(Edge* e, outEdges_)
				{
					if (e->to(*n))
						return e;
				}
	throw(NotAdjacentException("Node has no edge to given node."));
}

bool SingleNode::hasEdgeFrom(const Node* n) const
{
	BOOST_FOREACH(Edge* e, inEdges_)
				{
					if (e->from(*n))
						return true;
				}
	return false;
}

Edge* SingleNode::edgeFrom(const Node* n) const
{
	BOOST_FOREACH(Edge* e, inEdges_)
				{
					if (e->from(*n))
						return e;
				}
	throw(NotAdjacentException("Node has no edge from given node."));
}

bool SingleNode::hasUndirectedEdgeTo(const Node* n) const
{
	BOOST_FOREACH(Edge* e, unEdges_)
				{
					if (e->from(*n) || e->to(*n))
						return true;
				}
	return false;
}

Edge* SingleNode::undirectedEdgeTo(const Node* n) const
{
	BOOST_FOREACH(Edge* e, unEdges_)
				{
					if (e->from(*n) || e->to(*n))
						return e;
				}
	throw(NotAdjacentException("Node has no undirected edge to given node."));
}

void SingleNode::registerEdge(const Edge* e)
{
	if (hasEdge(e))
		return;

	if (e->source() == this)
	{
		if (e->isDirected())
		{
			if (hasEdgeTo(e->target()))
				throw SingletonException("Edge already exists.");

			outEdges_.insert(const_cast<Edge*> (e));
			if (e->isLoop())
			{
				inEdges_.insert(const_cast<Edge*> (e));
				return;
			}
		}
		else if (hasUndirectedEdgeTo(e->target()))
			throw SingletonException("Edge already exists.");
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
			if (hasEdgeFrom(e->source()))
				throw SingletonException("Edge already exists.");
			inEdges_.insert(const_cast<Edge*> (e));
			if (e->isLoop())
			{
				outEdges_.insert(const_cast<Edge*> (e));
				return;
			}
		}
		else if (hasUndirectedEdgeTo(e->source()))
			throw SingletonException("Edge already exists.");
		else
		{
			unEdges_.insert(const_cast<Edge*> (e));
			return;
		}
	}

	// neither target nor source point to this node
	throw(NotAdjacentException(
			"Cannot register edge that does not connect to this node."));
}

void SingleNode::unregisterEdge(const Edge* e)
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

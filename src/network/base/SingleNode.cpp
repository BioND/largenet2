/**
 * @file SingleNode.cpp
 * @date 01.09.2009
 * @author gerd
 */

#include "SingleNode.h"
#include "Edge.h"
#include "exceptions.h"
#include <stdexcept>

namespace largenet
{

bool SingleNode::hasEdgeTo(const Node* n) const
{
	for (edge_set::iterator it = outEdges_.begin(); it != outEdges_.end(); ++it)
	{
		if ((*it)->to(*n))
			return true;
	}
	return false;
}

Edge* SingleNode::edgeTo(const Node* n) const
{
	for (edge_set::iterator it = outEdges_.begin(); it != outEdges_.end(); ++it)
	{
		if ((*it)->to(*n))
			return *it;
	}
	throw(std::invalid_argument("Node has no edge to given node."));
}

bool SingleNode::hasEdgeFrom(const Node* n) const
{
	for (edge_set::iterator it = inEdges_.begin(); it != inEdges_.end(); ++it)
	{
		if ((*it)->from(*n))
			return true;
	}
	return false;
}

Edge* SingleNode::edgeFrom(const Node* n) const
{
	for (edge_set::iterator it = inEdges_.begin(); it != inEdges_.end(); ++it)
	{
		if ((*it)->from(*n))
			return *it;
	}
	throw(std::invalid_argument("Node has no edge from given node."));
}

void SingleNode::registerEdge(const Edge* e)
{
	if (hasEdge(e))
		return;

	if (e->source() == this)
	{
		if (hasEdgeTo(e->target()))
			throw SingletonException("Edge already exists.");

		outEdges_.insert(const_cast<Edge*> (e));
		if (!e->isDirected()) // register bidirectional edge both in out- and inEdges
		{
			if (e->isLoop()) // cannot have bidirectional self-loop, that would be a multi-edge
				throw SingletonException(
						"Bidirectional self-loops are not allowed in SingleNode");
			else
			{
				inEdges_.insert(const_cast<Edge*> (e));
				return; // finished here
			}
		}
	}

	if (e->target() == this)
	{
		if (hasEdgeFrom(e->source()))
			throw SingletonException("Edge already exists.");
		inEdges_.insert(const_cast<Edge*> (e));
		if (!e->isDirected()) // register bidirectional edge both in out- and inEdges
		{
			if (e->isLoop()) // cannot have bidirectional self-loop, that would be a multi-edge
				throw SingletonException(
						"Bidirectional self-loops are not allowed in SingleNode");
			else
			{
				outEdges_.insert(const_cast<Edge*> (e));
				return; // finished here
			}
		}
	}

	// neither target nor source point to this node
	throw(std::invalid_argument(
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
}

}

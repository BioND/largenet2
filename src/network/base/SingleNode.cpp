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

	edge_set* edges = &outEdges_;
	if (e->source() == this)
	{
		if (hasEdgeTo(e->target()))
			throw SingletonException("Edge already exists.");
		edges = &outEdges_;
	}
	else if (e->target() == this)
	{
		if (hasEdgeFrom(e->source()))
			throw SingletonException("Edge already exists.");
		if (e->isDirected()) // always register undirected edges as out edges
			edges = &inEdges_;
	}
	else
		throw(std::invalid_argument(
				"Cannot register edge that does not connect to this node."));

	edges->insert(const_cast<Edge*> (e)); // here be dragons
}

void SingleNode::unregisterEdge(const Edge* e)
{
	edge_set::iterator i = inEdges_.find(const_cast<Edge*> (e)); // here be dragons
	if (i != inEdges_.end())
		inEdges_.erase(i);
	else
	{
		i = outEdges_.find(const_cast<Edge*> (e)); // here be dragons;
		if (i != outEdges_.end())
			outEdges_.erase(i);
	}

}

}

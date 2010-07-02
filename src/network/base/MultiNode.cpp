/**
 * @file MultiNode.cpp
 * @date 01.09.2009
 * @author gerd
 */

#include "MultiNode.h"
#include "Edge.h"

namespace largenet
{

bool MultiNode::hasEdgeTo(const Node* n) const
{
	for (edge_set::iterator it = outEdges_.begin(); it != outEdges_.end(); ++it)
	{
		if ((*it)->to(*n))
			return true;
	}
	return false;
}

Edge* MultiNode::edgeTo(const Node* n) const
{

	for (edge_set::iterator it = outEdges_.begin(); it != outEdges_.end(); ++it)
	{
		if ((*it)->to(*n))
			return *it;
	}
	throw(std::invalid_argument("Node has no edge to given node."));
}

bool MultiNode::hasEdgeFrom(const Node* n) const
{
	for (edge_set::iterator it = inEdges_.begin(); it != inEdges_.end(); ++it)
	{
		if ((*it)->from(*n))
			return true;
	}
	return false;
}

Edge* MultiNode::edgeFrom(const Node* n) const
{
	for (edge_set::iterator it = inEdges_.begin(); it != inEdges_.end(); ++it)
	{
		if ((*it)->from(*n))
			return *it;
	}
	throw(std::invalid_argument("Node has no edge from given node."));
}

void MultiNode::registerEdge(const Edge* e)
{
	if (hasEdge(e))
		return;
	edge_set* edges = &outEdges_;
	if (e->source() == this)
		edges = &outEdges_;
	else if (e->target() == this)
	{
		if (e->isDirected()) // always register undirected edges as out edges
			edges = &inEdges_;
	}
	else
		throw(std::invalid_argument(
				"Cannot register edge that does not connect to this node."));

	edges->insert(const_cast<Edge*> (e)); // here be dragons
}

void MultiNode::unregisterEdge(const Edge* e)
{
	edge_set::iterator i = inEdges_.find(const_cast<Edge*> (e)); // here be dragons
	if (i != inEdges_.end())
		inEdges_.erase(i);
	else
	{
		i = outEdges_.find(const_cast<Edge*> (e)); // here be dragons
		if (i != outEdges_.end())
			outEdges_.erase(i);
	}
}

}

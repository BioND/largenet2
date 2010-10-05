/**
 * @file SingleNode.h
 * @date 01.09.2009
 * @author gerd
 */

#ifndef SINGLENODE_H_
#define SINGLENODE_H_

#include "Node.h"

namespace largenet {

class SingleNode: public Node
{
public:
	SingleNode(node_id_t id) : Node(id) {}
	virtual ~SingleNode() {}
	degree_t outDegree() const { return outEdges_.size(); }
	degree_t inDegree() const { return inEdges_.size(); }
	bool hasInEdge(const Edge* e) const { /* here be dragons */ return inEdges_.find(const_cast<Edge*> (e)) != inEdges_.end(); }
	bool hasOutEdge(const Edge* e) const { /* here be dragons */ return outEdges_.find(const_cast<Edge*> (e)) != outEdges_.end(); }
	bool hasEdgeTo(const Node* n) const;
	bool hasEdgeFrom(const Node* n) const;
	Edge* edgeTo(const Node* n) const;
	Edge* edgeFrom(const Node* n) const;
	edge_iterator_range outEdges() const { return std::make_pair(outEdges_.begin(), outEdges_.end()); }
	edge_iterator_range inEdges() const { return std::make_pair(inEdges_.begin(), inEdges_.end()); }
	OutNeighborIteratorRange outNeighbors()
	{
		return std::make_pair(OutNeighborIterator(outEdges_.begin(), id()),
				OutNeighborIterator(outEdges_.end(), id()));
	}
	ConstOutNeighborIteratorRange outNeighbors() const
	{
		return std::make_pair(
				ConstOutNeighborIterator(outEdges_.begin(), id()),
				ConstOutNeighborIterator(outEdges_.end(), id()));
	}
	InNeighborIteratorRange inNeighbors()
	{
		return std::make_pair(InNeighborIterator(inEdges_.begin(), id()),
				InNeighborIterator(inEdges_.end(), id()));
	}
	ConstInNeighborIteratorRange inNeighbors() const
	{
		return std::make_pair(ConstInNeighborIterator(inEdges_.begin(), id()),
				ConstInNeighborIterator(inEdges_.end(), id()));
	}

protected:
	void registerEdge(const Edge* e);
	void unregisterEdge(const Edge* e);

private:
	edge_set outEdges_, inEdges_;
};

}

#endif /* SINGLENODE_H_ */

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
	virtual degree_t outDegree() const { return outEdges_.size(); }
	virtual degree_t inDegree() const { return inEdges_.size(); }
	virtual bool hasInEdge(const Edge* e) const { /* here be dragons */ return inEdges_.find(const_cast<Edge*> (e)) != inEdges_.end(); }
	virtual bool hasOutEdge(const Edge* e) const { /* here be dragons */ return outEdges_.find(const_cast<Edge*> (e)) != outEdges_.end(); }
	virtual bool hasEdgeTo(const Node* n) const;
	virtual bool hasEdgeFrom(const Node* n) const;
	virtual Edge* edgeTo(const Node* n) const;
	virtual Edge* edgeFrom(const Node* n) const;
	virtual edge_iterator_range outEdges() const { return std::make_pair(outEdges_.begin(), outEdges_.end()); }
	virtual edge_iterator_range inEdges() const { return std::make_pair(inEdges_.begin(), inEdges_.end()); }
	virtual OutNeighborIteratorRange outNeighbors() { return std::make_pair(OutNeighborIterator(outEdges_.begin(), id()), OutNeighborIterator(outEdges_.end(), id())); }
	virtual ConstOutNeighborIteratorRange outNeighbors() const { return std::make_pair(ConstOutNeighborIterator(outEdges_.begin(), id()), ConstOutNeighborIterator(outEdges_.end(), id())); }
	virtual InNeighborIteratorRange inNeighbors() { return std::make_pair(InNeighborIterator(inEdges_.begin()), InNeighborIterator(inEdges_.end())); }
	virtual ConstInNeighborIteratorRange inNeighbors() const { return std::make_pair(ConstInNeighborIterator(inEdges_.begin()), ConstInNeighborIterator(inEdges_.end())); }

protected:
	virtual void registerEdge(const Edge* e);
	virtual void unregisterEdge(const Edge* e);

private:
	edge_set outEdges_, inEdges_;
};

}

#endif /* SINGLENODE_H_ */

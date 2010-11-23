/**
 * @file MultiNode.h
 * @date 01.09.2009
 * @author gerd
 */

#ifndef MULTINODE_H_
#define MULTINODE_H_

#include "Node.h"

namespace largenet
{

class MultiNode: public Node
{
public:
	MultiNode(node_id_t id) :
		Node(id)
	{
	}
	virtual ~MultiNode()
	{
	}
	degree_t outDegree() const
	{
		return outEdges_.size();
	}
	degree_t inDegree() const
	{
		return inEdges_.size();
	}
	degree_t mutualDegree() const;
	degree_t undirectedDegree() const
	{
		return unEdges_.size();
	}
	bool hasInEdge(const Edge* e) const
	{ /* here be dragons */
		return inEdges_.find(const_cast<Edge*> (e)) != inEdges_.end();
	}
	bool hasOutEdge(const Edge* e) const
	{ /* here be dragons */
		return outEdges_.find(const_cast<Edge*> (e)) != outEdges_.end();
	}
	bool hasUndirectedEdge(const Edge* e) const
	{ /* here be dragons */
		return unEdges_.find(const_cast<Edge*> (e)) != unEdges_.end();
	}
	bool hasEdgeTo(const Node* n) const;
	bool hasEdgeFrom(const Node* n) const;
	bool hasUndirectedEdgeTo(const Node* n) const;
	Edge* edgeTo(const Node* n) const;
	Edge* edgeFrom(const Node* n) const;
	Edge* undirectedEdgeTo(const Node* n) const;
	edge_iterator_range outEdges() const
	{
		return edge_iterator_range(outEdges_.begin(), outEdges_.end());
	}
	edge_iterator_range inEdges() const
	{
		return edge_iterator_range(inEdges_.begin(), inEdges_.end());
	}
	edge_iterator_range undirectedEdges() const
	{
		return edge_iterator_range(unEdges_.begin(), unEdges_.end());
	}
	OutNeighborIteratorRange outNeighbors()
	{
		return OutNeighborIteratorRange(OutNeighborIterator(outEdges_.begin(),
				id()), OutNeighborIterator(outEdges_.end(), id()));
	}
	ConstOutNeighborIteratorRange outNeighbors() const
	{
		return ConstOutNeighborIteratorRange(ConstOutNeighborIterator(
				outEdges_.begin(), id()), ConstOutNeighborIterator(
				outEdges_.end(), id()));
	}
	InNeighborIteratorRange inNeighbors()
	{
		return InNeighborIteratorRange(InNeighborIterator(inEdges_.begin(),
				id()), InNeighborIterator(inEdges_.end(), id()));
	}
	ConstInNeighborIteratorRange inNeighbors() const
	{
		return ConstInNeighborIteratorRange(ConstInNeighborIterator(
				inEdges_.begin(), id()), ConstInNeighborIterator(
				inEdges_.end(), id()));
	}
	ConstUndirectedNeighborIteratorRange undirectedNeighbors() const
	{
		return ConstUndirectedNeighborIteratorRange(
				ConstUndirectedNeighborIterator(unEdges_.begin(), id()),
				ConstUndirectedNeighborIterator(unEdges_.end(), id()));
	}
	UndirectedNeighborIteratorRange undirectedNeighbors()
	{
		return UndirectedNeighborIteratorRange(UndirectedNeighborIterator(
				unEdges_.begin(), id()), UndirectedNeighborIterator(
				unEdges_.end(), id()));
	}

protected:
	void registerEdge(const Edge* e);
	void unregisterEdge(const Edge* e);

private:
	edge_set outEdges_, inEdges_, unEdges_;
};

}

#endif /* MULTINODE_H_ */

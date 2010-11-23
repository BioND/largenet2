/**
 * @file Node.h
 * @author Gerd Zschaler
 * @date Aug 15, 2008
 * Declaration of the lnet::Node class.
 */
#ifndef NODE_H_
#define NODE_H_

#include "types.h"
#include "exceptions.h"
#include "node_iterators.h"
#include <cassert>
#include <set>
#include <utility>
#include <boost/noncopyable.hpp>
#include <stdexcept>

namespace largenet
{

class Edge;

class Node: public boost::noncopyable
{
	friend class Edge;
public:
	typedef std::set<Edge*> edge_set;
	typedef edge_set::iterator edge_iterator;
	typedef edge_set::const_iterator const_edge_iterator;
	typedef std::pair<edge_iterator, edge_iterator> edge_iterator_range;

	typedef iterators::NodeOutNeighborIterator<edge_iterator>
			OutNeighborIterator;
	typedef iterators::NodeOutNeighborIterator<const_edge_iterator, true>
			ConstOutNeighborIterator;
	typedef iterators::NodeInNeighborIterator<edge_iterator> InNeighborIterator;
	typedef iterators::NodeInNeighborIterator<const_edge_iterator, true>
			ConstInNeighborIterator;

	typedef std::pair<OutNeighborIterator, OutNeighborIterator>
			OutNeighborIteratorRange;
	typedef std::pair<InNeighborIterator, InNeighborIterator>
			InNeighborIteratorRange;
	typedef std::pair<ConstOutNeighborIterator, ConstOutNeighborIterator>
			ConstOutNeighborIteratorRange;
	typedef std::pair<ConstInNeighborIterator, ConstInNeighborIterator>
			ConstInNeighborIteratorRange;

	typedef iterators::UndirectedNodeNeighborIterator<edge_iterator> UndirectedNeighborIterator;
	typedef iterators::UndirectedNodeNeighborIterator<const_edge_iterator, true> ConstUndirectedNeighborIterator;
	typedef std::pair<UndirectedNeighborIterator, UndirectedNeighborIterator> UndirectedNeighborIteratorRange;
	typedef std::pair<ConstUndirectedNeighborIterator, ConstUndirectedNeighborIterator> ConstUndirectedNeighborIteratorRange;

	Node(node_id_t id) :
		id_(id)
	{
	}
	virtual ~Node() {}
	node_id_t id() const
	{
		return id_;
	}
	/**
	 * Number of outgoing edges
	 * @return out-degree of this node
	 */
	virtual degree_t outDegree() const = 0;
	/**
	 * Number of incoming edges
	 * @return in-degree of this node
	 */
	virtual degree_t inDegree() const = 0;
	/**
	 * Number of mutual edges (pairs of incoming and outgoing edges from/to same neighbor).
	 * Undirected edges are not taken into account.
	 * @return mutual degree of this node
	 */
	virtual degree_t mutualDegree() const = 0;
	/**
	 * Number of undirected edges
	 * @return undirected degree of this node
	 */
	virtual degree_t undirectedDegree() const = 0;
	/**
	 * Total number of incoming, outgoing, and undirected edges
	 * @return Total degree of this node
	 */
	virtual degree_t degree() const
	{
		return inDegree() + outDegree() + undirectedDegree();
	}
	virtual bool hasInEdge(const Edge* e) const = 0;
	virtual bool hasOutEdge(const Edge* e) const = 0;
	virtual bool hasUndirectedEdge(const Edge* e) const = 0;
	bool hasEdge(const Edge* e) const
	{
		return hasOutEdge(e) || hasInEdge(e) || hasUndirectedEdge(e);
	}
	virtual bool hasEdgeTo(const Node* n) const = 0;
	virtual bool hasEdgeFrom(const Node* n) const = 0;
	virtual bool hasUndirectedEdgeTo(const Node* n) const = 0;
	virtual Edge* edgeTo(const Node* n) const = 0;
	virtual Edge* edgeFrom(const Node* n) const = 0;
	virtual Edge* undirectedEdgeTo(const Node* n) const = 0;
	Edge* edgeToAdjacentNode(const Node* n) const
	{
		Edge* e = 0;
		try
		{
			e = edgeTo(n);
		} catch (NotAdjacentException&)
		{
			try {
				e = edgeFrom(n);
			} catch (NotAdjacentException&)
			{
				e = undirectedEdgeTo(n);
			}
		}
		return e;
	}

	bool isAdjacentTo(const Node* n) const
	{
		return hasEdgeTo(n) || hasEdgeFrom(n) || hasUndirectedEdgeTo(n);
	}
	virtual edge_iterator_range outEdges() const = 0;
	virtual edge_iterator_range inEdges() const = 0;
	virtual edge_iterator_range undirectedEdges() const = 0;
	virtual ConstOutNeighborIteratorRange outNeighbors() const = 0;
	virtual OutNeighborIteratorRange outNeighbors() = 0;
	virtual ConstInNeighborIteratorRange inNeighbors() const = 0;
	virtual InNeighborIteratorRange inNeighbors() = 0;
	virtual ConstUndirectedNeighborIteratorRange undirectedNeighbors() const = 0;
	virtual UndirectedNeighborIteratorRange undirectedNeighbors() = 0;

/*	template<class RandomNumGen>
	Node* randomOutNeighbor(RandomNumGen& rnd)
	{
		const degree_size_t deg = outDegree();
		if (deg == 0)
			throw(std::invalid_argument(
					"Cannot pick random neighbor from empty set."));
		const int num = rnd.IntFromTo(0, deg - 1);
		OutNeighborIteratorRange iters = outNeighbors();
		OutNeighborIterator it = iters.first;
		std::advance(it, num);
		assert(it != iters.second);
		return it.operator->();
	}

	template<class RandomNumGen>
	const Node* randomOutNeighbor(RandomNumGen& rnd) const
	{
		const degree_t deg = outDegree();
		if (deg == 0)
			throw(std::invalid_argument(
					"Cannot pick random neighbor from empty set."));
		const int num = rnd.IntFromTo(0, deg - 1);
		ConstOutNeighborIteratorRange iters = outNeighbors();
		ConstOutNeighborIterator it = iters.first;
		std::advance(it, num);
		assert(it != iters.second); // should always give true
		return it.operator->();
	}

	template<class RandomNumGen>
	Node* randomInNeighbor(RandomNumGen& rnd)
	{
		const degree_t deg = inDegree();
		if (deg == 0)
			throw(std::invalid_argument(
					"Cannot pick random neighbor from empty set."));
		const int num = rnd.IntFromTo(0, deg - 1);
		InNeighborIteratorRange iters = inNeighbors();
		InNeighborIterator it = iters.first;
		std::advance(it, num);
		assert(it != iters.second); // should always give true
		return it.operator->();
	}

	template<class RandomNumGen>
	const Node* randomInNeighbor(RandomNumGen& rnd) const
	{
		const degree_t deg = inDegree();
		if (deg == 0)
			throw(std::invalid_argument(
					"Cannot pick random neighbor from empty set."));
		const int num = rnd.IntFromTo(0, deg - 1);
		ConstInNeighborIteratorRange iters = inNeighbors();
		ConstInNeighborIterator it = iters.first;
		std::advance(it, num);
		assert(it != iters.second); // should always give true
		return it.operator->();
	}
*/
protected:
	virtual void registerEdge(const Edge* e) = 0;
	virtual void unregisterEdge(const Edge* e) = 0;
	void setId(node_id_t id)
	{
		id_ = id;
	}

private:
	node_id_t id_;
};

}
#endif /*NODE_H_*/

#ifndef NODE_H_
#define NODE_H_

#include <largenet2/base/types.h>
#include <largenet2/base/exceptions.h>
#include <largenet2/base/node_iterators.h>
#include <cassert>
#include <set>
#include <utility>
#include <boost/noncopyable.hpp>
#include <stdexcept>

namespace largenet
{

class Edge;

/**
 * Node interface class
 *
 * Represents a node in the network. A Node provides access to its incoming and outgoing
 * edges and neighbors.
 */
class Node: public boost::noncopyable
{
	friend class Edge;
public:
	typedef std::set<Edge*> edge_set;	///< Used to store pointers to adjacent edges
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

	/**
	 * Constructor
	 *
	 * Creates a node with ID @p id
	 * @param id Node ID
	 */
	Node(node_id_t id) :
		id_(id)
	{
	}

	/**
	 * Destructor
	 */
	virtual ~Node() {}

	/**
	 * Get the node's ID
	 *
	 * @return Node ID
	 */
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
	/**
	 * Check if @p e is an incoming edge of this node
	 * @param e pointer to Edge
	 * @return true if @p e is an incoming edge of this node
	 */
	virtual bool hasInEdge(const Edge* e) const = 0;
	/**
	 * Check if @p e is an outgoing edge of this node
	 * @param e pointer to Edge
	 * @return true if @p e is an outgoing edge of this node
	 */
	virtual bool hasOutEdge(const Edge* e) const = 0;
	/**
	 * Check if @p e is an undirected edge connected to this node
	 * @param e pointer to Edge
	 * @return true if @p e is an undirected edge connected to this node
	 */
	virtual bool hasUndirectedEdge(const Edge* e) const = 0;
	/**
	 * Check if @p e connects to this node.
	 *
	 * The Edge @p e may be an outgoing, incoming, or undirected edge connected
	 * to this node.
	 * @param e pointer to Edge
	 * @return true if @p e connects to this node
	 */
	bool hasEdge(const Edge* e) const
	{
		return hasOutEdge(e) || hasInEdge(e) || hasUndirectedEdge(e);
	}
	/**
	 * Check if this node has an outgoing edge to node @p n
	 * @param n pointer to Node
	 * @return true if this node has an outgoing edge connecting to @p n
	 */
	virtual bool hasEdgeTo(const Node* n) const = 0;
	/**
	 * Check if this node has an incoming edge from node @p n
	 * @param n pointer to Node
	 * @return true if this node has an incoming edge connecting to @p n
	 */
	virtual bool hasEdgeFrom(const Node* n) const = 0;
	/**
	 * Check if this node has an undirected edge connecting to node @p n
	 * @param n pointer to Node
	 * @return true if this node has an undirected edge connecting to node @p n
	 */
	virtual bool hasUndirectedEdgeTo(const Node* n) const = 0;
	/**
	 * Get edge to @p n
	 * @param n pointer to @p n
	 * @return pointer to the outgoing edge connecting to @p n
	 * @throw NotAdjacentException if @p n is not connected by an outgoing edge
	 */
	virtual Edge* edgeTo(const Node* n) const = 0;
	/**
	 * Get edge from @p n
	 * @param n pointer to @p n
	 * @return pointer to the incoming edge coming from @p n
	 * @throw NotAdjacentException if @p n is not connected by an incoming edge
	 */
	virtual Edge* edgeFrom(const Node* n) const = 0;
	/**
	 * Get undirected edge to @p n
	 * @param n pointer to @p n
	 * @return pointer to the undirected edge connecting to @p n
	 * @throw NotAdjacentException if @p n is not connected by an undirected edge
	 */
	virtual Edge* undirectedEdgeTo(const Node* n) const = 0;
	/**
	 * Get (any) edge to @p n
	 *
	 * Returns a directed edge to/from or an undirected edge to @p n.
	 * @param n pointer to Node
	 * @return pointer to the edge connecting to @p n
	 * @throw NotAdjacentException if @p n is not adjacent
	 */
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

	/**
	 * Check whether @p n is adjacent to this node
	 * @param n pointer to Node
	 * @return true if @p n is connected to this node by a directed/undirected edge
	 */
	bool isAdjacentTo(const Node* n) const
	{
		return hasEdgeTo(n) || hasEdgeFrom(n) || hasUndirectedEdgeTo(n);
	}
	/**
	 * Get outgoing edges
	 * @return iterator range of outgoing edges
	 */
	virtual edge_iterator_range outEdges() const = 0;
	/**
	 * Get incoming edges
	 * @return iterator range of incoming edges
	 */
	virtual edge_iterator_range inEdges() const = 0;
	/**
	 * Get undirected edges
	 * @return iterator range of undirected edges
	 */
	virtual edge_iterator_range undirectedEdges() const = 0;
	/**
	 * Get outgoing neighbors
	 * @return const iterator range of outgoing neighbors
	 */
	virtual ConstOutNeighborIteratorRange outNeighbors() const = 0;
	/**
	 * Get outgoing neighbors
	 * @return iterator range of outgoing neighbors
	 */
	virtual OutNeighborIteratorRange outNeighbors() = 0;
	/**
	 * Get incoming neighbors
	 * @return const iterator range of incoming neighbors
	 */
	virtual ConstInNeighborIteratorRange inNeighbors() const = 0;
	/**
	 * Get incoming neighbors
	 * @return iterator range of incoming neighbors
	 */
	virtual InNeighborIteratorRange inNeighbors() = 0;
	/**
	 * Get undirected neighbors
	 * @return const iterator range of undirected neighbors
	 * (i.e., which are connected by undirected edges)
	 */
	virtual ConstUndirectedNeighborIteratorRange undirectedNeighbors() const = 0;
	/**
	 * Get undirected neighbors
	 * @return iterator range of undirected neighbors
	 * (i.e., which are connected by undirected edges)
	 */
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
	/**
	 * Register an adjacent edge instance with this node
	 * @param e pointer to Edge
	 */
	virtual void registerEdge(const Edge* e) = 0;
	/**
	 * Unregister an adjacent edge instance from this node (e.g., before
	 * removing the edge)
	 * @param e pointer to edge
	 */
	virtual void unregisterEdge(const Edge* e) = 0;
	/**
	 * Set node ID
	 */
	void setId(node_id_t id)
	{
		id_ = id;
	}

private:
	node_id_t id_;
};

}
#endif /*NODE_H_*/

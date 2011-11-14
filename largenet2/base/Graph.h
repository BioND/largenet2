/**
 * @file Graph.h
 * @date 12.08.2009
 * @author gerd
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <largenet2/base/types.h>
#include <largenet2/base/Node.h>
#include <largenet2/base/Edge.h>
#include <largenet2/base/repo/CPtrRepository.h>
#include <largenet2/base/graph_iterators.h>
#include <boost/noncopyable.hpp>
#include <list>
#include <utility>
#include <memory>
#include <stdexcept>

namespace largenet
{

//class Node;
//class Edge;
class ElementFactory;
class GraphListener;

/**
 * The Graph class
 *
 * A Graph object holds the nodes and links and provides an interface to access,
 * traverse, and modify them.
 */
class Graph: public boost::noncopyable
{
private:
	typedef repo::CPtrRepository<Node> NodeContainer;
	typedef repo::CPtrRepository<Edge> EdgeContainer;
	typedef std::list<GraphListener*> ListenerContainer; // use boost::ptr_list if taking ownership seems better

public:
	/// iterator for all nodes
	typedef iterators::GraphNodeIterator<NodeContainer::iterator> NodeIterator;
	/// iterator for all nodes in given state
	typedef iterators::GraphNodeIterator<NodeContainer::CategoryIterator> NodeStateIterator;
	/// iterator for all edges
	typedef iterators::GraphEdgeIterator<EdgeContainer::iterator> EdgeIterator;
	/// iterator for all edges in given state
	typedef iterators::GraphEdgeIterator<EdgeContainer::CategoryIterator> EdgeStateIterator;
	/// const node iterator
	typedef iterators::GraphNodeIterator<NodeContainer::const_iterator, true> ConstNodeIterator;
	/// const node iterator for all nodes in given state
	typedef iterators::GraphNodeIterator<NodeContainer::ConstCategoryIterator,
			true> ConstNodeStateIterator;
	/// const edge iterator
	typedef iterators::GraphEdgeIterator<EdgeContainer::const_iterator, true> ConstEdgeIterator;
	/// const edge iterator for all edges in given state
	typedef iterators::GraphEdgeIterator<EdgeContainer::ConstCategoryIterator,
			true> ConstEdgeStateIterator;

	/// node iterator range
	typedef std::pair<NodeIterator, NodeIterator> NodeIteratorRange;
	/// node state iterator range
	typedef std::pair<NodeStateIterator, NodeStateIterator> NodeStateIteratorRange;
	/// edge iterator range
	typedef std::pair<EdgeIterator, EdgeIterator> EdgeIteratorRange;
	/// edge state iterator range
	typedef std::pair<EdgeStateIterator, EdgeStateIterator> EdgeStateIteratorRange;
	/// const node iterator range
	typedef std::pair<ConstNodeIterator, ConstNodeIterator> ConstNodeIteratorRange;
	/// const node state iterator range
	typedef std::pair<ConstNodeStateIterator, ConstNodeStateIterator> ConstNodeStateIteratorRange;
	/// const edge iterator range
	typedef std::pair<ConstEdgeIterator, ConstEdgeIterator> ConstEdgeIteratorRange;
	/// const edge state iterator range
	typedef std::pair<ConstEdgeStateIterator, ConstEdgeStateIterator> ConstEdgeStateIteratorRange;

	/**
	 * Create a graph with @p nodeStates possible node states and @p edgeStates
	 * possible edge states.
	 */
	Graph(node_state_t nodeStates, edge_state_t edgeStates);
	/**
	 * Destructor
	 */
	~Graph();
	/**
	 * Assign an element factory used to create nodes and edges.
	 *
	 * The element factory is used to create new nodes and edges when required.
	 * By setting the proper element factory, one can enforce the absence of
	 * parallel links
	 * @see SingleEdgeElementFactory
	 * @see MultiEdgeElementFactory
	 * @param elf std::auto_ptr to a new element factory (note that the Graph
	 * instance takes ownership of the element factory)
	 */
	void setElementFactory(std::auto_ptr<ElementFactory> elf);
	/**
	 * Add a graph listener
	 */
	Graph& addGraphListener(GraphListener* l);
	/**
	 * Remove a registered graph listener
	 */
	void removeGraphListener(GraphListener* l);
	/**
	 * Clear the graph
	 *
	 * Removes all nodes and edges, leaving an empty graph.
	 */
	void clear();
	/**
	 * Get number of nodes
	 */
	node_size_t numberOfNodes() const;
	/**
	 * Get number of nodes in state @p s
	 */
	node_size_t numberOfNodes(node_state_t s) const;
	/**
	 * Get number of edges
	 */
	edge_size_t numberOfEdges() const;
	/**
	 * Get number of edges in state @p s
	 */
	edge_size_t numberOfEdges(edge_state_t s) const;
	/**
	 * Get number of possible node states
	 */
	node_state_size_t numberOfNodeStates() const;
	/**
	 * Get number of possible edge states
	 */
	edge_state_size_t numberOfEdgeStates() const;
	/**
	 * Create a new node.
	 *
	 * The new node is created in state @p 0.
	 * @return node ID of the added node
	 */
	node_id_t addNode();
	/**
	 * Create a new node in state @p s
	 * @return node ID of the added node
	 */
	node_id_t addNode(node_state_t s);
	/**
	 * Create a new edge between @p source and @p target node
	 * @param source source node
	 * @param target target node
	 * @param directed create directed edge?
	 * @return edge ID of the added edge
	 */
	edge_id_t addEdge(node_id_t source, node_id_t target, bool directed);
	/**
	 * Delete node @p n
	 * @param n node ID of the node to delete
	 */
	void removeNode(node_id_t n);
	/**
	 * Delete edge @p e
	 * @param e edge ID of the edge to delete
	 */
	void removeEdge(edge_id_t e);
	/**
	 * Get node with ID @p n
	 * @return pointer to node @p n
	 * @throw std::invalid_argument if node @p n does not exist
	 */
	Node* node(node_id_t n);
	/**
	 * Get node with ID @p n
	 * @return const pointer to node @p n
	 * @throw std::invalid_argument if node @p n does not exist
	 */
	const Node* node(node_id_t n) const;
	/**
	 * Get edge with ID @p e
	 * @return pointer to edge @p e
	 * @throw std::invalid_argument if edge @p e does not exist
	 */
	Edge* edge(edge_id_t e);
	/**
	 * Get edge with ID @p e
	 * @return const pointer to edge @p e
	 * @throw std::invalid_argument if edge @p e does not exist
	 */
	const Edge* edge(edge_id_t e) const;
	/**
	 * Get random node
	 *
	 * A random node is selected using the supplied instance of a random
	 * number generator. @p rnd must provide an IntFromTo(int low, int high) method
	 * returning a random integer in [low, high].
	 * @param rnd instance random number generator
	 * @return pointer to random node
	 * @throw std::invalid_argument if there are no nodes
	 */
	template<class RandomNumGen> Node* randomNode(RandomNumGen& rnd);
	/**
	 * Get random node
	 *
	 * A random node is selected using the supplied instance of a random
	 * number generator. @p rnd must provide an IntFromTo(int low, int high) method
	 * returning a random integer in [low, high].
	 * @param rnd instance random number generator
	 * @return const pointer to random node
	 * @throw std::invalid_argument if there are no nodes
	 */
	template<class RandomNumGen> const Node* randomNode(
			RandomNumGen& rnd) const;
	/**
	 * Get random node in state @p s
	 *
	 * A random node is selected using the supplied instance of a random
	 * number generator. @p rnd must provide an IntFromTo(int low, int high) method
	 * returning a random integer in [low, high].
	 * @param rnd instance random number generator
	 * @param s node state
	 * @return pointer to random node in state @p s
	 * @throw std::invalid_argument if there are no nodes in state @p s
	 */
	template<class RandomNumGen> Node* randomNode(node_state_t s,
			RandomNumGen& rnd);
	/**
	 * Get random node in state @p s
	 *
	 * A random node is selected using the supplied instance of a random
	 * number generator. @p rnd must provide an IntFromTo(int low, int high) method
	 * returning a random integer in [low, high].
	 * @param rnd instance random number generator
	 * @param s node state
	 * @return const pointer to random node in state @p s
	 * @throw std::invalid_argument if there are no nodes in state @p s
	 */
	template<class RandomNumGen> const Node* randomNode(node_state_t s,
			RandomNumGen& rnd) const;
	/**
	 * Get random edge
	 *
	 * A random edge is selected using the supplied instance of a random
	 * number generator. @p rnd must provide an IntFromTo(int low, int high) method
	 * returning a random integer in [low, high].
	 * @param rnd instance random number generator
	 * @return pointer to random edge
	 * @throw std::invalid_argument if there are no edges
	 */
	template<class RandomNumGen> Edge* randomEdge(RandomNumGen& rnd);
	/**
	 * Get random edge
	 *
	 * A random edge is selected using the supplied instance of a random
	 * number generator. @p rnd must provide an IntFromTo(int low, int high) method
	 * returning a random integer in [low, high].
	 * @param rnd instance random number generator
	 * @return const pointer to random edge
	 * @throw std::invalid_argument if there are no edges
	 */
	template<class RandomNumGen> const Edge* randomEdge(
			RandomNumGen& rnd) const;
	/**
	 * Get random edge in state @p s
	 *
	 * A random edge is selected using the supplied instance of a random
	 * number generator. @p rnd must provide an IntFromTo(int low, int high) method
	 * returning a random integer in [low, high].
	 * @param rnd instance random number generator
	 * @param s edge state
	 * @return pointer to random edge in state @p s
	 * @throw std::invalid_argument if there are no edges in state @p s
	 */
	template<class RandomNumGen> Edge* randomEdge(edge_state_t s,
			RandomNumGen& rnd);
	/**
	 * Get random edge in state @p s
	 *
	 * A random edge is selected using the supplied instance of a random
	 * number generator. @p rnd must provide an IntFromTo(int low, int high) method
	 * returning a random integer in [low, high].
	 * @param rnd instance random number generator
	 * @param s edge state
	 * @return const pointer to random edge in state @p s
	 * @throw std::invalid_argument if there are no edges in state @p s
	 */
	template<class RandomNumGen> const Edge* randomEdge(edge_state_t s,
			RandomNumGen& rnd) const;

	/**
	 * Set state of node @p n to @p s
	 * @param n node ID
	 * @param s new node state
	 */
	void setNodeState(node_id_t n, node_state_t s);
	/**
	 * Set state of edge @p e to @p s
	 * @param e edge ID
	 * @param s new edge state
	 */
	void setEdgeState(edge_id_t e, edge_state_t s);
	/**
	 * Get node state of node @p n
	 * @param n node ID
	 */
	node_state_t nodeState(node_id_t n) const;
	/**
	 * Get edge state of edge @p e
	 * @param e edge ID
	 */
	edge_state_t edgeState(edge_id_t e) const;

	/**
	 * Get nodes
	 * @return iterator range for all nodes
	 */
	NodeIteratorRange nodes();
	/**
	 * Get nodes
	 * @return const interator range for all nodes
	 */
	ConstNodeIteratorRange nodes() const;
	/**
	 * Get edges
	 * @return iterator range for all edges
	 */
	EdgeIteratorRange edges();
	/**
	 * Get edges
	 * @return const iterator range for all edges
	 */
	ConstEdgeIteratorRange edges() const;
	/**
	 * Get nodes in state @p s
	 * @return iterator range for all nodes in state @p s
	 */
	NodeStateIteratorRange nodes(node_state_t s);
	/**
	 * Get nodes in state @p s
	 * @return const iterator range for all nodes in state @p s
	 */
	ConstNodeStateIteratorRange nodes(node_state_t s) const;
	/**
	 * Get edges in state @p s
	 * @return iterator range for all edges in state @p s
	 */
	EdgeStateIteratorRange edges(edge_state_t s);
	/**
	 * Get edges in state @p s
	 * @return const iterator range for all edges in state @p s
	 */
	ConstEdgeStateIteratorRange edges(edge_state_t s) const;
	/**
	 * Check whether there exists a directed or undirected edge from @p source
	 * to @p target
	 */
	bool isEdge(node_id_t source, node_id_t target) const;
	/**
	 * Check whether two nodes are connected by an edge
	 */
	bool adjacent(node_id_t n1, node_id_t n2) const;

private:
	void afterNodeAdd(node_id_t n);
	void afterEdgeAdd(edge_id_t e);
	void beforeNodeRemove(node_id_t n);
	void beforeEdgeRemove(edge_id_t e);
	void beforeGraphClear();
	void afterNodeStateChange(node_id_t n, node_state_t oldState,
			node_state_t newState);
	void afterEdgeStateChange(edge_id_t e, edge_state_t oldState,
			edge_state_t newState);

	std::auto_ptr<ElementFactory> elf_;
	NodeContainer nodes_;
	EdgeContainer edges_;
	ListenerContainer listeners_;
};

inline node_size_t Graph::numberOfNodes() const
{
	return nodes_.size();
}

inline node_size_t Graph::numberOfNodes(const node_state_t s) const
{
	return nodes_.count(s);
}

inline edge_size_t Graph::numberOfEdges() const
{
	return edges_.size();
}

inline edge_size_t Graph::numberOfEdges(const edge_state_t s) const
{
	return edges_.count(s);
}

inline node_state_size_t Graph::numberOfNodeStates() const
{
	return nodes_.numberOfCategories();
}

inline edge_state_size_t Graph::numberOfEdgeStates() const
{
	return edges_.numberOfCategories();
}

inline Node* Graph::node(const node_id_t n)
{
	if (nodes_.valid(n))
		return &nodes_[n];
	else
		throw(std::invalid_argument("Invalid node ID."));
}

inline const Node* Graph::node(const node_id_t n) const
{
	if (nodes_.valid(n))
		return &nodes_[n];
	else
		throw(std::invalid_argument("Invalid node ID."));
}

inline Edge* Graph::edge(const edge_id_t e)
{
	if (edges_.valid(e))
		return &edges_[e];
	else
		throw(std::invalid_argument("Invalid edge ID."));
}

inline const Edge* Graph::edge(const edge_id_t e) const
{
	if (edges_.valid(e))
		return &edges_[e];
	else
		throw(std::invalid_argument("Invalid edge ID."));
}

inline node_state_t Graph::nodeState(const node_id_t n) const
{
	return nodes_.category(n);
}

inline edge_state_t Graph::edgeState(const edge_id_t e) const
{
	return edges_.category(e);
}

inline void Graph::setElementFactory(std::auto_ptr<ElementFactory> elf)
{
	if (elf_.get() != elf.get())
		elf_ = elf; // releases and destroys old factory (auto_ptr assignment is elf_.reset(elf.release()))
}

inline Graph& Graph::addGraphListener(GraphListener* l)
{
	listeners_.push_back(l);
	return *this; // for convenience
}

inline void Graph::removeGraphListener(GraphListener* l)
{
	listeners_.remove(l);
}

template<class RandomNumGen>
const Node* Graph::randomNode(RandomNumGen& rnd) const
{
	if (numberOfNodes() == 0)
		throw(std::invalid_argument("Cannot pick random node from empty set."));
	return node(
			nodes_.id(
					static_cast<repo::address_t>(rnd.IntFromTo(0,
							nodes_.size() - 1))));
}

template<class RandomNumGen>
Node* Graph::randomNode(RandomNumGen& rnd)
{
	if (numberOfNodes() == 0)
		throw(std::invalid_argument("Cannot pick random node from empty set."));
	return node(
			nodes_.id(
					static_cast<repo::address_t>(rnd.IntFromTo(0,
							nodes_.size() - 1))));
}

template<class RandomNumGen>
const Node* Graph::randomNode(const node_state_t s, RandomNumGen& rnd) const
{
	if (numberOfNodes(s) == 0)
		throw(std::invalid_argument("Cannot pick random node from empty set."));
	return node(
			nodes_.id(
					s,
					static_cast<repo::address_t>(rnd.IntFromTo(0,
							nodes_.count(s) - 1))));
}

template<class RandomNumGen>
Node* Graph::randomNode(const node_state_t s, RandomNumGen& rnd)
{
	if (numberOfNodes(s) == 0)
		throw(std::invalid_argument("Cannot pick random node from empty set."));
	return node(
			nodes_.id(
					s,
					static_cast<repo::address_t>(rnd.IntFromTo(0,
							nodes_.count(s) - 1))));
}

template<class RandomNumGen>
const Edge* Graph::randomEdge(RandomNumGen& rnd) const
{
	if (numberOfEdges() == 0)
		throw(std::invalid_argument("Cannot pick random edge from empty set."));
	return edge(
			edges_.id(
					static_cast<repo::address_t>(rnd.IntFromTo(0,
							edges_.size() - 1))));
}

template<class RandomNumGen>
Edge* Graph::randomEdge(RandomNumGen& rnd)
{
	if (numberOfEdges() == 0)
		throw(std::invalid_argument("Cannot pick random edge from empty set."));
	return edge(
			edges_.id(
					static_cast<repo::address_t>(rnd.IntFromTo(0,
							edges_.size() - 1))));
}

template<class RandomNumGen>
const Edge* Graph::randomEdge(const edge_state_t s, RandomNumGen& rnd) const
{
	if (numberOfEdges(s) == 0)
		throw(std::invalid_argument("Cannot pick random edge from empty set."));
	return edge(
			edges_.id(
					s,
					static_cast<repo::address_t>(rnd.IntFromTo(0,
							edges_.count(s) - 1))));
}

template<class RandomNumGen>
Edge* Graph::randomEdge(const edge_state_t s, RandomNumGen& rnd)
{
	if (numberOfEdges(s) == 0)
		throw(std::invalid_argument("Cannot pick random edge from empty set."));
	return edge(
			edges_.id(
					s,
					static_cast<repo::address_t>(rnd.IntFromTo(0,
							edges_.count(s) - 1))));
}

}

#endif /* GRAPH_H_ */

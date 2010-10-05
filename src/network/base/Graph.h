/**
 * @file Graph.h
 * @date 12.08.2009
 * @author gerd
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "types.h"
#include "Node.h"
#include "Edge.h"
#include "../../repo/CPtrRepository.h"
#include "graph_iterators.h"
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

class Graph: public boost::noncopyable
{
private:
	typedef repo::CPtrRepository<Node> NodeContainer;
	typedef repo::CPtrRepository<Edge> EdgeContainer;
	typedef std::list<GraphListener*> ListenerContainer; // use boost::ptr_list if taking ownership seems better

public:
	typedef iterators::GraphNodeIterator<NodeContainer::iterator> NodeIterator;
	typedef iterators::GraphNodeIterator<NodeContainer::CategoryIterator>
			NodeStateIterator;
	typedef iterators::GraphEdgeIterator<EdgeContainer::iterator> EdgeIterator;
	typedef iterators::GraphEdgeIterator<EdgeContainer::CategoryIterator>
			EdgeStateIterator;
	typedef iterators::GraphNodeIterator<NodeContainer::const_iterator, true>
			ConstNodeIterator;
	typedef iterators::GraphNodeIterator<NodeContainer::ConstCategoryIterator,
			true> ConstNodeStateIterator;
	typedef iterators::GraphEdgeIterator<EdgeContainer::const_iterator, true>
			ConstEdgeIterator;
	typedef iterators::GraphEdgeIterator<EdgeContainer::ConstCategoryIterator,
			true> ConstEdgeStateIterator;

	typedef std::pair<NodeIterator, NodeIterator> NodeIteratorRange;
	typedef std::pair<NodeStateIterator, NodeStateIterator>
			NodeStateIteratorRange;
	typedef std::pair<EdgeIterator, EdgeIterator> EdgeIteratorRange;
	typedef std::pair<EdgeStateIterator, EdgeStateIterator>
			EdgeStateIteratorRange;
	typedef std::pair<ConstNodeIterator, ConstNodeIterator>
			ConstNodeIteratorRange;
	typedef std::pair<ConstNodeStateIterator, ConstNodeStateIterator>
			ConstNodeStateIteratorRange;
	typedef std::pair<ConstEdgeIterator, ConstEdgeIterator>
			ConstEdgeIteratorRange;
	typedef std::pair<ConstEdgeStateIterator, ConstEdgeStateIterator>
			ConstEdgeStateIteratorRange;

	Graph(node_state_t nodeStates, edge_state_t edgeStates);
	~Graph();
	void setElementFactory(std::auto_ptr<ElementFactory> elf);
	Graph& addGraphListener(GraphListener* l);
	void removeGraphListener(GraphListener* l);
	void clear();

	node_size_t numberOfNodes() const;
	node_size_t numberOfNodes(node_state_t s) const;
	edge_size_t numberOfEdges() const;
	edge_size_t numberOfEdges(edge_state_t s) const;

	node_state_size_t numberOfNodeStates() const;
	edge_state_size_t numberOfEdgeStates() const;

	node_id_t addNode();
	node_id_t addNode(node_state_t s);
	edge_id_t addEdge(node_id_t source, node_id_t target, bool directed = false);
	void removeNode(node_id_t n);
	void removeEdge(edge_id_t e);
	Node* node(node_id_t n);
	const Node* node(node_id_t n) const;
	Edge* edge(edge_id_t e);
	const Edge* edge(edge_id_t e) const;

	template<class RandomNumGen> Node* randomNode(RandomNumGen& rnd);
	template<class RandomNumGen> const Node* randomNode(RandomNumGen& rnd) const;
	template<class RandomNumGen> Node* randomNode(node_state_t s,
			RandomNumGen& rnd);
	template<class RandomNumGen> const Node* randomNode(node_state_t s,
			RandomNumGen& rnd) const;
	template<class RandomNumGen> Edge* randomEdge(RandomNumGen& rnd);
	template<class RandomNumGen> const Edge* randomEdge(RandomNumGen& rnd) const;
	template<class RandomNumGen> Edge* randomEdge(edge_state_t s,
			RandomNumGen& rnd);
	template<class RandomNumGen> const Edge* randomEdge(edge_state_t s,
			RandomNumGen& rnd) const;

	void setNodeState(node_id_t n, node_state_t s);
	void setEdgeState(edge_id_t e, edge_state_t s);
	node_state_t nodeState(node_id_t n) const;
	edge_state_t edgeState(edge_id_t e) const;

	NodeIteratorRange nodes();
	ConstNodeIteratorRange nodes() const;
	EdgeIteratorRange edges();
	ConstEdgeIteratorRange edges() const;

	NodeStateIteratorRange nodes(node_state_t s);
	ConstNodeStateIteratorRange nodes(node_state_t s) const;
	EdgeStateIteratorRange edges(edge_state_t s);
	ConstEdgeStateIteratorRange edges(edge_state_t s) const;

	bool isEdge(node_id_t source, node_id_t target) const;
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
	return node(nodes_.id(static_cast<repo::address_t> (rnd.IntFromTo(0,
			nodes_.size() - 1))));
}

template<class RandomNumGen>
Node* Graph::randomNode(RandomNumGen& rnd)
{
	if (numberOfNodes() == 0)
		throw(std::invalid_argument("Cannot pick random node from empty set."));
	return node(nodes_.id(static_cast<repo::address_t> (rnd.IntFromTo(0,
			nodes_.size() - 1))));
}

template<class RandomNumGen>
const Node* Graph::randomNode(const node_state_t s, RandomNumGen& rnd) const
{
	if (numberOfNodes(s) == 0)
		throw(std::invalid_argument("Cannot pick random node from empty set."));
	return node(nodes_.id(s, static_cast<repo::address_t> (rnd.IntFromTo(0,
			nodes_.count(s) - 1))));
}

template<class RandomNumGen>
Node* Graph::randomNode(const node_state_t s, RandomNumGen& rnd)
{
	if (numberOfNodes(s) == 0)
		throw(std::invalid_argument("Cannot pick random node from empty set."));
	return node(nodes_.id(s, static_cast<repo::address_t> (rnd.IntFromTo(0,
			nodes_.count(s) - 1))));
}

template<class RandomNumGen>
const Edge* Graph::randomEdge(RandomNumGen& rnd) const
{
	if (numberOfEdges() == 0)
		throw(std::invalid_argument("Cannot pick random edge from empty set."));
	return edge(edges_.id(static_cast<repo::address_t> (rnd.IntFromTo(0,
			edges_.size() - 1))));
}

template<class RandomNumGen>
Edge* Graph::randomEdge(RandomNumGen& rnd)
{
	if (numberOfEdges() == 0)
		throw(std::invalid_argument("Cannot pick random edge from empty set."));
	return edge(edges_.id(static_cast<repo::address_t> (rnd.IntFromTo(0,
			edges_.size() - 1))));
}

template<class RandomNumGen>
const Edge* Graph::randomEdge(const edge_state_t s, RandomNumGen& rnd) const
{
	if (numberOfEdges(s) == 0)
		throw(std::invalid_argument("Cannot pick random edge from empty set."));
	return edge(edges_.id(s, static_cast<repo::address_t> (rnd.IntFromTo(0,
			edges_.count(s) - 1))));
}

template<class RandomNumGen>
Edge* Graph::randomEdge(const edge_state_t s, RandomNumGen& rnd)
{
	if (numberOfEdges(s) == 0)
		throw(std::invalid_argument("Cannot pick random edge from empty set."));
	return edge(edges_.id(s, static_cast<repo::address_t> (rnd.IntFromTo(0,
			edges_.count(s) - 1))));
}

}

#endif /* GRAPH_H_ */

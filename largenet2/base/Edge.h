/**
 * @file Edge.h
 * @date 12.08.2009
 * @author gerd
 */

#ifndef EDGE_H_
#define EDGE_H_

#include <largenet2/base/types.h>
#include <largenet2/base/exceptions.h>
#include <boost/noncopyable.hpp>

namespace largenet
{

class Node;

/**
 * An edge.
 */
class Edge: public boost::noncopyable
{
protected:
	/**
	 * Constructor
	 */
	Edge() : id_(0), source_(0), target_(0) {}
	/**
	 * Constructor
	 * @param id Edge ID
	 * @param source source node
	 * @param target target node
	 * @param directed create directed edge?
	 */
	Edge(edge_id_t id, Node& source, Node& target, bool directed) :
		id_(id), source_(&source), target_(&target), directed_(directed)
	{}
public:
	/*
	 * Force creation via factory function, as we cannot call virtual functions in
	 * constructor (needed in Edge::connect()).
	 */
	/**
	 * Edge factory method.
	 *
	 * Creates a new edge.
	 * @param id Edge ID
	 * @param source source node
	 * @param target target node
	 * @param directed create directed edge?
	 * @return
	 */
	static Edge* create(edge_id_t id, Node& source, Node& target, bool directed);
	/**
	 * Destructor
	 *
	 * Unregisters this edge from source and target nodes.
	 */
	virtual ~Edge() { disconnect(); }
	/**
	 * Check whether the edge is directed.
	 */
	bool isDirected() const { return directed_; }
	/**
	 * Get edge ID
	 * @return edge ID
	 */
	edge_id_t id() const { return id_; }
	/**
	 * Get source node
	 * @return pointer to source node
	 */
	Node* source() const { return source_; }
	/**
	 * Get target node
	 * @return pointer to target node
	 */
	Node* target() const { return target_; }
	/**
	 * Get opposite node
	 *
	 * If @p from is the source node, returns the target node, and vice versa.
	 * @param from source or target node
	 * @return opposite node
	 * @throw std::invalid_argument if @p from is not attached to this edge
	 */
	Node* opposite(const Node& from) const;
	/**
	 * Check whether the edge is a loop, i.e. source and target are the same.
	 * @return true if edge is a loop
	 */
	bool isLoop() const { return source_ == target_; }
	/**
	 * Check for equality.
	 *
	 * Two edges are considered to be equal iff they connect the same source and target
	 * and have the same directionality.
	 * Note that for undirected edges, source and target can be interchanged.
	 * @param e other edge
	 * @return true if equal
	 */
	bool operator==(const Edge& e) const;
	/**
	 * Check if this edge comes from node @p from
	 *
	 * For directed edges, checks whether source == @p from. For undirected
	 * edges, checks whether either source == @p from or target == @p from.
	 * @param from node
	 * @return true if edge comes from @p from
	 */
	bool from(const Node& from) const
	{
		if (directed_)
			return source_ == &from;
		else
			return (source_ == &from) || (target_ == &from);
	}
	/**
	 * Check if this edge goes to node @p to
	 *
	 * For directed edges, checks whether source == @p to. For undirected
	 * edges, checks whether either source == @p to or target == @p to.
	 * @param to node
	 * @return true if edge goes to @p to
	 */
	bool to(const Node& to) const
	{
		if (directed_)
			return target_ == &to;
		else
			return (source_ == &to) || (target_ == &to);
	}

protected:
	/**
	 * Connect and register with source and target nodes.
	 */
	void connect();
	/**
	 * Disconnect and unregister from source and target nodes.
	 */
	void disconnect();

private:
	edge_id_t id_;
	Node* source_;
	Node* target_;
	bool directed_;
};

inline Edge* Edge::create(const edge_id_t id, Node& source, Node& target, bool directed)
{
	Edge* e = new Edge(id, source, target, directed);
	try
	{
		e->connect();
	} catch (largenet::SingletonException&)
	{
		delete e;
		throw ;
	}
	return e;
}

inline bool Edge::operator ==(const Edge& e) const
{
	bool val = (source_ == e.source_) && (target_ == e.target_);
	if (!directed_)
		val |= ((source_ == e.target_) && (target_ == e.source_));
	val &=  (directed_ == e.directed_);
	return val;
}

}
#endif /* EDGE_H_ */

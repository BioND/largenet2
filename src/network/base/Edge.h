/**
 * @file Edge.h
 * @date 12.08.2009
 * @author gerd
 */

#ifndef EDGE_H_
#define EDGE_H_

#include "types.h"
#include "exceptions.h"
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
	Edge() : id_(0), source_(0), target_(0) {}
	Edge(edge_id_t id, Node& source, Node& target, bool directed) : id_(id), source_(&source), target_(&target), directed_(directed) {}
public:
	/**
	 * Force creation via factory function, as we cannot call virtual functions in
	 * constructor (needed in Edge::connect()).
	 */
	static Edge* create(edge_id_t id, Node& source, Node& target, bool directed);
	virtual ~Edge() { disconnect(); }
	bool isDirected() const { return directed_; }
	edge_id_t id() const { return id_; }
	Node* source() const { return source_; }
	Node* target() const { return target_; }
	Node* opposite(const Node& from) const;
	bool isLoop() const { return source_ == target_; }
	bool operator==(const Edge& e) const;
	bool from(const Node& from) const { if (directed_) return source_ == &from; else return (source_ == &from) || (target_ == &from); }
	bool to(const Node& to) const { if (directed_) return target_ == &to; else return (source_ == &to) || (target_ == &to); }

protected:
	void connect();
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

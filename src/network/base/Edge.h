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
 * A directed edge.
 */
class Edge: public boost::noncopyable
{
protected:
	Edge() : id_(0), source_(0), target_(0) {}
	Edge(edge_id_t id, Node& source, Node& target) : id_(id), source_(&source), target_(&target) {}
public:
	/**
	 * Force creation via factory function, as we cannot call virtual functions in
	 * constructor (needed in Edge::connect()).
	 */
	static Edge* create(edge_id_t id, Node& source, Node& target);
	virtual ~Edge() { disconnect(); }
	bool isDirected() const { return directed(); }
	edge_id_t id() const { return id_; }
	Node* source() const { return source_; }
	Node* target() const { return target_; }
	Node* opposite(const Node& from) const;
	bool isLoop() const { return source_ == target_; }
	bool operator==(const Edge& e) const { return isEqual(e); }
	bool from(const Node& from) const { return isFrom(from); }
	bool to(const Node& to) const { return isTo(to); }

protected:
	void connect();
	void disconnect();

private:
	virtual bool directed() const { return true; }
	virtual bool isEqual(const Edge& e) const { return (source_ == e.source_) && (target_ == e.target_); }
	virtual bool isFrom(const Node& from) const { return source_ == &from; }
	virtual bool isTo(const Node& to) const { return target_ == &to; }
	edge_id_t id_;
	Node* source_;
	Node* target_;
};

inline Edge* Edge::create(const edge_id_t id, Node& source, Node& target)
{
	Edge* e = new Edge(id, source, target);
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

typedef Edge DirectedEdge;

class UndirectedEdge: public Edge
{
private:
	UndirectedEdge() : Edge() {}
	UndirectedEdge(edge_id_t id, Node& source, Node& target);
public:
	static UndirectedEdge* create(edge_id_t id, Node& source, Node& target);
	virtual ~UndirectedEdge() {}
private:
	bool directed() const { return false; }
	bool isEqual(const Edge& e) const;
	bool isFrom(const Node& from) const { return (source() == &from) || (target() == &from); }
	bool isTo(const Node& to) const { return (target() == &to) || (source() == &to); }
};

inline UndirectedEdge* UndirectedEdge::create(const edge_id_t id, Node& source, Node& target)
{
	UndirectedEdge* e = new UndirectedEdge(id, source, target);
	try
	{
		e->connect();
	}
	catch (SingletonException&)
	{
		delete e;
		throw;
	}
	return e;
}

inline bool UndirectedEdge::isEqual(const Edge& e) const
{
	return ((source() == e.source()) && (target() == e.target())) || ((source() == e.target()) && (target() == e.source()));
}

template<class E>
inline bool is_directed(const E*);

template<>
inline bool is_directed<DirectedEdge>(const DirectedEdge*)
{
	return true;
}

template<>
inline bool is_directed<UndirectedEdge>(const UndirectedEdge*)
{
	return false;
}


}

#endif /* EDGE_H_ */

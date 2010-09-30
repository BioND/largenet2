/**
 * @file graph_iterators.h
 * @date 08.10.2009
 * @author gerd
 */

#ifndef GRAPH_ITERATORS_H_
#define GRAPH_ITERATORS_H_

#include "types.h"
#include "Node.h"
#include "Edge.h"
#include "../../util/choosetype.h"
#include <iterator>

namespace largenet
{

//class Node;
//class Edge;

namespace iterators
{

template<class Iterator, bool is_const = false>
class GraphNodeIterator
{
public:
	typedef typename std::iterator_traits<Iterator>::value_type value_type;
	typedef typename choose_type<is_const, const typename std::iterator_traits<
			Iterator>::reference,
			typename std::iterator_traits<Iterator>::reference>::type reference;
	typedef const typename std::iterator_traits<Iterator>::reference
			const_reference;
	typedef typename choose_type<is_const, const typename std::iterator_traits<
			Iterator>::pointer,
			typename std::iterator_traits<Iterator>::pointer>::type pointer;
	typedef node_id_t difference_type;
	typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename choose_type<is_const, const Node*, Node*>::type node_pointer;

	explicit GraphNodeIterator(const Iterator& i) :
		it_(i)
	{
	}
	GraphNodeIterator()
	{
	}
	GraphNodeIterator(const GraphNodeIterator& other) :
		it_(other.it_)
	{
	}
	typename choose_type<is_const, const node_id_t, node_id_t>::type id()
	{
		return it_.id();
	}
	typename choose_type<is_const, const_reference, reference>::type operator*()
	{
		return *it_;
	}
	node_pointer operator->()
	{
		return &(*it_);
	}
	GraphNodeIterator& operator=(const GraphNodeIterator& i)
	{
		if (&i != this)
			it_ = i.it_;
		return *this;
	}

	friend bool operator==(const GraphNodeIterator& a, const GraphNodeIterator& b)
	{
		return a.it_ == b.it_;
	}
	friend bool operator!=(const GraphNodeIterator& a, const GraphNodeIterator& b)
	{
		return a.it_ != b.it_;
	}
	GraphNodeIterator& operator++()
	{
		++it_;
		return *this;
	}
	GraphNodeIterator operator++(int)
	{
		GraphNodeIterator temp(*this);
		++(*this);
		return temp;
	}
private:
	Iterator it_;
};

template<class Iterator, bool is_const = false>
class GraphEdgeIterator
{
public:
	typedef typename std::iterator_traits<Iterator>::value_type value_type;
	typedef typename choose_type<is_const, const typename std::iterator_traits<
			Iterator>::reference,
			typename std::iterator_traits<Iterator>::reference>::type reference;
	typedef const typename std::iterator_traits<Iterator>::reference
			const_reference;
	typedef typename choose_type<is_const, const typename std::iterator_traits<
			Iterator>::pointer,
			typename std::iterator_traits<Iterator>::pointer>::type pointer;
	typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
	typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;

	typedef typename choose_type<is_const, const Edge*, Edge*>::type edge_pointer;

	explicit GraphEdgeIterator(const Iterator& i) :
		it_(i)
	{
	}
	GraphEdgeIterator()
	{
	}
	GraphEdgeIterator(const GraphEdgeIterator& other) :
		it_(other.it_)
	{
	}
	typename choose_type<is_const, const edge_id_t, edge_id_t>::type id()
	{
		return it_.id();
	}
	typename choose_type<is_const, const_reference, reference>::type operator*()
	{
		return *it_;
	}
	edge_pointer operator->()
	{
		return &(*it_);
	}
	GraphEdgeIterator& operator=(const GraphEdgeIterator& i)
	{
		if (&i != this)
			it_ = i.it_;
		return *this;
	}
	friend bool operator==(const GraphEdgeIterator& a, const GraphEdgeIterator& b)
	{
		return a.it_ == b.it_;
	}
	friend bool operator!=(const GraphEdgeIterator& a, const GraphEdgeIterator& b)
	{
		return a.it_ != b.it_;
	}
	GraphEdgeIterator& operator++()
	{
		++it_;
		return *this;
	}
	GraphEdgeIterator operator++(int)
	{
		GraphEdgeIterator temp(*this);
		++(*this);
		return temp;
	}
private:
	Iterator it_;
};
}
}

#endif /* GRAPH_ITERATORS_H_ */

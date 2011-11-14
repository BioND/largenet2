/**
 * @file graph_iterators.h
 * @date 08.10.2009
 * @author gerd
 */

#ifndef GRAPH_ITERATORS_H_
#define GRAPH_ITERATORS_H_

#include <largenet2/base/types.h>
#include <largenet2/base/Node.h>
#include <largenet2/base/Edge.h>
#include <largenet2/util/choosetype.h>
#include <iterator>

namespace largenet
{

//class Node;
//class Edge;

namespace iterators
{

/**
 * Iterator for nodes
 */
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

	/**
	 * Constructor
	 * @param i iterator instance this GraphNodeIterator encapsulates
	 */
	explicit GraphNodeIterator(const Iterator& i) :
		it_(i)
	{
	}
	/**
	 * Default constructor
	 */
	GraphNodeIterator()
	{
	}
	/**
	 * Copy constructor
	 * @param other iterator to copy
	 */
	GraphNodeIterator(const GraphNodeIterator& other) :
		it_(other.it_)
	{
	}
	/**
	 * Get iterator ID
	 * @return iterator ID
	 */
	typename choose_type<is_const, const node_id_t, node_id_t>::type id()
	{
		return it_.id();
	}
	/**
	 * Dereference operator
	 * @return reference
	 */
	typename choose_type<is_const, const_reference, reference>::type operator*()
	{
		return *it_;
	}
	/**
	 * Pointer operator
	 * @return pointer
	 */
	node_pointer operator->()
	{
		return &(*it_);
	}
	/**
	 * Assignment operator
	 */
	GraphNodeIterator& operator=(const GraphNodeIterator& i)
	{
		if (&i != this)
			it_ = i.it_;
		return *this;
	}

	/**
	 * Check for equality
	 * @return true if equal
	 */
	friend bool operator==(const GraphNodeIterator& a, const GraphNodeIterator& b)
	{
		return a.it_ == b.it_;
	}
	/**
	 * Check for inequality
	 * @return true if unequal
	 */
	friend bool operator!=(const GraphNodeIterator& a, const GraphNodeIterator& b)
	{
		return a.it_ != b.it_;
	}
	/**
	 * Increment operator (prefix)
	 */
	GraphNodeIterator& operator++()
	{
		++it_;
		return *this;
	}
	/**
	 * Increment operator (postfix)
	 */
	GraphNodeIterator operator++(int)
	{
		GraphNodeIterator temp(*this);
		++(*this);
		return temp;
	}
private:
	Iterator it_;
};

/**
 * Iterator for edges
 */
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

	/**
	 * Constructor
	 * @param i iterator instance this GraphEdgeIterator encapsulates
	 */
	explicit GraphEdgeIterator(const Iterator& i) :
		it_(i)
	{
	}
	/**
	 * Default constructor
	 */
	GraphEdgeIterator()
	{
	}
	/**
	 * Copy constructor
	 */
	GraphEdgeIterator(const GraphEdgeIterator& other) :
		it_(other.it_)
	{
	}
	/**
	 * Iterator ID
	 */
	typename choose_type<is_const, const edge_id_t, edge_id_t>::type id()
	{
		return it_.id();
	}
	/**
	 * Dereference operator
	 * @return reference
	 */
	typename choose_type<is_const, const_reference, reference>::type operator*()
	{
		return *it_;
	}
	/**
	 * Pointer operator
	 */
	edge_pointer operator->()
	{
		return &(*it_);
	}
	/**
	 * Assignment operator
	 */
	GraphEdgeIterator& operator=(const GraphEdgeIterator& i)
	{
		if (&i != this)
			it_ = i.it_;
		return *this;
	}
	/**
	 * Check for equality
	 */
	friend bool operator==(const GraphEdgeIterator& a, const GraphEdgeIterator& b)
	{
		return a.it_ == b.it_;
	}
	/**
	 * Check for unequality
	 */
	friend bool operator!=(const GraphEdgeIterator& a, const GraphEdgeIterator& b)
	{
		return a.it_ != b.it_;
	}
	/**
	 * Increment operator (prefix)
	 */
	GraphEdgeIterator& operator++()
	{
		++it_;
		return *this;
	}
	/**
	 * Increment operator (postfix)
	 */
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

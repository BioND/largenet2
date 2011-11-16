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
	typedef typename choose_type<is_const,
			const typename std::iterator_traits<Iterator>::reference,
			typename std::iterator_traits<Iterator>::reference>::type reference;
	typedef const typename std::iterator_traits<Iterator>::reference const_reference;
	typedef typename choose_type<is_const,
			const typename std::iterator_traits<Iterator>::pointer,
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
	template<bool other_is_const>
	GraphNodeIterator(const GraphNodeIterator<Iterator, other_is_const>& other) :
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
	template<bool other_is_const>
	GraphNodeIterator& operator=(
			const GraphNodeIterator<Iterator, other_is_const>& i)
	{
		if (it_ != i.it_)
			it_ = i.it_;
		return *this;
	}

	/**
	 * Check for equality
	 * @return true if equal
	 */
	template<bool other_is_const>
	bool operator==(const GraphNodeIterator<Iterator, other_is_const>& it) const
	{
		return it_ == it.it_;
	}
	/**
	 * Check for inequality
	 * @return true if unequal
	 */
	template<bool other_is_const>
	bool operator!=(const GraphNodeIterator<Iterator, other_is_const>& it) const
	{
		return !operator==(it);
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
	template<class I, bool c> friend class GraphNodeIterator;
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
	typedef typename choose_type<is_const,
			const typename std::iterator_traits<Iterator>::reference,
			typename std::iterator_traits<Iterator>::reference>::type reference;
	typedef const typename std::iterator_traits<Iterator>::reference const_reference;
	typedef typename choose_type<is_const,
			const typename std::iterator_traits<Iterator>::pointer,
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
	template<bool other_is_const>
	GraphEdgeIterator(const GraphEdgeIterator<Iterator, other_is_const>& other) :
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
	template<bool other_is_const>
	GraphEdgeIterator& operator=(
			const GraphEdgeIterator<Iterator, other_is_const>& i)
	{
		if (it_ != i.it_)
			it_ = i.it_;
		return *this;
	}
	/**
	 * Check for equality
	 */
	template<bool other_is_const>
	bool operator==(const GraphEdgeIterator<Iterator, other_is_const>& it) const
	{
		return it_ == it.it_;
	}
	/**
	 * Check for unequality
	 */
	template<bool other_is_const>
	bool operator!=(const GraphEdgeIterator<Iterator, other_is_const>& it) const
	{
		return it_ != it.it_;
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
	template<class I, bool c> friend class GraphEdgeIterator;
	Iterator it_;
};
}
}

#endif /* GRAPH_ITERATORS_H_ */

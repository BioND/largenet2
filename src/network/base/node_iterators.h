/**
 * @file node_iterators.h
 * @date 02.11.2009
 * @author gerd
 */

#ifndef NODE_ITERATORS_H_
#define NODE_ITERATORS_H_

#include "types.h"
#include "../../util/choosetype.h"
#include <iterator>

namespace largenet
{

class Node;

namespace iterators
{

template<class Iterator, bool is_const = false>
class NodeOutNeighborIterator
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
	typedef typename std::iterator_traits<Iterator>::iterator_category
			iterator_category;
	typedef typename choose_type<is_const, const Node*, Node*>::type
			node_pointer;

	explicit NodeOutNeighborIterator(const Iterator& i, const node_id_t nid) :
		it_(i), nid_(nid)
	{
	}
	NodeOutNeighborIterator()
	{
	}
	NodeOutNeighborIterator(const NodeOutNeighborIterator& other, const node_id_t nid) :
		it_(other.it_), nid_(nid)
	{
	}
	typename choose_type<is_const, const node_id_t, node_id_t>::type operator*()
	{
		if ((*it_)->isDirected())
			return (*it_)->target()->id();
		else
			return ((nid_ == (*it_)->target()->id()) ? (*it_)->source()->id() : (*it_)->target()->id());
	}

	node_pointer operator->()
	{
		if ((*it_)->isDirected())
			return (*it_)->target();
		else
			return ((nid_ == (*it_)->target()->id()) ? (*it_)->source() : (*it_)->target());
	}

	NodeOutNeighborIterator& operator=(const NodeOutNeighborIterator& i)
	{
		if (&i != this)
			it_ = i.it_;
		return *this;
	}

	friend bool operator==(const NodeOutNeighborIterator& a,
			const NodeOutNeighborIterator& b)
	{
		return a.it_ == b.it_;
	}
	friend bool operator!=(const NodeOutNeighborIterator& a,
			const NodeOutNeighborIterator& b)
	{
		return a.it_ != b.it_;
	}
	NodeOutNeighborIterator& operator++()
	{
		++it_;
		return *this;
	}
	NodeOutNeighborIterator operator++(int)
	{
		NodeOutNeighborIterator temp(*this);
		++(*this);
		return temp;
	}
	NodeOutNeighborIterator& operator--()
	{
		--it_;
		return *this;
	}
	NodeOutNeighborIterator operator--(int)
	{
		NodeOutNeighborIterator temp(*this);
		--(*this);
		return temp;
	}
private:
	Iterator it_;
	node_id_t nid_;
};

template<class Iterator, bool is_const = false>
class NodeInNeighborIterator
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
	typedef typename std::iterator_traits<Iterator>::iterator_category
			iterator_category;
	typedef typename choose_type<is_const, const Node*, Node*>::type
			node_pointer;

	explicit NodeInNeighborIterator(const Iterator& i) :
		it_(i)
	{
	}
	NodeInNeighborIterator()
	{
	}
	NodeInNeighborIterator(const NodeInNeighborIterator& other) :
		it_(other.it_)
	{
	}
	typename choose_type<is_const, const node_id_t, node_id_t>::type operator*()
	{
		return (*it_)->source()->id();
	}

	node_pointer operator->()
	{
		return (*it_)->source();
	}

	NodeInNeighborIterator& operator=(const NodeInNeighborIterator& i)
	{
		if (&i != this)
			it_ = i.it_;
		return *this;
	}

	friend bool operator==(const NodeInNeighborIterator& a,
			const NodeInNeighborIterator& b)
	{
		return a.it_ == b.it_;
	}
	friend bool operator!=(const NodeInNeighborIterator& a,
			const NodeInNeighborIterator& b)
	{
		return a.it_ != b.it_;
	}
	NodeInNeighborIterator& operator++()
	{
		++it_;
		return *this;
	}
	NodeInNeighborIterator operator++(int)
	{
		NodeInNeighborIterator temp(*this);
		++(*this);
		return temp;
	}
	NodeInNeighborIterator& operator--()
	{
		--it_;
		return *this;
	}
	NodeInNeighborIterator operator--(int)
	{
		NodeInNeighborIterator temp(*this);
		--(*this);
		return temp;
	}
private:
	Iterator it_;
};
}
}

#endif /* NODE_ITERATORS_H_ */

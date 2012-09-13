#ifndef NODE_ITERATORS_H_
#define NODE_ITERATORS_H_

#include <largenet2/base/types.h>
#include <largenet2/util/choosetype.h>
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
	typedef node_id_t difference_type;
	typedef typename std::iterator_traits<Iterator>::iterator_category
			iterator_category;
	typedef typename choose_type<is_const, const Node*, Node*>::type
			node_pointer;
	typedef typename choose_type<is_const, const Node&, Node&>::type
			node_reference;
	typedef node_reference reference;
	typedef const node_reference const_reference;
	typedef node_pointer pointer;
	typedef const node_pointer const_pointer;
	typedef Node value_type;

	explicit NodeOutNeighborIterator(const Iterator& i, const node_id_t nid) :
		it_(i), nid_(nid)
	{
	}
	NodeOutNeighborIterator()
	{
	}
	NodeOutNeighborIterator(const NodeOutNeighborIterator& other) :
		it_(other.it_), nid_(other.nid_)
	{
	}
	typename choose_type<is_const, const node_id_t, node_id_t>::type id()
	{
		if ((*it_)->isDirected())
			return (*it_)->target()->id();
		else
			return ((nid_ == (*it_)->target()->id()) ? (*it_)->source()->id()
					: (*it_)->target()->id());
	}
	node_reference operator*()
	{
		if ((*it_)->isDirected())
			return *((*it_)->target());
		else
			return ((nid_ == (*it_)->target()->id()) ? *((*it_)->source())
					: *((*it_)->target()));
	}
	node_pointer operator->()
	{
		if ((*it_)->isDirected())
			return (*it_)->target();
		else
			return ((nid_ == (*it_)->target()->id()) ? (*it_)->source()
					: (*it_)->target());
	}

	NodeOutNeighborIterator& operator=(const NodeOutNeighborIterator& i)
	{
		if (&i != this)
		{
			it_ = i.it_;
			nid_ = i.nid_;
		}
		return *this;
	}

	friend bool operator==(const NodeOutNeighborIterator& a,
			const NodeOutNeighborIterator& b)
	{
		return (a.it_ == b.it_) && (a.nid_ == b.nid_);
	}
	friend bool operator!=(const NodeOutNeighborIterator& a,
			const NodeOutNeighborIterator& b)
	{
		return !(a == b);
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
	typedef node_id_t difference_type;
	typedef typename std::iterator_traits<Iterator>::iterator_category
			iterator_category;
	typedef typename choose_type<is_const, const Node*, Node*>::type
			node_pointer;
	typedef typename choose_type<is_const, const Node&, Node&>::type
			node_reference;
	typedef node_reference reference;
	typedef const node_reference const_reference;
	typedef node_pointer pointer;
	typedef const node_pointer const_pointer;
	typedef Node value_type;

	explicit NodeInNeighborIterator(const Iterator& i, const node_id_t nid) :
		it_(i), nid_(nid)
	{
	}
	NodeInNeighborIterator()
	{
	}
	NodeInNeighborIterator(const NodeInNeighborIterator& other) :
		it_(other.it_), nid_(other.nid_)
	{
	}
	typename choose_type<is_const, const node_id_t, node_id_t>::type id()
	{
		if ((*it_)->isDirected())
			return (*it_)->source()->id();
		else
			return ((nid_ == (*it_)->target()->id()) ? (*it_)->source()->id()
					: (*it_)->target()->id());
	}
	node_reference operator*()
	{
		if ((*it_)->isDirected())
			return *((*it_)->source());
		else
			return (nid_ == (*it_)->target()->id()) ? *((*it_)->source())
					: *((*it_)->target());
	}
	node_pointer operator->()
	{
		if ((*it_)->isDirected())
			return (*it_)->source();
		else
			return (nid_ == (*it_)->target()->id()) ? (*it_)->source()
					: (*it_)->target();
	}

	NodeInNeighborIterator& operator=(const NodeInNeighborIterator& i)
	{
		if (&i != this)
		{
			it_ = i.it_;
			nid_ = i.nid_;
		}
		return *this;
	}

	friend bool operator==(const NodeInNeighborIterator& a,
			const NodeInNeighborIterator& b)
	{
		return (a.it_ == b.it_) && (a.nid_ == b.nid_);
	}
	friend bool operator!=(const NodeInNeighborIterator& a,
			const NodeInNeighborIterator& b)
	{
		return !(a == b);
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
	node_id_t nid_;
};

template<class Iterator, bool is_const = false>
class UndirectedNodeNeighborIterator
{
public:
	typedef node_id_t difference_type;
	typedef typename std::iterator_traits<Iterator>::iterator_category
			iterator_category;
	typedef typename choose_type<is_const, const Node*, Node*>::type
			node_pointer;
	typedef typename choose_type<is_const, const Node&, Node&>::type
			node_reference;
	typedef node_reference reference;
	typedef const node_reference const_reference;
	typedef node_pointer pointer;
	typedef const node_pointer const_pointer;
	typedef Node value_type;

	explicit UndirectedNodeNeighborIterator(const Iterator& i,
			const node_id_t nid) :
		it_(i), nid_(nid)
	{
	}
	UndirectedNodeNeighborIterator()
	{
	}
	UndirectedNodeNeighborIterator(const UndirectedNodeNeighborIterator& other) :
		it_(other.it_), nid_(other.nid_)
	{
	}
	typename choose_type<is_const, const node_id_t, node_id_t>::type id()
	{
		return ((nid_ == (*it_)->target()->id()) ? (*it_)->source()->id()
				: (*it_)->target()->id());
	}
	node_reference operator*()
	{
		return ((nid_ == (*it_)->target()->id()) ? *((*it_)->source())
				: *((*it_)->target()));
	}
	node_pointer operator->()
	{
		return ((nid_ == (*it_)->target()->id()) ? (*it_)->source()
				: (*it_)->target());
	}

	UndirectedNodeNeighborIterator& operator=(
			const UndirectedNodeNeighborIterator& i)
	{
		if (&i != this)
		{
			it_ = i.it_;
			nid_ = i.nid_;
		}
		return *this;
	}

	friend bool operator==(const UndirectedNodeNeighborIterator& a,
			const UndirectedNodeNeighborIterator& b)
	{
		return (a.it_ == b.it_) && (a.nid_ == b.nid_);
	}
	friend bool operator!=(const UndirectedNodeNeighborIterator& a,
			const UndirectedNodeNeighborIterator& b)
	{
		return !(a == b);
	}
	UndirectedNodeNeighborIterator& operator++()
	{
		++it_;
		return *this;
	}
	UndirectedNodeNeighborIterator operator++(int)
	{
		UndirectedNodeNeighborIterator temp(*this);
		++(*this);
		return temp;
	}
	UndirectedNodeNeighborIterator& operator--()
	{
		--it_;
		return *this;
	}
	UndirectedNodeNeighborIterator operator--(int)
	{
		UndirectedNodeNeighborIterator temp(*this);
		--(*this);
		return temp;
	}
private:
	Iterator it_;
	node_id_t nid_;
};

}
}

#endif /* NODE_ITERATORS_H_ */

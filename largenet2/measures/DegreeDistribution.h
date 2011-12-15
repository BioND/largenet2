/**
 * @file DegreeDistribution.h
 * @date 18.01.2010
 * @author gerd
 */

#ifndef DEGREEDISTRIBUTION_H_
#define DEGREEDISTRIBUTION_H_

#include <largenet2/base/Graph.h>
#include <boost/noncopyable.hpp>
#include <vector>
#include <stdexcept>

namespace largenet
{
namespace measures
{

/// raw degree distribution container type
typedef std::vector<node_size_t> degree_dist_t;

/// selector for in-degree distributions
struct inS
{
};
/// selector for out-degree distributions
struct outS
{
};
/// selector for total-degree distributions
struct bothS
{
};

/**
 * Degree distribution
 * @tparam directionS Selector for in-, out-, or total-degree distribution.
 *                    Possible values are inS, outS, and bothS.
 */
template<typename directionS = bothS>
class DegreeDistribution: public boost::noncopyable
{
public:
	typedef degree_dist_t::size_type size_type;

	explicit DegreeDistribution(const Graph& g);
	DegreeDistribution(const Graph& g, node_state_t s);
	DegreeDistribution(const Graph& g, node_state_t s1, node_state_t s2);

	node_size_t operator[](degree_t k) const
	{
		try
		{
			return dist_.at(k);
		} catch (std::out_of_range&)
		{
			return 0;
		}
		return 0;
	}

	degree_t maxDegree() const
	{
		return dist_.size() > 0 ? dist_.size() - 1 : 0;
	}

	size_type size() const
	{
		return dist_.size();
	}

	degree_dist_t::const_iterator begin() const
	{
		return dist_.begin();
	}
	degree_dist_t::const_iterator end() const
	{
		return dist_.end();
	}

	DegreeDistribution& operator>>(node_size_t& n);

private:
	template<class _NodeIterator> degree_t degree(_NodeIterator& it) const;
	template<class _NodeIterator> degree_t countNeighbors(_NodeIterator& it,
			const Graph& g, node_state_t s) const;
	degree_dist_t dist_;
	degree_dist_t::const_iterator cur_;
};

typedef DegreeDistribution<inS> InDegreeDistribution;
typedef DegreeDistribution<outS> OutDegreeDistribution;

template<>
template<class _NodeIterator>
degree_t DegreeDistribution<inS>::degree(_NodeIterator& it) const
{
	return it->inDegree();
}

template<>
template<class _NodeIterator>
degree_t DegreeDistribution<outS>::degree(_NodeIterator& it) const
{
	return it->outDegree();
}

template<>
template<class _NodeIterator>
degree_t DegreeDistribution<bothS>::degree(_NodeIterator& it) const
{
	return it->degree();
}

template<>
template<class _NodeIterator>
degree_t DegreeDistribution<inS>::countNeighbors(_NodeIterator& it,
		const Graph& g, const node_state_t s) const
{
	degree_t num = 0;
	Node::ConstInNeighborIteratorRange iters = it->inNeighbors();
	for (Node::ConstInNeighborIterator i = iters.first; i != iters.second; ++i)
	{
		if (g.nodeState(i.id()) == s)
			++num;
	}
	return num;
}

template<>
template<class _NodeIterator>
degree_t DegreeDistribution<outS>::countNeighbors(_NodeIterator& it,
		const Graph& g, const node_state_t s) const
{
	degree_t num = 0;
	Node::ConstOutNeighborIteratorRange iters = it->outNeighbors();
	for (Node::ConstOutNeighborIterator i = iters.first; i != iters.second; ++i)
	{
		if (g.nodeState(i.id()) == s)
			++num;
	}
	return num;
}

template<>
template<class _NodeIterator>
degree_t DegreeDistribution<bothS>::countNeighbors(_NodeIterator& it,
		const Graph& g, const node_state_t s) const
{
	degree_t num = 0;
	Node::ConstOutNeighborIteratorRange iters = it->outNeighbors();
	for (Node::ConstOutNeighborIterator i = iters.first; i != iters.second; ++i)
	{
		if (g.nodeState(i.id()) == s)
			++num;
	}
	Node::ConstInNeighborIteratorRange iters2 = it->inNeighbors();
	for (Node::ConstInNeighborIterator i = iters2.first; i != iters2.second; ++i)
	{
		if (g.nodeState(i.id()) == s)
			++num;
	}
	return num;
}

template<typename directionS>
DegreeDistribution<directionS>::DegreeDistribution(const Graph& g)
{
	Graph::ConstNodeIteratorRange iters = g.nodes();
	for (Graph::ConstNodeIterator& it = iters.first; it != iters.second; ++it)
	{
		degree_t k = degree(it);
		while (k >= dist_.size())
		{
			dist_.push_back(0);
		}
		++dist_[k];
	}
	cur_ = dist_.begin();
}

template<typename directionS>
DegreeDistribution<directionS>::DegreeDistribution(const Graph& g,
		const node_state_t s)
{
	Graph::ConstNodeStateIteratorRange iters = g.nodes(s);
	for (Graph::ConstNodeStateIterator& it = iters.first; it != iters.second; ++it)
	{
		degree_t k = degree(it);
		while (k >= dist_.size())
		{
			dist_.push_back(0);
		}
		++dist_[k];
	}
	cur_ = dist_.begin();
}

template<typename directionS>
DegreeDistribution<directionS>::DegreeDistribution(const Graph& g,
		const node_state_t s1, const node_state_t s2)
{
	Graph::ConstNodeStateIteratorRange iters = g.nodes(s1);
	for (Graph::ConstNodeStateIterator& it = iters.first; it != iters.second; ++it)
	{
		degree_t k = countNeighbors(it, g, s2);
		while (k >= dist_.size())
		{
			dist_.push_back(0);
		}
		++dist_[k];
	}
	cur_ = dist_.begin();
}

template<typename directionS>
DegreeDistribution<directionS>& DegreeDistribution<directionS>::operator>>(
		node_size_t& n)
{
	if (cur_ != dist_.end())
	{
		n = *(cur_++);
	}
	else
	{
		n = 0;
	}
	return *this;
}

//template<>
//DegreeDistribution<inS>::DegreeDistribution(const Graph& g)
//{
//	Graph::ConstNodeIteratorRange iters = g.nodes();
//	for (Graph::ConstNodeIterator& it = iters.first; it != iters.second; ++it)
//	{
//		degree_t k = it->inDegree();
//		while (k >= dist_.size())
//		{
//			dist_.push_back(0);
//		}
//		++dist_[k];
//	}
//}
//
//template<>
//DegreeDistribution<bothS>::DegreeDistribution(const Graph& g)
//{
//	Graph::ConstNodeIteratorRange iters = g.nodes();
//	for (Graph::ConstNodeIterator& it = iters.first; it != iters.second; ++it)
//	{
//		degree_t k = it->degree();
//		while (k >= dist_.size())
//		{
//			dist_.push_back(0);
//		}
//		++dist_[k];
//	}
//}
//
//template<>
//DegreeDistribution<outS>::DegreeDistribution(const Graph& g, const node_state_t s)
//{
//	Graph::ConstNodeStateIteratorRange iters = g.nodes(s);
//	for (Graph::ConstNodeStateIterator& it = iters.first; it != iters.second; ++it)
//	{
//		degree_t k = it->outDegree();
//		while (k >= dist_.size())
//		{
//			dist_.push_back(0);
//		}
//		++dist_[k];
//	}
//}
//
//template<>
//DegreeDistribution<inS>::DegreeDistribution(const Graph& g, const node_state_t s)
//{
//	Graph::ConstNodeStateIteratorRange iters = g.nodes(s);
//	for (Graph::ConstStateNodeIterator& it = iters.first; it != iters.second; ++it)
//	{
//		degree_t k = it->inDegree();
//		while (k >= dist_.size())
//		{
//			dist_.push_back(0);
//		}
//		++dist_[k];
//	}
//}
//
//template<>
//DegreeDistribution<bothS>::DegreeDistribution(const Graph& g, const node_state_t s)
//{
//	Graph::ConstNodeStateIteratorRange iters = g.nodes(s);
//	for (Graph::ConstNodeStateIterator& it = iters.first; it != iters.second; ++it)
//	{
//		degree_t k = it->degree();
//		while (k >= dist_.size())
//		{
//			dist_.push_back(0);
//		}
//		++dist_[k];
//	}
//}

}
}

#endif /* DEGREEDISTRIBUTION_H_ */

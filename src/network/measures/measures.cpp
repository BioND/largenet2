/**
 * @file measures.cpp
 * @date 12.01.2011
 * @author gerd
 */

#include "measures.h"
#include <boost/foreach.hpp>

namespace largenet
{
namespace measures
{

degree_t maxInDegree(const Graph& g)
{
	degree_t max = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		if (max < n.inDegree())
			max = n.inDegree();
	}
	return max;
}

degree_t minInDegree(const Graph& g)
{
	degree_t min = g.numberOfEdges();
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		if (min > n.inDegree())
			min = n.inDegree();
	}
	return min;
}

degree_range_t inDegreeRange(const Graph& g)
{
	degree_t min = g.numberOfEdges(), max = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		degree_t k = n.inDegree();
		if (min > k)
			min = k;
		if (max < k)
			max = k;
	}
	return std::make_pair(min, max);
}

degree_t maxOutDegree(const Graph& g)
{
	degree_t max = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		if (max < n.outDegree())
			max = n.outDegree();
	}
	return max;
}

degree_t minOutDegree(const Graph& g)
{
	degree_t min = g.numberOfEdges();
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		if (min > n.outDegree())
			min = n.outDegree();
	}
	return min;
}

degree_range_t outDegreeRange(const Graph& g)
{
	degree_t min = g.numberOfEdges(), max = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		degree_t k = n.outDegree();
		if (min > k)
			min = k;
		if (max < k)
			max = k;
	}
	return std::make_pair(min, max);
}

}
}

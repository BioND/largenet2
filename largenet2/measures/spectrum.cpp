#include "spectrum.h"

#include <boost/foreach.hpp>

namespace largenet
{
namespace measures
{

sparse_dmatrix_t adjacency_matrix(const Graph& g)
{
	std::map<node_id_t, node_id_t> node_index_map;
	node_id_t i = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		node_index_map.insert(std::make_pair(n.id(), i));
		++i;
	}
	sparse_dmatrix_t m(g.numberOfNodes(), g.numberOfNodes());
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		m(node_index_map[e.source()->id()], node_index_map[e.target()->id()]) = 1;
		if (!e.isDirected())
		{
			m(node_index_map[e.target()->id()], node_index_map[e.source()->id()]) = 1;
		}
	}
	return m;
}

sparse_dmatrix_t degree_matrix(const Graph& g)
{
	sparse_dmatrix_t m(g.numberOfNodes(), g.numberOfNodes());
	node_id_t i = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		m(i, i) = n.degree();
		++i;
	}
	return m;
}

sparse_dmatrix_t laplacian(const Graph& g)
{
	sparse_dmatrix_t d = degree_matrix(g), a = adjacency_matrix(g);
	return d - a;
}

sparse_dmatrix_t normalized_laplacian(const Graph& g)
{
	throw std::runtime_error("Not yet implemented!");
}

}
}


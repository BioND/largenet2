/**
 * @file largenet2_boost.h
 * Boost Graph Library (BGL) concepts to use largenet2 in BGL algorithms
 */

#ifndef LARGENET2_BOOST_H_
#define LARGENET2_BOOST_H_

#include <largenet2/base/Graph.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <utility>

namespace largenet
{
namespace detail
{
typedef boost::function<node_id_t(Node&)> node_func_t;
typedef boost::function<edge_id_t(Edge&)> edge_func_t;
typedef boost::function<edge_id_t(Edge*)> ptr_edge_func_t;

/*
class node_iterator_t: public boost::iterator_adaptor<node_iterator_t,
		Graph::NodeIterator, node_id_t, std::forward_iterator_tag, node_id_t>
{
public:
	node_iterator_t() :
			node_iterator_t::iterator_adaptor_(Graph::NodeIterator())
	{
	}
	explicit node_iterator_t(const Graph::NodeIterator& it) :
			node_iterator_t::iterator_adaptor_(it)
	{
	}
	template<class U>
	node_iterator_t(
			const U& other,
			typename boost::enable_if_convertible<U, Graph::NodeIterator>::type* =
					0) :
			node_iterator_t::iterator_adaptor_(other.base())
	{
	}
private:
	friend class boost::iterator_core_access;
	node_id_t dereference() const
	{
		return base_reference()->id();
	}
};
*/
typedef boost::transform_iterator<node_func_t, Graph::NodeIterator> node_iterator_t;
typedef boost::transform_iterator<edge_func_t, Graph::EdgeIterator> edge_iterator_t;
typedef boost::transform_iterator<ptr_edge_func_t, Node::edge_iterator> node_edge_iterator_t;
inline node_id_t node_id(const Node& n)
{
	return n.id();
}
inline edge_id_t edge_id(const Edge& e)
{
	return e.id();
}
inline edge_id_t ptr_edge_id(const Edge* e)
{
	return e->id();
}
}
}

namespace boost
{
struct largenet_graph_traversal_category: public virtual bidirectional_graph_tag, // access to in-edges
		public virtual vertex_list_graph_tag, // efficient vertex traversal
		public virtual edge_list_graph_tag // efficient edge traversal
{
};

template<>
struct graph_traits<largenet::Graph>
{
	typedef largenet::node_id_t vertex_descriptor;
	typedef largenet::edge_id_t edge_descriptor;

	// FIXME we need to use iterator adaptors/facades here, because the BGL requires
	// the iterator's value_types to be edge or vertex descriptors
	typedef largenet::detail::node_edge_iterator_t out_edge_iterator;
	typedef largenet::detail::node_edge_iterator_t in_edge_iterator;
	typedef largenet::detail::edge_iterator_t edge_iterator;
	typedef largenet::detail::node_iterator_t vertex_iterator;

	typedef largenet_graph_traversal_category traversal_category;
	// FIXME need clever mechanics for this
	typedef directed_tag directed_category;
	typedef allow_parallel_edge_tag edge_parallel_category;

	typedef largenet::node_size_t vertices_size_type;
	typedef largenet::edge_size_t edges_size_type;
	typedef largenet::degree_size_t degree_size_type;

	typedef largenet::node_state_t vertex_property_type;
	typedef largenet::edge_state_t edge_property_type;
};
}
namespace largenet
{
// VertexListGraph concept

inline std::pair<boost::graph_traits<largenet::Graph>::vertex_iterator,
		boost::graph_traits<largenet::Graph>::vertex_iterator> vertices(
		const largenet::Graph& g)
{
	typedef boost::graph_traits<largenet::Graph>::vertex_iterator vi_t;
	largenet::Graph::NodeIteratorRange iters = const_cast<largenet::Graph&>(g).nodes();
	return std::pair<vi_t, vi_t>(vi_t(iters.first, &largenet::detail::node_id), vi_t(iters.second, &largenet::detail::node_id));
	//return const_cast<largenet::Graph&>(g).nodes();
}

inline boost::graph_traits<largenet::Graph>::vertices_size_type num_vertices(
		const largenet::Graph& g)
{
	return g.numberOfNodes();
}

// IncidenceGraph concept

inline boost::graph_traits<largenet::Graph>::vertex_descriptor source(
		boost::graph_traits<largenet::Graph>::edge_descriptor e,
		const largenet::Graph& g)
{
	return g.edge(e)->source()->id();
}

inline boost::graph_traits<largenet::Graph>::vertex_descriptor target(
		boost::graph_traits<largenet::Graph>::edge_descriptor e,
		const largenet::Graph& g)
{
	return g.edge(e)->target()->id();
}

inline std::pair<boost::graph_traits<largenet::Graph>::out_edge_iterator,
		boost::graph_traits<largenet::Graph>::out_edge_iterator> out_edges(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u,
		const largenet::Graph& g)
{
	return g.node(u)->outEdges();
}

inline boost::graph_traits<largenet::Graph>::degree_size_type out_degree(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u,
		const largenet::Graph& g)
{
	return g.node(u)->outDegree();
}

// EdgeListGraph concept

inline std::pair<boost::graph_traits<largenet::Graph>::edge_iterator,
		boost::graph_traits<largenet::Graph>::edge_iterator> edges(
		const largenet::Graph& g)
{
	typedef boost::graph_traits<largenet::Graph>::edge_iterator ei_t;
	largenet::Graph::EdgeIteratorRange iters = const_cast<largenet::Graph&>(g).edges();
	return std::pair < ei_t, ei_t
			> (ei_t(iters.first, &largenet::detail::edge_id), ei_t(iters.second,
					&largenet::detail::edge_id));
}

inline boost::graph_traits<largenet::Graph>::edges_size_type num_edges(
		const largenet::Graph& g)
{
	return g.numberOfEdges();
}

// BidirectionalGraph concept

inline std::pair<boost::graph_traits<largenet::Graph>::in_edge_iterator,
		boost::graph_traits<largenet::Graph>::in_edge_iterator> in_edges(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u,
		const largenet::Graph& g)
{
	typedef boost::graph_traits<largenet::Graph>::in_edge_iterator ei_t;
	largenet::Node::edge_iterator_range iters = g.node(u)->inEdges();
	return std::pair < ei_t, ei_t
			> (ei_t(iters.first, &largenet::detail::ptr_edge_id), ei_t(
					iters.second, &largenet::detail::ptr_edge_id));
}

inline boost::graph_traits<largenet::Graph>::degree_size_type in_degree(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u,
		const largenet::Graph& g)
{
	return g.node(u)->inDegree();
}

inline boost::graph_traits<largenet::Graph>::degree_size_type degree(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u,
		const largenet::Graph& g)
{
	return g.node(u)->degree();
}

// MutableGraph concept

/**
 * Add edge between @p u and @p v
 * @param g graph instance
 * @return pair of new/existing edge ID and flag indicating whether a new edge was
 * inserted or the edge exists already and parallel edges are not allowed
 */
inline std::pair<boost::graph_traits<largenet::Graph>::edge_descriptor, bool> add_edge(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u,
		boost::graph_traits<largenet::Graph>::vertex_descriptor v,
		largenet::Graph& g)
{
	largenet::edge_size_t old_num = g.numberOfEdges();
	largenet::edge_id_t e = g.addEdge(u, v, true); // FIXME check for undirected graphs
	return std::make_pair(e, g.numberOfEdges() > old_num);
}

/**
 * Remove all edges from @p u to @p v
 * @param g graph instance
 */
inline void remove_edge(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u,
		boost::graph_traits<largenet::Graph>::vertex_descriptor v,
		largenet::Graph& g)
{
	while (g.node(u)->hasEdgeTo(g.node(v)))
	{
		largenet::Edge* edge = g.node(u)->edgeTo(g.node(v));
		g.removeEdge(edge->id());
	}
}

inline void remove_edge(boost::graph_traits<largenet::Graph>::edge_descriptor e,
		largenet::Graph& g)
{
	g.removeEdge(e);
}

inline void remove_edge(boost::graph_traits<largenet::Graph>::edge_iterator it,
		largenet::Graph& g)
{
	g.removeEdge(*it);
}

template<typename _Predicate>
inline void remove_edge_if(_Predicate, largenet::Graph& g)
{
	std::vector<largenet::edge_id_t> to_remove;
	BOOST_FOREACH(largenet::Edge& e, g.edges())
			{
				if (_Predicate(e.id()))
					to_remove.push_back(e.id());
			}
	BOOST_FOREACH(largenet::edge_id_t eid, to_remove)
			{
				g.removeEdge(eid);
			}
}

template<typename _Predicate>
inline void remove_out_edge_if(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u, _Predicate,
		largenet::Graph& g)
{
	std::vector<largenet::edge_id_t> to_remove;
	BOOST_FOREACH(largenet::Edge* e, g.node(u)->outEdges())
			{
				if (_Predicate(e->id()))
					to_remove.push_back(e->id());
			}
	BOOST_FOREACH(largenet::edge_id_t eid, to_remove)
			{
				g.removeEdge(eid);
			}
}

template<typename _Predicate>
inline void remove_in_edge_if(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u, _Predicate,
		largenet::Graph& g)
{
	std::vector<largenet::edge_id_t> to_remove;
	BOOST_FOREACH(largenet::Edge* e, g.node(u)->inEdges())
			{
				if (_Predicate(e->id()))
					to_remove.push_back(e->id());
			}
	BOOST_FOREACH(largenet::edge_id_t eid, to_remove)
			{
				g.removeEdge(eid);
			}
}

inline boost::graph_traits<largenet::Graph>::vertex_descriptor add_vertex(
		largenet::Graph& g)
{
	return g.addNode();
}

inline void clear_vertex(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u,
		largenet::Graph& g)
{
	std::vector<largenet::edge_id_t> to_remove;
	BOOST_FOREACH(largenet::Edge* e, g.node(u)->inEdges())
			{
				to_remove.push_back(e->id());
			}
	BOOST_FOREACH(largenet::Edge* e, g.node(u)->outEdges())
			{
				to_remove.push_back(e->id());
			}
	BOOST_FOREACH(largenet::Edge* e, g.node(u)->undirectedEdges())
			{
				to_remove.push_back(e->id());
			}
	BOOST_FOREACH(largenet::edge_id_t eid, to_remove)
			{
				g.removeEdge(eid);
			}
}

inline void remove_vertex(
		boost::graph_traits<largenet::Graph>::vertex_descriptor u,
		largenet::Graph& g)
{
	g.removeNode(u);
}

}

#endif /* LARGENET2_BOOST_H_ */

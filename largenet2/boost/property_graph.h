#ifndef PROPERTY_GRAPH_H_
#define PROPERTY_GRAPH_H_

#include <largenet2/base/Graph.h>
#include <largenet2/boost/largenet2_boost.h>
#include <boost/graph/properties.hpp>

namespace largenet
{
template<class G>
class VertexIndexPropertyMap
{
public:
	explicit VertexIndexPropertyMap(G& g) :
			graph_(g)
	{
	}
	G& graph()
	{
		return graph_;
	}
	node_id_t get(node_id_t key) const
	{
		return graph_.node(key)->id();
	}

private:
	G& graph_;
};
}

namespace boost
{

template<>
struct property_map<largenet::Graph, vertex_index_t>
{
	typedef typename largenet::VertexIndexPropertyMap<largenet::Graph> type;
	typedef typename largenet::VertexIndexPropertyMap<const largenet::Graph> const_type;
};

template<class G>
struct property_traits<largenet::VertexIndexPropertyMap<G> >
{
	typedef largenet::node_id_t value_type;
	typedef largenet::node_id_t reference;
	typedef typename graph_traits<G>::vertex_descriptor key_type;
	typedef read_write_property_map_tag category;
};

}

namespace largenet
{

template<class G>
VertexIndexPropertyMap<G> get(boost::vertex_index_t p, G& g)
{
	return VertexIndexPropertyMap<G>(g);
}

template<class G>
node_id_t get(boost::vertex_index_t p, G& g,
		boost::graph_traits<Graph>::vertex_descriptor x)
{
	return get(p, g).get(x);
}

template<class G>
void put(boost::vertex_index_t p, G& g,
		boost::graph_traits<Graph>::vertex_descriptor x, node_id_t v)
{
	// do nothing
}

template<class G>
typename boost::property_traits<VertexIndexPropertyMap<G> >::reference get(
		VertexIndexPropertyMap<G>& pmap,
		typename boost::property_traits<VertexIndexPropertyMap<G> >::key_type key)
{
	return pmap.get(key);
}

template<class G>
void put(VertexIndexPropertyMap<G>& pmap,
		typename boost::property_traits<VertexIndexPropertyMap<G> >::key_type key,
		typename boost::property_traits<VertexIndexPropertyMap<G> >::value_type value)
{
	// do nothing
}

}

#endif /* PROPERTY_GRAPH_H_ */

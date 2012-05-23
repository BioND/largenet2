/**
 * @file largenet2_boost_test.cpp
 * @date 15.11.2011
 * @author gerd
 */

#include <boost/graph/graph_concepts.hpp>
#include <boost/concept_check.hpp>
#include <largenet2/boost/largenet2_boost.h>
#include <largenet2/boost/property_graph.h>

using namespace largenet;

int main(int argc, char **argv)
{
	BOOST_CONCEPT_ASSERT((boost::GraphConcept<Graph>));
	BOOST_CONCEPT_ASSERT((boost::VertexListGraphConcept<Graph>));
	BOOST_CONCEPT_ASSERT((boost::EdgeListGraphConcept<Graph>));
	BOOST_CONCEPT_ASSERT((boost::VertexAndEdgeListGraphConcept<Graph>));
	BOOST_CONCEPT_ASSERT((boost::BidirectionalGraphConcept<Graph>));
	BOOST_CONCEPT_ASSERT((boost::MutableGraphConcept<Graph>));

	BOOST_CONCEPT_ASSERT(
			(boost::PropertyGraphConcept<Graph, boost::graph_traits<Graph>::vertex_descriptor, boost::vertex_index_t>));
	return 0;
}

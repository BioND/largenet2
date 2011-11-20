/**
 * @file largenet2_boost_test.cpp
 * @date 15.11.2011
 * @author gerd
 */

#include <boost/graph/graph_concepts.hpp>
#include <boost/concept/assert.hpp>
#include <largenet2/boost/largenet2_boost.h>

using namespace boost;
using namespace largenet;

int main(int argc, char **argv)
{
	BOOST_CONCEPT_ASSERT((VertexListGraphConcept<Graph>));
	BOOST_CONCEPT_ASSERT((EdgeListGraphConcept<Graph>));
	BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept<Graph>));
	BOOST_CONCEPT_ASSERT((MutableGraphConcept<Graph>));
}

/**
 * @file largenet2_boost_test.cpp
 * @date 15.11.2011
 * @author gerd
 */

#include <boost/graph/graph_concepts.hpp>
#include <boost/concept_check.hpp>
#include <largenet2/boost/largenet2_boost.h>

using namespace boost;
using namespace largenet;

int main(int argc, char **argv)
{
	function_requires<VertexListGraphConcept<Graph> >();
	function_requires<EdgeListGraphConcept<Graph> >();
	function_requires<BidirectionalGraphConcept<Graph> >();
	function_requires<MutableGraphConcept<Graph> >();
}

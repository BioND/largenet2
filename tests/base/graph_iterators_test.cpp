/*
 * graph_iterators_test.cpp
 *
 *  Created on: 16.11.2011
 *      Author: gerd
 */

#include <largenet2.h>
#include <boost/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

using namespace largenet;

int main(int argc, char **argv)
{
	Graph g(2, 3);
	g.addNode();
	g.addNode(1);
	g.addNode();
	Graph::NodeIterator n = g.nodes().first;
	Graph::ConstNodeIterator c_n(n);
	BOOST_ASSERT(c_n == n);
	BOOST_ASSERT(n == c_n);
	if (boost::is_convertible<Graph::ConstNodeIterator, Graph::NodeIterator>::value)
		std::cerr << "Must not be able to convert const to non-const iterator!\n";
}

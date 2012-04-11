/*
 * graph_iterators_test.cpp
 *
 *  Created on: 16.11.2011
 *      Author: gerd
 */

#include <iostream>
#include <largenet2.h>
#include <boost/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept_check.hpp>

using namespace largenet;

int main(int argc, char **argv)
{
	BOOST_CONCEPT_ASSERT((boost::ForwardIterator<Graph::NodeIterator>));
	Graph g(2, 3);
	g.addNode();
	g.addNode(1);
	g.addNode();
	Graph::NodeIterator n = g.nodes().first;
	Graph::ConstNodeIterator c_n(n);
	BOOST_ASSERT(c_n == n);
	BOOST_ASSERT(n == c_n);
	if (!boost::is_convertible<Graph::NodeIterator, Graph::ConstNodeIterator>::value)
	{
		std::cerr << "Must be able to convert non-const to const iterator!\n";
		return -1;
	}
	if (boost::is_convertible<Graph::ConstNodeIterator, Graph::NodeIterator>::value)
	{
		std::cerr << "Must not be able to convert const to non-const iterator!\n";
		return -1;
	}
	return 0;
}

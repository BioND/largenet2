#include <boost/test/unit_test.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/concept_check.hpp>

#include <largenet2.h>

using namespace largenet;

BOOST_TEST_DONT_PRINT_LOG_VALUE( Graph::NodeIterator )
BOOST_TEST_DONT_PRINT_LOG_VALUE( Graph::ConstNodeIterator )

BOOST_AUTO_TEST_SUITE( graph_iterators )

BOOST_AUTO_TEST_CASE( concepts )
{
	BOOST_CONCEPT_ASSERT((boost::ForwardIterator<Graph::NodeIterator>));
}

BOOST_AUTO_TEST_CASE( const_iterators )
{
	Graph g(2, 3);
	g.addNode();
	g.addNode(1);
	g.addNode();
	Graph::NodeIterator n = g.nodes().first;
	Graph::ConstNodeIterator c_n(n);
	BOOST_CHECK_EQUAL(c_n, n);
	BOOST_CHECK_EQUAL(n, c_n);

	if (!boost::is_convertible<Graph::NodeIterator, Graph::ConstNodeIterator>::value)
	{
		BOOST_FAIL("Must be able to convert non-const to const iterator!");
	}
	if (boost::is_convertible<Graph::ConstNodeIterator, Graph::NodeIterator>::value)
	{
		BOOST_FAIL("Must not be able to convert const to non-const iterator!");
	}
}

BOOST_AUTO_TEST_SUITE_END()

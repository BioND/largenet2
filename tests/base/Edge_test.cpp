#include <boost/test/unit_test.hpp>

#include <largenet2/base/MultiNode.h>
#include <largenet2/base/Edge.h>

using namespace largenet;

BOOST_TEST_DONT_PRINT_LOG_VALUE( Edge );

BOOST_AUTO_TEST_SUITE( Edge_tests )

BOOST_AUTO_TEST_CASE( interface )
{
	MultiNode s(1), t(2);
	Edge* e = Edge::create(5, s, t, true);	// factory construction
	BOOST_CHECK_EQUAL(e->id(), 5);
	BOOST_CHECK_EQUAL(e->source(), &s);
	BOOST_CHECK_EQUAL(e->from(s), true);
	BOOST_CHECK_EQUAL(e->from(t), false);
	BOOST_CHECK_EQUAL(e->target(), &t);
	BOOST_CHECK_EQUAL(e->to(t), true);
	BOOST_CHECK_EQUAL(e->to(s), false);
	BOOST_CHECK_EQUAL(e->opposite(s), &t);
	BOOST_CHECK_EQUAL(e->opposite(t), &s);
	BOOST_CHECK_EQUAL(e->isDirected(), true);
	BOOST_CHECK_EQUAL(e->isLoop(), false);

	Edge* e2 = Edge::create(5, s, t, false);
	BOOST_CHECK_EQUAL(e2->id(), 5);
	BOOST_CHECK_EQUAL(e2->source(), &s);
	BOOST_CHECK_EQUAL(e2->from(s), true);
	BOOST_CHECK_EQUAL(e2->from(t), true);
	BOOST_CHECK_EQUAL(e2->target(), &t);
	BOOST_CHECK_EQUAL(e2->to(t), true);
	BOOST_CHECK_EQUAL(e2->to(s), true);
	BOOST_CHECK_EQUAL(e2->opposite(s), &t);
	BOOST_CHECK_EQUAL(e2->opposite(t), &s);
	BOOST_CHECK_EQUAL(e2->isDirected(), false);
	BOOST_CHECK_EQUAL(e2->isLoop(), false);

	Edge* e3 = Edge::create(3, s, s, false);
	BOOST_CHECK_EQUAL(e3->id(), 3);
	BOOST_CHECK_EQUAL(e3->source(), &s);
	BOOST_CHECK_EQUAL(e3->from(s), true);
	BOOST_CHECK_EQUAL(e3->to(s), true);
	BOOST_CHECK_EQUAL(e3->target(), &s);
	BOOST_CHECK_EQUAL(e3->opposite(s), &s);
	BOOST_CHECK_EQUAL(e3->isDirected(), false);
	BOOST_CHECK_EQUAL(e3->isLoop(), true);

	Edge* e4 = Edge::create(3, s, s, false);
	BOOST_CHECK_EQUAL(*e3, *e4);
	BOOST_CHECK_NE(*e, *e2);
	BOOST_CHECK_NE(*e, *e3);
	BOOST_CHECK_NE(*e2, *e3);

	delete e;
	delete e2;
	delete e3;
	delete e4;
}

BOOST_AUTO_TEST_SUITE_END()




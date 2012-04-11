#include <boost/test/unit_test.hpp>
#include <boost/concept_check.hpp>

#include <largenet2/base/repo/CPtrRepository.h>
#include <memory>
#include <iostream>

#include "test_types.h"

typedef MyInt val_type;
typedef repo::CPtrRepository<val_type> ptr_rep_type;

BOOST_TEST_DONT_PRINT_LOG_VALUE( ptr_rep_type::const_iterator )
BOOST_TEST_DONT_PRINT_LOG_VALUE( ptr_rep_type::iterator )

//std::ostream& operator<<(std::ostream& o, const ptr_rep_type::const_iterator& i)
//{
//	o << *i;
//	return o;
//}

void ptr_fillRepo(ptr_rep_type& c, const unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
		c.insert(new val_type(i + 1), i % c.numberOfCategories());
}

void ptr_fillRepo(ptr_rep_type& c, const unsigned int size, const repo::category_t cat)
{
	for (unsigned int i = 0; i < size; ++i)
		c.insert(new val_type(i + 1), cat);
}

BOOST_AUTO_TEST_SUITE(ptr_repo_tests)

BOOST_AUTO_TEST_CASE( ptr_repo_basics )
{
	ptr_rep_type c(10, 1000); // space for 1000 items in 10 categories
	BOOST_CHECK_EQUAL(c.capacity(), 1000);
	BOOST_CHECK_EQUAL(c.size(), 0);
	BOOST_CHECK_EQUAL(c.numberOfCategories(), 10);
}

BOOST_AUTO_TEST_CASE( ptr_repo_access )
{
	ptr_rep_type c(10, 1000);

	std::vector<repo::id_t> ids;
	std::vector<repo::category_t> cats;

	// insert items in category
	for (unsigned int i = 0; i < 10; ++i)
	{
		cats.push_back(i);
		ids.push_back(c.insert(new val_type(i + 1), i));
	}

	// access item categories
	for (unsigned int i = 0; i < ids.size(); ++i)
		BOOST_CHECK_EQUAL(cats[i], c.category(ids[i]));
}

BOOST_AUTO_TEST_CASE( ptr_repo_modification )
{
	ptr_rep_type c(10, 1000); // space for 1000 items in 10 categories

	// insert items
	ptr_fillRepo(c, 10);
	for (unsigned int i = 0; i < c.size(); ++i)
		BOOST_CHECK_EQUAL(val_type(i+1), c[i]);

	// delete items
	for (int i = 0; i < 10; ++i)
		c.erase(c.id(0));
	BOOST_CHECK_EQUAL(0, c.size());

	// change item categories
	std::vector<repo::id_t> ids;
	std::vector<repo::category_t> cats;
	for (unsigned int i = 0; i < 10; ++i)
	{
		cats.push_back(i);
		ids.push_back(c.insert(new val_type(i + 1), i));
	}

	c.setCategory(ids[3], 7);
	cats[3] = 7;

	for (unsigned int i = 0; i < ids.size(); ++i)
		BOOST_CHECK_EQUAL(cats[i], c.category(ids[i]));

	// insert auto_ptr
	ptr_rep_type c2(5, 10);
	for (int i = 0; i < 10; ++i)
		c2 << std::auto_ptr<val_type>(new val_type(i));
	BOOST_CHECK_EQUAL(10, c2.size());
}

BOOST_AUTO_TEST_CASE( ptr_repo_memory )
{
	// resize repository
	ptr_rep_type c(10, 50); // space for 50 items in 10 categories

	ptr_fillRepo(c, 50);

	BOOST_CHECK_EQUAL(50, c.capacity());

	c << new val_type(57);
	BOOST_CHECK_EQUAL(100, c.capacity());
}

BOOST_AUTO_TEST_CASE( ptr_repo_index_iterator )
{
	const int rep_size = 10;
	ptr_rep_type c(5, rep_size);
	ptr_fillRepo(c, rep_size);
	BOOST_CHECK_EQUAL(rep_size, c.size());

	unsigned int i = 0;
	for (ptr_rep_type::IndexIterator it = c.begin(); it != c.end(); ++it)
		++i;
	BOOST_CHECK_EQUAL(rep_size, i);

	i = 0;
	ptr_rep_type::IndexIteratorRange iters = c.items();
	for (ptr_rep_type::IndexIterator it = iters.first; it != iters.second; ++it)
		++i;
	BOOST_CHECK_EQUAL(rep_size, i);

	for (ptr_rep_type::const_iterator it = c.begin(); it != c.end(); ++it)
	{
		it->sayHello();
	}
}

BOOST_AUTO_TEST_CASE( ptr_repo_category_iterator )
{
	ptr_rep_type c(10, 100);
	ptr_fillRepo(c, 100, 2); // 100 items in category 2

	unsigned int i = 0;
	const unsigned int m = 30;
	for (ptr_rep_type::IndexIterator it = c.begin(); (it != c.end()) && (i < m); ++it)
	{
		c.setCategory(it.id(), 5);
		++i;
	}
	// now we should have exactly m items in category 5
	unsigned int k = 0;
	for (ptr_rep_type::CategoryIterator it = c.begin(5); it != c.end(5); ++it)
	{
		BOOST_CHECK_EQUAL(5, c.category(it.id()));
		++k;
	}
	BOOST_CHECK_EQUAL(m, k);
}

BOOST_AUTO_TEST_CASE( ptr_repo_index_iterator_del )
{
	ptr_rep_type c(10, 100);
	ptr_fillRepo(c, 100);
	c.erase(c.id(3));
	c.erase(c.id(0));
	c.erase(c.id(20));
	c.erase(c.id(7));
	c.erase(c.id(46));
	BOOST_CHECK_EQUAL(95, c.size());
	unsigned int i = 0;
	ptr_rep_type::IndexIterator eit(c.end());
	for (ptr_rep_type::IndexIterator it = c.begin(); it != eit; ++it)
	{
		++i;
	}
	BOOST_CHECK_EQUAL(95, i);
}

BOOST_AUTO_TEST_CASE( ptr_repo_index_iterator_category )
{
	ptr_rep_type c(10, 100);
	ptr_fillRepo(c, 100);
	BOOST_CHECK_EQUAL(0, c.minID());
	BOOST_CHECK_EQUAL(99, c.maxID());
	c << new val_type(3) << new val_type(4) << new val_type(5);
	BOOST_CHECK_EQUAL(0, c.minID());
	BOOST_CHECK_EQUAL(102, c.maxID());
	ptr_rep_type::IndexIterator eit(c.end());
	for (ptr_rep_type::IndexIterator it = c.begin(); it != eit; ++it)
		c.setCategory(it.id(), 3);
	BOOST_CHECK_EQUAL(103, c.count(3));
}

//void ptr_repo_copy()
//{
//	ptr_rep_type c(10, 100);
//	ptr_fillRepo(c, 100);
//	c.erase(c.id(3));
//	c.erase(c.id(0));
//	c.erase(c.id(20));
//	c.erase(c.id(7));
//	c.erase(c.id(46));
//	c.insert(new val_type(80), 3);
//	c.insert(new val_type(1413), 2);
//	c.insert(new val_type(99), 7);
//
//	ptr_rep_type d(c);
//	BOOST_CHECK_EQUAL(c.size(), d.size());
//	BOOST_CHECK_EQUAL(c.capacity() - 2, d.capacity());
//}

//void ptr_repo_assign()
//{
//	ptr_rep_type c(10, 100);
//	ptr_fillRepo(c, 100);
//
//	ptr_rep_type d(5, 30);
//	ptr_fillRepo(d, 30);
//
//	d = c;
//	BOOST_CHECK_EQUAL(100, d.size());
//}

BOOST_AUTO_TEST_CASE( ptr_repo_shrink_categories )
{
	ptr_rep_type c(10, 100);
	ptr_fillRepo(c, 100);
	repo::id_size_t n = c.count(8) + c.count(9);
	repo::id_size_t n_old = c.count(7);
	c.setNumberOfCategories(8);
	BOOST_CHECK_EQUAL(8, c.numberOfCategories());
	BOOST_CHECK_EQUAL(n_old + n, c.count(7));
}

BOOST_AUTO_TEST_CASE( ptr_repo_grow_categories )
{
	ptr_rep_type c(10, 100);
	ptr_fillRepo(c, 100);
	repo::id_size_t n_old = c.count(9);
	c.setNumberOfCategories(12);
	BOOST_CHECK_EQUAL(12, c.numberOfCategories());
	BOOST_CHECK_EQUAL(n_old, c.count(9));
	BOOST_CHECK_EQUAL(0, c.count(10));
	BOOST_CHECK_EQUAL(0, c.count(11));
	c.insert(new val_type(5), 10);
	BOOST_CHECK_EQUAL(1, c.count(10));
}

BOOST_AUTO_TEST_CASE( ptr_repo_stl_count )
{
	ptr_rep_type c(10, 100);
	ptr_fillRepo(c, 100);
	c[3] = 5;
	c[10] = 5;
	c[32] = 5;
	c[33] = 5;
	c[74] = 5;
	unsigned int i = std::count(c.begin(), c.end(), 5);
	BOOST_CHECK_EQUAL(6, i);
}

BOOST_AUTO_TEST_CASE( ptr_repo_stl_copy )
{
	ptr_rep_type c(10, 100), d(10, 100);
	ptr_fillRepo(c, 100);
	ptr_fillRepo(d, 100);
	for (ptr_rep_type::iterator i = c.begin(); i != c.end(); ++i)
		*i = val_type(0);

	std::copy(c.begin(), c.end(), d.begin());
	for (unsigned int i = 0; i < d.size(); ++i)
		BOOST_CHECK_EQUAL(d[i], c[i]);
}

BOOST_AUTO_TEST_CASE( ptr_repo_iterator_concepts )
{
	BOOST_CONCEPT_ASSERT((boost::ForwardIterator<ptr_rep_type::iterator>));
	BOOST_CONCEPT_ASSERT((boost::ForwardIterator<ptr_rep_type::const_iterator>));
	BOOST_CONCEPT_ASSERT((boost::Convertible<ptr_rep_type::iterator, ptr_rep_type::const_iterator>));
}

BOOST_AUTO_TEST_CASE( ptr_repo_iterators )
{
	ptr_rep_type c(10, 100);
	ptr_fillRepo(c, 100);
	ptr_rep_type::iterator it = c.begin();
	++it;
	ptr_rep_type::const_iterator c_it(it);
	BOOST_CHECK_EQUAL(c_it, it);
	BOOST_CHECK_EQUAL(it, c_it);
	ptr_rep_type::const_iterator c_it2 = c.end();
	++it;
	c_it2 = c_it;
	c_it = it;
	BOOST_CHECK_EQUAL(it, c_it);
	++c_it;
	//it = c_it; // should fail to compile
}

BOOST_AUTO_TEST_SUITE_END()

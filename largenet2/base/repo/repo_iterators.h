/*
 * repo_iterators.h
 *
 *  Created on: 16.11.2011
 *      Author: gerd
 */

#ifndef REPO_ITERATORS_H_
#define REPO_ITERATORS_H_

#include <largenet2/base/repo/repo_types.h>
#include <largenet2/util/choosetype.h>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/call_traits.hpp>
#include <iterator>
#include <cassert>

namespace repo
{
namespace iterators
{
namespace detail
{

template<class Repo, class T = typename Repo::value_type>
class RepoIndexIteratorImpl: public boost::iterator_facade<
		RepoIndexIteratorImpl<Repo>, T, std::input_iterator_tag,
		typename Repo::reference, long int>
{
public:
	typedef Repo* repo_ptr;
	typedef typename boost::call_traits<Repo>::reference repo_ref;
	/**
	 * Default constructor needed for STL compliance. This creates a singular
	 * (invalid) iterator which does not belong to any repository.
	 */
	RepoIndexIteratorImpl() :
			rep_(0), cur_(0)
	{
	}
	/**
	 * Basic constructor. This creates an iterator pointing to the first
	 * item in the repository @p repo.
	 * @param repo Repository the iterator belongs to.
	 */
	explicit RepoIndexIteratorImpl(repo_ref repo) :
			rep_(&repo), cur_(0)
	{
		assert(rep_ != 0);
	}
	/**
	 * Position constructor. This creates an iterator pointing to the @p n'th
	 * item in the repository @p repo.
	 * @param repo Repository the iterator belongs to.
	 * @param n Number of item.
	 */
	RepoIndexIteratorImpl(repo_ref repo, id_t n) :
			rep_(&repo), cur_(n)
	{
		assert(rep_ != 0);
		// this should be correct now
		assert(cur_ <= rep_->capacity());
	}
	/**
	 * Copy constructor.
	 * @param it Iterator to copy from.
	 */
	template<class V>
	RepoIndexIteratorImpl(const RepoIndexIteratorImpl<Repo, V>& it) :
			rep_(it.rep_), cur_(it.cur_)
	{
	}
	/**
	 * Return item ID in repository.
	 */
	id_t id() const
	{
		assert(rep_ != 0);
		assert(rep_->valid(cur_));
		return cur_;
	}

	/**
	 * Return item category in repository.
	 * @return Category of item in repository.
	 */
	category_t category() const
	{
		assert(rep_ != 0);
		assert(rep_->valid(cur_));
		return rep_->category(cur_);
	}

private:
	friend class boost::iterator_core_access;
	template<class, class > friend class RepoIndexIteratorImpl;

	void increment()
	{
		assert(rep_ != 0);
		while (true)
		{
			if (cur_ == rep_->maxID())
			{
				++cur_;
				break;
			}
			if (cur_ > rep_->maxID())
				break;
			if (rep_->valid(++cur_))
				break;
		}
	}

	template<class V>
	bool equal(const RepoIndexIteratorImpl<Repo, V>& other) const
	{
		return ((rep_ == other.rep_) && (cur_ == other.cur_));
	}

	typename Repo::reference dereference() const
	{
		assert(rep_ != 0);
		assert(rep_->valid(cur_));
		return rep_->item(cur_);
	}

private:
	// FIXME this should be const if the iterator is const
	repo_ptr rep_; ///< repository the iterator belongs to
	id_t cur_; ///< current iterator position
};

template<class Repo, class T = typename Repo::value_type>
class RepoCategoryIteratorImpl: public boost::iterator_facade<
		RepoCategoryIteratorImpl<Repo>, T, std::input_iterator_tag,
		typename Repo::reference, long int>
{
public:
	typedef Repo* repo_ptr;
	typedef typename boost::call_traits<Repo>::reference repo_ref;
	/**
	 * Default constructor needed for STL compliance. This creates a singular
	 * (invalid) iterator which does not belong to any repository.
	 */
	RepoCategoryIteratorImpl() :
			rep_(0), category_(0), cur_(0)
	{
	}
	/**
	 * Basic constructor. This creates an iterator pointing to the first
	 * item in category @p cat in the repository @p repo.
	 * @param repo Repository the iterator belongs to.
	 * @param cat Category to iterate over.
	 */
	RepoCategoryIteratorImpl(repo_ref repo, category_t cat) :
			rep_(&repo), category_(cat), cur_(0)
	{
		assert(rep_ != 0);
		assert(category_ < rep_->numberOfCategories());
	}
	/**
	 * Position constructor. This creates an iterator pointing to the @p n'th
	 * item in category @p cat in the repository @p repo.
	 * @param repo Repository the iterator belongs to.
	 * @param cat Category to iterate over.
	 * @param n Number of item.
	 */
	RepoCategoryIteratorImpl(repo_ref repo, category_t cat, address_t n) :
			rep_(&repo), category_(cat), cur_(n)
	{
		assert(rep_ != 0);
		assert(category_ < rep_->numberOfCategories());
		assert(cur_ <= rep_->count(category_));
		// equal on end
	}
	/**
	 * Copy constructor.
	 * @param it Iterator to copy from.
	 */
	template<class V>
	RepoCategoryIteratorImpl(const RepoCategoryIteratorImpl<Repo, V>& it) :
			rep_(it.rep_), category_(it.category_), cur_(it.cur_)
	{
	}
	id_t id() const
	{
		assert(rep_ != 0);
		assert(cur_ < rep_->count(category_));
		return rep_->id(category_, cur_);
	}

	category_t category() const
	{
		return category_;
	}
private:
	friend class boost::iterator_core_access;
	template<class, class > friend class RepoCategoryIteratorImpl;

	void increment()
	{
		assert(rep_ != 0);
		if (rep_) // do not increment invalid (singular) iterator
		{
			++cur_;
		}
	}

	template<class V>
	bool equal(const RepoCategoryIteratorImpl<Repo, V>& other) const
	{
		return ((rep_ == other.rep_) && (category_ == other.category_)
				&& (cur_ == other.cur_));
	}

	typename Repo::reference dereference() const
	{
		assert(rep_ != 0);
		// this should be correct now
		assert(cur_ < rep_->count(category_));
		return rep_->item(category_, cur_);
	}

private:
	// FIXME this should be const if the iterator is const
	repo_ptr rep_; ///< repository the iterator belongs to
	category_t category_; ///< Category the iterator traverses.
	address_t cur_; ///< Current iterator position, relative to rep_->offset_[category_] (index in ids_ array).
};

}

template<class Repo, bool is_const = false>
class RepoIndexIterator: public detail::RepoIndexIteratorImpl<
		Repo,
		typename choose_type<is_const, typename Repo::value_type const,
				typename Repo::value_type>::type>
{
public:
	RepoIndexIterator() :
			detail::RepoIndexIteratorImpl()
	{
	}
	explicit RepoIndexIterator(repo_ref repo) :
			detail::RepoIndexIteratorImpl(repo)
	{
	}
	RepoIndexIterator(repo_ref repo, id_t n) :
			detail::RepoIndexIteratorImpl(repo, n)
	{
	}
};

template<class Repo, bool is_const>
class RepoCategoryIterator: public detail::RepoCategoryIteratorImpl<
		Repo,
		typename choose_type<is_const, typename Repo::value_type const,
				typename Repo::value_type>::type>
{
public:
	RepoCategoryIterator() :
			detail::RepoCategoryIteratorImpl()
	{
	}
	RepoCategoryIterator(repo_ref repo, category_t cat) :
			detail::RepoCategoryIteratorImpl(repo, cat)
	{
	}
	RepoCategoryIterator(repo_ref repo, category_t cat, address_t n) :
			detail::RepoCategoryIteratorImpl(repo, cat, n)
	{
	}
};

}
}

#endif /* REPO_ITERATORS_H_ */

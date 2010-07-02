/**
 * @file repo_iterators.h
 * @date 30.09.2009
 * @author gerd
 */

#ifndef REPO_ITERATORS_H_
#define REPO_ITERATORS_H_

#include "repo_types.h"
#include "../util/choosetype.h"
#include <boost/call_traits.hpp>
#include <iterator>
#include <cassert>

namespace repo
{

namespace iterators
{

/**
 * Index iterator.
 *
 * This should be used for the traversal of the repository. If valid, it will
 * always dereference to the unique ID of an item actually stored in the repository.
 * Note that inserting into the repository invalidates all iterators.
 */
template<class Repo, bool is_const = false>
class RepoIndexIterator
{
public:
	typedef typename Repo::value_type value_type;
	typedef typename choose_type<is_const, typename Repo::const_reference,
			typename Repo::reference>::type reference;
	typedef typename Repo::const_reference const_reference;
	typedef typename choose_type<is_const, typename Repo::const_pointer,
			typename Repo::pointer>::type pointer;
	typedef long int difference_type;
	typedef std::input_iterator_tag iterator_category;

	typedef typename choose_type<is_const, const Repo&, Repo&>::type repo_ref;
	typedef typename choose_type<is_const, const Repo* const , Repo*>::type
			repo_ptr;

	/**
	 * Default constructor needed for STL compliance. This creates a singular
	 * (invalid) iterator which does not belong to any repository.
	 */
	RepoIndexIterator() :
		rep_(0), cur_(0)
	{
	}
	/**
	 * Basic constructor. This creates an iterator pointing to the first
	 * item in the repository @p repo.
	 * @param repo Repository the iterator belongs to.
	 */
	explicit RepoIndexIterator(repo_ref repo) :
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
	RepoIndexIterator(repo_ref repo, id_t n) :
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
	RepoIndexIterator(const RepoIndexIterator& it) :
		rep_(it.rep_), cur_(it.cur_)
	{
	}

	/**
	 * Destructor. Does nothing.
	 */
	~RepoIndexIterator()
	{
	}

	/**
	 * Assignment operator.
	 * @param it Iterator to assign from.
	 * @return Reference to self.
	 */
	RepoIndexIterator& operator=(const RepoIndexIterator& it)
	{
		if (this != &it)
		{
			rep_ = it.rep_;
			cur_ = it.cur_;
		}
		return *this;
	}

	/**
	 * Equality operator is a friend, declared as non-template
	 * but depending on template parameter.
	 * @see M. Austern: The Standard Librarian: Defining Iterators and Const
	 * Iterators. http://www.ddj.com/cpp/184401331
	 * @param a first iterator to be compared
	 * @param b second iterator to be compared
	 * @return true if equal
	 */
	friend bool operator==(const RepoIndexIterator& a,
			const RepoIndexIterator& b)
	{
		return ((a.rep_ == b.rep_) && (a.cur_ == b.cur_));
	}

	friend bool operator!=(const RepoIndexIterator& a,
			const RepoIndexIterator& b)
	{
		return !(a == b);
	}

	/**
	 * Prefix increment operator.
	 * @return Reference to (incremented) self.
	 */
	RepoIndexIterator& operator++()
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
		return *this;
	}
	/**
	 * Postfix increment operator.
	 * @return Copy of self before increment.
	 */
	RepoIndexIterator operator++(int)
	{
		RepoIndexIterator tmp(*this);
		++(*this);
		return tmp;
	}
	/**
	 * Dereference operator.
	 * @return Reference to item.
	 */
	reference operator*()
	{
		assert(rep_ != 0);
		assert(rep_->valid(cur_));
		return rep_->item(cur_);
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
	repo_ptr rep_; ///< repository the iterator belongs to
	id_t cur_; ///< current iterator position
};

template<class Repo, bool is_const = false>
class RepoCategoryIterator
{
public:
	typedef typename Repo::value_type value_type;
	typedef typename choose_type<is_const, typename Repo::const_reference,
			typename Repo::reference>::type reference;
	typedef typename Repo::const_reference const_reference;
	typedef typename choose_type<is_const, typename Repo::const_pointer,
			typename Repo::pointer>::type pointer;
	typedef long int difference_type;
	typedef std::input_iterator_tag iterator_category;

	typedef typename choose_type<is_const, const Repo&, Repo&>::type repo_ref;
	typedef typename choose_type<is_const, const Repo* const , Repo*>::type
			repo_ptr;

public:
	/**
	 * Default constructor needed for STL compliance. This creates a singular
	 * (invalid) iterator which does not belong to any repository.
	 */
	RepoCategoryIterator() :
		rep_(0), category_(0), cur_(0)
	{
	}
	/**
	 * Basic constructor. This creates an iterator pointing to the first
	 * item in category @p cat in the repository @p repo.
	 * @param repo Repository the iterator belongs to.
	 * @param cat Category to iterate over.
	 */
	RepoCategoryIterator(repo_ref repo, category_t cat) :
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
	RepoCategoryIterator(repo_ref repo, category_t cat, address_t n) :
		rep_(&repo), category_(cat), cur_(n)
	{
		assert(rep_ != 0);
		assert(category_ < rep_->numberOfCategories());
		assert(cur_ <= rep_->count(category_)); // equal on end
	}
	/**
	 * Copy constructor.
	 * @param it Iterator to copy from.
	 */
	RepoCategoryIterator(const RepoCategoryIterator& it) :
		rep_(it.rep_), category_(it.category_), cur_(it.cur_)
	{
	}
	/**
	 * Destructor. Does nothing.
	 */
	~RepoCategoryIterator()
	{
	}

	/**
	 * Assignment operator.
	 * @param it Iterator to assign from.
	 * @return Reference to self.
	 */
	RepoCategoryIterator& operator=(const RepoCategoryIterator& it)
	{
		if (this != &it)
		{
			rep_ = it.rep_;
			category_ = it.category_;
			cur_ = it.cur_;
		}
		return *this;
	}

	/**
	 * Equality operator is a friend, declared as non-template
	 * but depending on template parameter.
	 * @see M. Austern: The Standard Librarian: Defining Iterators and Const
	 * Iterators. http://www.ddj.com/cpp/184401331
	 * @param a first iterator to be compared
	 * @param b second iterator to be compared
	 * @return true if equal
	 */
	friend bool operator==(const RepoCategoryIterator& a,
			const RepoCategoryIterator& b)
	{
		return ((a.rep_ == b.rep_) && (a.category_ == b.category_) && (a.cur_
				== b.cur_));
	}

	friend bool operator!=(const RepoCategoryIterator& a,
			const RepoCategoryIterator& b)
	{
		return !(a == b);
	}

	/**
	 * Prefix increment operator.
	 * @return Reference to (incremented) self.
	 */
	RepoCategoryIterator& operator++()
	{
		assert(rep_ != 0);

		if (rep_) // do not increment invalid (singular) iterator
		{
			++cur_;
		}
		return *this;
	}
	/**
	 * Postfix increment operator.
	 * @return Copy of self before increment.
	 */
	RepoCategoryIterator operator++(int)
	{
		RepoCategoryIterator tmp(*this);
		++(*this);
		return tmp;
	}
	/**
	 * Dereference operator.
	 * @return Reference to item.
	 */
	reference operator*()
	{
		assert(rep_ != 0);
		// this should be correct now
		assert(cur_ < rep_->count(category_));
		return rep_->item(category_, cur_);
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
	repo_ptr rep_; ///< Repository the iterator belongs to.
	category_t category_; ///< Category the iterator traverses.
	address_t cur_; ///< Current iterator position, relative to rep_->offset_[category_] (index in ids_ array).
};

}

}
#endif /* REPO_ITERATORS_H_ */

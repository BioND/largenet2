/**
 * @file repo_iterators.h
 * @date 30.09.2009
 * @author gerd
 */

#ifndef REPO_ITERATORS_H_
#define REPO_ITERATORS_H_

#include <largenet2/base/repo/repo_types.h>
#include <largenet2/util/choosetype.h>
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
	typedef typename choose_type<is_const, const Repo*, Repo*>::type repo_ptr;

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
	template<bool other_is_const>
	RepoIndexIterator(const RepoIndexIterator<Repo, other_is_const>& it) :
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
	template<bool other_is_const>
	RepoIndexIterator& operator=(
			const RepoIndexIterator<Repo, other_is_const>& it)
	{
		if ((rep_ != it.rep_) || (cur_ != it.cur_))
		{
			rep_ = it.rep_;
			cur_ = it.cur_;
		}
		return *this;
	}

	/**
	 * Equality operator is a template on the const-ness of @p it, so
	 * as to be able to compare non-const iterators with const iterators
	 * @return true if @p it belongs to the same repository and points at
	 * the same current value
	 */
	template<bool other_is_const>
	bool operator==(const RepoIndexIterator<Repo, other_is_const>& it) const
	{
		return ((rep_ == it.rep_) && (cur_ == it.cur_));
	}

	/**
	 * Inequality operator
	 */
	template<bool other_is_const>
	bool operator!=(const RepoIndexIterator<Repo, other_is_const>& it) const
	{
		return !operator==(it);
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
	template<class R, bool c> friend class RepoIndexIterator;
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
	typedef typename choose_type<is_const, const Repo*, Repo*>::type repo_ptr;

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
		assert(cur_ <= rep_->count(category_));
		// equal on end
	}
	/**
	 * Copy constructor.
	 * @param it Iterator to copy from.
	 */
	template<bool other_is_const>
	RepoCategoryIterator(const RepoCategoryIterator<Repo, other_is_const>& it) :
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
	template<bool other_is_const>
	RepoCategoryIterator& operator=(const RepoCategoryIterator<Repo, other_is_const>& it)
	{
		if ((rep_ != it.rep_) || (category_ != it.category_) || (cur_ != it.cur_))
		{
			rep_ = it.rep_;
			category_ = it.category_;
			cur_ = it.cur_;
		}
		return *this;
	}

	/**
	 * Equality operator is a template on the const-ness of @p it, so
	 * as to be able to compare non-const iterators with const iterators
	 * @return true if @p it belongs to the same repository and points at
	 * the same current value
	 */
	template<bool other_is_const>
	bool operator==(const RepoCategoryIterator<Repo, other_is_const>& it) const
	{
		return ((rep_ == it.rep_) && (category_ == it.category_)
				&& (cur_ == it.cur_));
	}
	template<bool other_is_const>
	bool operator!=(const RepoCategoryIterator<Repo, other_is_const>& it) const
	{
		return !operator==(it);
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
	template<class R, bool c> friend class RepoCategoryIterator;
	repo_ptr rep_; ///< Repository the iterator belongs to.
	category_t category_; ///< Category the iterator traverses.
	address_t cur_; ///< Current iterator position, relative to rep_->offset_[category_] (index in ids_ array).
};

}

}
#endif /* REPO_ITERATORS_H_ */

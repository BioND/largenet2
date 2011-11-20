#ifndef REPO_ITERATORS_H_
#define REPO_ITERATORS_H_

#include <largenet2/base/repo/repo_types.h>
#include <boost/iterator/iterator_facade.hpp>
#include <cassert>

namespace repo
{

namespace iterators
{

template<class T, class Repo>
class IndexIterator: public boost::iterator_facade<IndexIterator<T, Repo> , T,
boost::forward_traversal_tag>
{
public:
	typedef Repo* repo_ptr; // TODO make this const if T is const
	typedef Repo& repo_ref;

	IndexIterator() :
			rep_(0), cur_(0)
	{
	}
	explicit IndexIterator(repo_ref rep) :
			rep_(&rep), cur_(0)
	{
	}
	IndexIterator(repo_ref rep, id_t i) :
			rep_(&rep), cur_(i)
	{
		assert(cur_ <= rep_->capacity());
	}

	template<class U, class R>
	IndexIterator(const IndexIterator<U, R>& it) :
			rep_(it.rep_), cur_(it.cur_)
	{
	}

	category_t category() const
	{
		assert(rep_ != 0);
		assert(rep_->valid(cur_));
		return rep_->category(cur_);
	}

	id_t id() const
	{
		assert(rep_ != 0);
		assert(rep_->valid(cur_));
		return cur_;
	}

private:
	friend class boost::iterator_core_access;
	template<class, class > friend class IndexIterator;

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

	T& dereference() const
	{
		assert(rep_ != 0);
		assert(rep_->valid(cur_));
		return rep_->item(cur_);
	}

	template<class U, class R>
	bool equal(const IndexIterator<U, R>& other) const
	{
		return ((other.rep_ == rep_) && (other.cur_ == cur_));
	}

private:
	repo_ptr rep_; ///< repository the iterator belongs to
	id_t cur_; ///< current iterator position
};

template<class T, class Repo>
class CategoryIterator: public boost::iterator_facade<CategoryIterator<T, Repo>
		, T,
		boost::forward_traversal_tag>
{
public:
	typedef Repo* repo_ptr; // TODO make this const if T is const
	typedef Repo& repo_ref;

	CategoryIterator() :
			rep_(0), category_(0), cur_(0)
	{
	}
	CategoryIterator(repo_ref rep, category_t cat) :
			rep_(&rep), category_(cat), cur_(0)
	{
		assert(rep_ != 0);
		assert(category_ < rep_->numberOfCategories());
	}
	CategoryIterator(repo_ref rep, category_t cat, address_t cur) :
			rep_(&rep), category_(cat), cur_(cur)
	{
		assert(rep_ != 0);
		assert(category_ < rep_->numberOfCategories());
		assert(cur_ <= rep_->count(category_));
		// equal on end
	}
	template<class U, class R>
	CategoryIterator(const CategoryIterator<U, R>& it) :
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
	template<class, class > friend class CategoryIterator;

	void increment()
	{
		assert(rep_ != 0);

		if (rep_) // do not increment invalid (singular) iterator
		{
			++cur_;
		}
	}

	T& dereference() const
	{
		assert(rep_ != 0);
		// this should be correct now
		assert(cur_ < rep_->count(category_));
		return rep_->item(category_, cur_);
	}

	template<class U>
	bool equal(const CategoryIterator<U, Repo>& other) const
	{
		return ((other.rep_ == rep_) && (other.category_ == category_)
				&& (other.cur_ == cur_));
	}
private:
	repo_ptr rep_; ///< Repository the iterator belongs to.
	category_t category_; ///< Category the iterator traverses.
	address_t cur_; ///< Current iterator position, relative to rep_->offset_[category_] (index in ids_ array).
};

}
}
#endif /* REPO_ITERATORS_H_ */

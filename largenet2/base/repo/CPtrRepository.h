/**
 * @file CPtrRepository.h
 * @date 09.10.2009
 * @author gerd
 */

#ifndef CPTRREPOSITORY_H_
#define CPTRREPOSITORY_H_

#include <largenet2/base/repo/repo_types.h>
#include <largenet2/base/repo/repo_iterators.h>
#include <largenet2/base/repo/repo_exceptions.h>
#include <vector>
#include <memory>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/noncopyable.hpp>
#include <cassert>
#include <utility>

namespace repo
{

/**
 * A convenient way of organizing access to objects that can be grouped into a finite
 * number of classes. Repository features efficient access to objects and can handle
 * some additional tasks.
 *
 * @author Gerd Zschaler <zschaler@pks.mpg.de>
 * @author Thilo Gross (original idea)
 */
template<class T, class CloneAllocator = boost::heap_clone_allocator,
		class Allocator = std::allocator<T> >
class CPtrRepository: boost::noncopyable
{
public:
	typedef T* value_type;
	typedef T& reference;
	typedef const T& const_reference;

	typedef T* pointer;
	typedef const T* const_pointer;

	typedef CPtrRepository<T, CloneAllocator, Allocator> this_type;

	typedef iterators::RepoIndexIterator<this_type, false> iterator;
	typedef iterators::RepoIndexIterator<this_type, true> const_iterator;
	typedef std::pair<iterator, iterator> iterator_range;
	typedef iterator IndexIterator;
	typedef const_iterator ConstIndexIterator;

	typedef iterators::RepoCategoryIterator<this_type, false> CategoryIterator;
	typedef iterators::RepoCategoryIterator<this_type, true>
			ConstCategoryIterator;

	typedef iterator_range IndexIteratorRange;
	typedef std::pair<ConstIndexIterator, ConstIndexIterator>
			ConstIndexIteratorRange;
	typedef std::pair<CategoryIterator, CategoryIterator> CategoryIteratorRange;
	typedef std::pair<ConstCategoryIterator, ConstCategoryIterator>
			ConstCategoryIteratorRange;

public:
	CPtrRepository();
	explicit CPtrRepository(category_t cat);
	CPtrRepository(category_t cat, id_size_t n);
	//	CPtrRepository(const CPtrRepository& r);
	~CPtrRepository();

	/**
	 * Return number of items stored.
	 * @return Number of items stored.
	 */
	id_size_t count() const
	{
		return nStored_;
	}
	/**
	 * Convenience function, same as count().
	 * @return Number of items stored.
	 */
	id_size_t size() const
	{
		return count();
	}
	/**
	 * Return number of items in category @p cat.
	 * @param cat Category to count items in.
	 * @return Number of items in category @p cat
	 */
	id_size_t count(category_t cat) const
	{
		assert(cat < C_);
		return count_[cat];
	}

	/**
	 * Return current maximum number of storable items, i.e. reserved memory.
	 * @return Current capacity.
	 */
	address_t capacity() const
	{
		return N_;
	}

	id_size_t maxSize() const
	{
		// taken from std::allocator
		return id_size_t(-1) / sizeof(T);
	}

	unsigned int enlargeFactor() const
	{
		return enlargeFactor_;
	}

	void setEnlargeFactor(unsigned int val)
	{
		if (val > 1)
			enlargeFactor_ = val;
	}

	/**
	 * Get the number of categories in the repository.
	 * @return Number of categories.
	 */
	category_t numberOfCategories() const
	{
		return C_;
	}

	/**
	 * Check if @p i is a valid ID of an item in the repository.
	 * @param i ID
	 * @return true if valid
	 */
	bool valid(id_t i) const
	{
		return ((nStored_ > 0) && (i < N_) && (nums_[i] < nStored_));
	}
	id_t maxID() const
	{
		return maxID_;
	}
	id_t minID() const
	{
		return minID_;
	}

	/**
	 * Set number of possible categories. If @p n is smaller than the current number of
	 * categories, all items with category numbers greater or equal than @p n are put into
	 * category @p n - 1.
	 * @param n New number of categories
	 */
	void setNumberOfCategories(category_t n);

	/**
	 * Return category of item with number @p n.
	 * @param n Number of item.
	 * @return	Category ID of item.
	 */
	category_t category(address_t n) const;
	/**
	 * Return category of item with unique ID @p id.
	 * @param id Unique ID of item.
	 * @return Category ID of item.
	 */
	category_t category(id_t id) const;

	/**
	 * Set category of item with @p id.
	 * @param id Unique ID of item.
	 * @param cat Category to put item into.
	 */
	void setCategory(id_t id, category_t cat);

	/**
	 * Return item with @p id.
	 * @param id Unique ID of item
	 * @return Reference to item
	 */
	reference item(id_t id);
	const_reference item(id_t id) const;

	/**
	 * Return @p n 'th item in category @p cat
	 * @param cat Category of item
	 * @param n Number of item in category
	 * @return Reference to item
	 */
	reference item(category_t cat, address_t n);
	const_reference item(category_t cat, address_t n) const;
	/**
	 * Return ID of @p n 'th item
	 * @param n Number of item
	 * @return Unique ID of item
	 */
	id_t id(address_t n) const;
	/**
	 * Return ID of @p n 'th item in category @p cat
	 * @param cat Category of item
	 * @param n Number of item in category @p cat
	 * @return Unique ID of item
	 */
	id_t id(category_t cat, address_t n) const;
	/*
	 * boost::ptr_container stuff
	 *
	 void      push_back( T* x );
	 template< class U >
	 void      push_back( std::auto_ptr<U> x );
	 auto_type pop_back();
	 iterator  insert( iterator position, T* x );
	 template< class U >
	 iterator  insert( iterator position, std::auto_ptr<U> x );
	 template< class InputIterator >
	 void      insert( iterator position, InputIterator first, InputIterator last );
	 template< class InputRange >
	 void      insert( iterator position, const InputRange& r );
	 iterator  erase( iterator position );
	 iterator  erase( iterator first, iterator last );
	 template< class Range >
	 iterator  erase( const Range& r );
	 void      resize( size_type size );
	 void      resize( size_type size, T* to_clone );
	 */
	/*
	 * boost::ptr_container requirements
	 *
	 template< class PtrSequence >
	 void transfer( iterator before, typename PtrSequence::iterator object,
	 PtrSequence& from );
	 template< class PtrSequence >
	 void transfer( iterator before, typename PtrSequence::iterator first, typename PtrSequence::iterator last,
	 PtrSequence& from );
	 void template< class PtrSequence, class Range >
	 void transfer( iterator before, const Range& r, PtrSequence& from );
	 template< class PtrSequence >
	 void transfer( iterator before, PtrSequence& from );
	 */

	id_t nextInsertId();
	/**
	 * Insert @p itm into category @p cat
	 * @param itm Pointer to item to insert into the repository. Note that the repository takes ownership.
	 * @param cat Category to insert the item into.
	 * @return Unique ID of inserted item.
	 */
	id_t insert(T* itm, category_t cat);
	template<class U>
	id_t insert(std::auto_ptr<U> itm, category_t cat);
	/**
	 * Insert a copy of @p itm into the repository.
	 * @param itm Item to insert into the repository.
	 * @return Unique ID of inserted item.
	 */
	id_t insert(T* itm);
	template<class U>
	id_t insert(std::auto_ptr<U> itm);

	/**
	 * Erase item from repository. The item's destructor is called.
	 * @param id Unique ID of item to erase
	 */
	void erase(id_t id);

	/**
	 * Get item with unique ID @p id
	 * @param id Unique id of item
	 * @return Reference to item
	 */
	reference operator[](id_t id);
	const_reference operator[](id_t id) const;

	void replace(id_t id, T* itm);
	template<class U>
	void replace(id_t id, std::auto_ptr<U> itm);

	/**
	 * Insert a copy of item @p itm into the repository.
	 * @param itm Item to insert into the repository
	 * @return reference to self (for operator concatenation)
	 */
	CPtrRepository& operator<<(T* itm);
	template<class U>
	CPtrRepository& operator<<(std::auto_ptr<U> itm);

	/**
	 * Return an iterator referring to the first item stored in the repository.
	 * Use this in conjunction with end() to iterate
	 * over all items. These iterators will always dereference to valid item IDs.
	 * @return Iterator pointing to first item ID.
	 */
	iterator begin();
	const_iterator begin() const;
	/**
	 * Return an iterator referring to the past-the-end element in the repository.
	 * @return Past-the-end iterator
	 */
	iterator end();
	const_iterator end() const;

	/**
	 * Return iterator range of all items stored in the repository.
	 * @return @c std::pair of IndexIterators, where the first points to the
	 * first item stored and the second to the past-the-end element
	 * in the repository.
	 */
	IndexIteratorRange items();
	ConstIndexIteratorRange items() const;
	/**
	 * Return iterator range of all items in category @p cat stored in
	 * the repository.
	 * @param cat Category to iterate over.
	 * @return @c std::pair of CategoryIterators, where the first points to the
	 * first item stored and the second to the past-the-end element
	 * in the repository.
	 */
	CategoryIteratorRange items(category_t cat);
	ConstCategoryIteratorRange items(category_t cat) const;

	CategoryIterator begin(category_t cat);
	ConstCategoryIterator begin(category_t cat) const;
	CategoryIterator end(category_t cat);
	ConstCategoryIterator end(category_t cat) const;

	void clear(); ///< clear repository

private:
	void init();
	//void copyItems(const CPtrRepository& r);
	/**
	 * Set category of item with number @p n.
	 * @param n Number of item.
	 * @param cat Category to put item into.
	 */
	void setCategory(address_t n, category_t cat);
	/**
	 * Set category of @p n 'th item in category @p oldCat to @p newCat
	 * @param oldCat Category the item is in.
	 * @param n Number of item in category @p oldCat
	 * @param newCat New category for item.
	 */
	void setCategory(category_t oldCat, address_t n, category_t newCat);

	/**
	 * Return item with number @p n.
	 * @param n Number of item
	 * @return Reference to item
	 */
	reference item(address_t n);
	const_reference item(address_t n) const;

	/**
	 * Remove @p n 'th item from repository.
	 * The item's destructor is called.
	 * @param n Number of item to remove
	 */
	void erase(address_t n);

	void enlarge(); ///< enlarge the storage space
	void increaseCat(address_t n, category_t cat); ///< increase category of entry
	void decreaseCat(address_t n, category_t cat); ///< decrease category of entry

	void reorderToMaxCategory(const category_t n);

	void updateMinID();
	void updateMaxID();
	/**
	 * Recalculate the minimum and maximum valid ID
	 */
	void updateMinMaxID();
	/**
	 * Recalculate the minimum and maximum valid ID, where @p id is guaranteed to be valid
	 * (e. g. after insertion).
	 * @param id Valid ID
	 */
	void updateMinMaxID(id_t id);

	category_t C_; ///< number of categories
	address_t N_; ///< current max number of items
	address_t nStored_; ///< total number of items stored
	std::vector<address_t> count_; ///< number of items per category;
	std::vector<address_t> offset_; ///< start index of a class
	std::vector<address_t> nums_; ///< number of an item according to id
	std::vector<id_t> ids_; ///< id of an item according to number
	boost::ptr_vector<boost::nullable<T>, CloneAllocator, Allocator> items_; ///< array of items
	id_t minID_; ///< smallest valid ID
	id_t maxID_; ///< largest valid ID
	unsigned int enlargeFactor_;
};

template<class T, class CloneAllocator, class Allocator>
inline void CPtrRepository<T, CloneAllocator, Allocator>::updateMinID()
{
	if (nStored_ > 0)
	{
		minID_ = 0;
		while (!valid(minID_) && (minID_ < N_))
			++minID_;
	}
	else
		minID_ = 0;
}

template<class T, class CloneAllocator, class Allocator>
inline void CPtrRepository<T, CloneAllocator, Allocator>::updateMaxID()
{
	if (nStored_ > 0)
	{
		maxID_ = N_ - 1;
		while (!valid(maxID_) && (maxID_ > 0))
			--maxID_;
	}
	else
		maxID_ = 0;
}

template<class T, class CloneAllocator, class Allocator>
inline void CPtrRepository<T, CloneAllocator, Allocator>::updateMinMaxID()
{
	updateMinID();
	updateMaxID();
}

template<class T, class CloneAllocator, class Allocator>
inline void CPtrRepository<T, CloneAllocator, Allocator>::updateMinMaxID(
		const id_t id)
{
	if (nStored_ > 0)
	{
		assert(id < N_);
		if (id < minID_)
			minID_ = id;
		if (id > maxID_)
			maxID_ = id;
	}
	else
	{
		minID_ = 0;
		maxID_ = 0;
	}
}

template<class T, class CloneAllocator, class Allocator>
CPtrRepository<T, CloneAllocator, Allocator>::CPtrRepository() :
	C_(1), N_(0), nStored_(0), minID_(0), maxID_(0), enlargeFactor_(2)
{
	init();
}

template<class T, class CloneAllocator, class Allocator>
CPtrRepository<T, CloneAllocator, Allocator>::CPtrRepository(
		const category_t cat) :
	C_(cat), N_(100), nStored_(0), count_(cat + 1, 0), offset_(cat + 1, 0),
			nums_(N_, 0), ids_(N_, 0), items_(N_), minID_(0), maxID_(0),
			enlargeFactor_(2)
{
	assert(C_ > 0);
	init();
}

template<class T, class CloneAllocator, class Allocator>
CPtrRepository<T, CloneAllocator, Allocator>::CPtrRepository(
		const category_t cat, const id_size_t n) :
	C_(cat), N_(n), nStored_(0), count_(cat + 1, 0), offset_(cat + 1, 0),
			nums_(N_, 0), ids_(N_, 0), items_(N_), minID_(0), maxID_(0),
			enlargeFactor_(2)
{
	init();
}

/// needs cloneability @see boost::ptr_container
//
//template<class T, class CloneAllocator, class Allocator>
//CPtrRepository<T, CloneAllocator, Allocator>::CPtrRepository(
//		const CPtrRepository<T, CloneAllocator, Allocator>& r) :
//	C_(r.C_), N_(r.nStored_), count_(C_ + 1, 0), offset_(C_ + 1, 0),
//			items_(N_), enlargeFactor_(r.enlargeFactor_)
//{
//	init();
//	copyItems(r);
//}

template<class T, class CloneAllocator, class Allocator>
CPtrRepository<T, CloneAllocator, Allocator>::~CPtrRepository()
{
}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::init()
{
	nStored_ = 0;
	nums_.reserve(N_);
	nums_.resize(N_, 0);
	ids_.reserve(N_);
	ids_.resize(N_, 0);
	count_.reserve(C_ + 1);
	count_.resize(C_ + 1, 0);
	offset_.reserve(C_ + 1);
	offset_.resize(C_ + 1, 0);
	for (unsigned int i = 0; i < N_; ++i)
	{
		ids_[i] = i;
		nums_[i] = i;
	}
	for (unsigned int i = 0; i < C_; ++i)
	{
		count_[i] = 0;
		offset_[i] = 0;
	}
	offset_[C_] = 0;
	count_[C_] = N_;
	minID_ = 0;
	maxID_ = 0;
	items_.reserve(N_);
	for (address_t i = 0; i < N_; ++i)
		items_.push_back(0);
}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::setNumberOfCategories(
		const category_t n)
{
	if (n == 0)
		return;
	if (nStored_ > 0)
		reorderToMaxCategory(n - 1);
	address_t oldCCount = count_[C_];
	address_t oldCOffset = offset_[C_];
	category_t oldC = C_;
	C_ = n;
	count_.resize(C_ + 1, 0);
	offset_.resize(C_ + 1, oldCOffset);
	count_[oldC] = 0;
	count_[C_] = oldCCount;
	offset_[C_] = oldCOffset;
}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::reorderToMaxCategory(
		const category_t n)
{
	if (n >= C_ - 1)
		return;

	// first id to move should be ids_[offset_[n+1]], last ids_[offset_[C_]-1]
	// number of ids to move should be offset_[C_] - offset_[n+1]

	id_size_t num = offset_[C_] - offset_[n + 1];
	std::vector<id_t> temp(num, 0);
	std::copy(ids_.begin() + offset_[n + 1], ids_.begin() + offset_[C_],
			temp.begin());

	for (std::vector<id_t>::const_iterator it = temp.begin(); it != temp.end(); ++it)
	{
		decreaseCat(nums_[*it], n);
	}
}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::clear()
{
	assert(C_ > 0);
	items_.clear(); // ensure that items' destructors are called
	init();
}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::enlarge()
{
	id_size_t new_size = (N_ > 0) ? N_ * enlargeFactor_ : enlargeFactor_;
	id_size_t max_size = maxSize();
	if (new_size > max_size)
		new_size = max_size;
	if (new_size <= N_)
		throw AllocException();
	else
	{
		items_.reserve(new_size);
		for (address_t i = N_; i < new_size; ++i)
			items_.push_back(0);
		ids_.reserve(new_size);
		for (address_t i = N_; i < new_size; ++i)
			ids_.push_back(i);

		nums_.reserve(new_size);
		for (id_t i = N_; i < new_size; ++i)
			nums_.push_back(i);

		count_[C_] += new_size - N_;
		N_ = new_size;
	}
}

/// we cannot copy objects, must rely on cloneability @see boost::ptr_container
//
//template<class T, class CloneAllocator, class Allocator>
//void CPtrRepository<T, CloneAllocator, Allocator>::copyItems(
//		const CPtrRepository<T, CloneAllocator, Allocator>& r)
//{
//	assert(C_ == r.C_);
//	for (const_iterator it = r.begin(); it != r.end(); ++it)
//	{
//		insert(*it, it.category());
//	}
//}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::increaseCat(
		const address_t n, const category_t cat)
{
	assert(n < N_);
	assert(cat <= C_);
	category_t cls = category(n);
	address_t mynum = n;
	id_t myid = ids_[mynum];
	assert(cls <= cat);
	while (cls < cat) // Keep increasing
	{
		// First go to last pos in current group
		address_t tarnum = offset_[cls] + count_[cls] - 1;
		if (mynum != tarnum)
		{
			id_t idbuf = ids_[tarnum];
			ids_[tarnum] = ids_[mynum];
			ids_[mynum] = idbuf;
			nums_[myid] = tarnum; // This is right cause we switched nums
			nums_[idbuf] = mynum;
			mynum = tarnum;
		}
		--count_[cls]; // Now shift the boundary
		++count_[cls + 1];
		--offset_[cls + 1];
		++cls;
	}
}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::decreaseCat(
		const address_t n, const category_t cat)
{
	assert(n < N_);
	assert(cat <= C_);
	category_t cls = category(n);
	address_t mynum = n;
	id_t myid = ids_[mynum];
	assert(cls >= cat);
	while (cls > cat) // Keep decreasing
	{
		// First go to first pos in current group
		address_t tarnum = offset_[cls];
		if (mynum != tarnum)
		{
			id_t idbuf = ids_[tarnum];
			ids_[tarnum] = ids_[mynum];
			ids_[mynum] = idbuf;
			nums_[myid] = tarnum; // This is right cause we switched nums
			nums_[idbuf] = mynum;
			mynum = tarnum;
		}
		--count_[cls]; // Now shift the boundary
		++count_[cls - 1];
		++offset_[cls];
		--cls;
	}
}

template<class T, class CloneAllocator, class Allocator>
inline category_t CPtrRepository<T, CloneAllocator, Allocator>::category(
		const id_t id) const
{
	assert(valid(id));
	return category(nums_[id]);
}

template<class T, class CloneAllocator, class Allocator>
inline category_t CPtrRepository<T, CloneAllocator, Allocator>::category(
		const address_t n) const
{
	assert(n < N_);
	address_t na = n;
	category_t c = 0;
	while (na >= count_[c])
	{
		na -= count_[c];
		++c;
	}
	return c;
}

template<class T, class CloneAllocator, class Allocator>
inline void CPtrRepository<T, CloneAllocator, Allocator>::setCategory(
		const id_t id, const category_t cat)
{
	assert(valid(id));
	setCategory(nums_[id], cat);
}

template<class T, class CloneAllocator, class Allocator>
inline void CPtrRepository<T, CloneAllocator, Allocator>::setCategory(
		const address_t n, const category_t cat)
{
	assert(cat < C_);
	assert(n <= nStored_);
	category_t cls = category(n);
	if (cls < cat)
		increaseCat(n, cat);
	else
		decreaseCat(n, cat);
}

template<class T, class CloneAllocator, class Allocator>
inline void CPtrRepository<T, CloneAllocator, Allocator>::setCategory(
		const category_t oldCat, const address_t n, const category_t newCat)
{
	assert(oldCat < C_);
	assert(n < count_[oldCat]);
	assert(newCat < C_);
	address_t num = offset_[oldCat] + n;
	setCategory(num, newCat);
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::reference CPtrRepository<
		T, CloneAllocator, Allocator>::item(const id_t id)
{
	assert(valid(id));
	return items_[id];
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::reference CPtrRepository<
		T, CloneAllocator, Allocator>::operator[](const id_t id)
{
	return item(id);
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::const_reference CPtrRepository<
		T, CloneAllocator, Allocator>::item(const id_t id) const
{
	assert(valid(id));
	return items_[id];
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::const_reference CPtrRepository<
		T, CloneAllocator, Allocator>::operator[](const id_t id) const
{
	return item(id);
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::reference CPtrRepository<
		T, CloneAllocator, Allocator>::item(const address_t n)
{
	assert(n < N_);
	assert(valid(ids_[n]));
	return items_[ids_[n]];
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::const_reference CPtrRepository<
		T, CloneAllocator, Allocator>::item(const address_t n) const
{
	assert(n < N_);
	assert(valid(ids_[n]));
	return items_[ids_[n]];
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::reference CPtrRepository<
		T, CloneAllocator, Allocator>::item(const category_t cat,
		const address_t n)
{
	assert(cat < C_);
	assert(n < count_[cat]);
	assert(valid(ids_[offset_[cat] + n]));
	return items_[ids_[offset_[cat] + n]];
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::const_reference CPtrRepository<
		T, CloneAllocator, Allocator>::item(const category_t cat,
		const address_t n) const
{
	assert(cat < C_);
	assert(n < count_[cat]);
	assert(valid(ids_[offset_[cat] + n]));
	return items_[ids_[offset_[cat] + n]];
}

template<class T, class CloneAllocator, class Allocator>
inline id_t CPtrRepository<T, CloneAllocator, Allocator>::id(const address_t n) const
{
	assert(n < N_);
	return ids_[n];
}

template<class T, class CloneAllocator, class Allocator>
inline id_t CPtrRepository<T, CloneAllocator, Allocator>::id(
		const category_t cat, const address_t n) const
{
	assert(cat < C_);
	assert(offset_[cat] + n < N_);
	assert(n < count_[cat]);
	return ids_[offset_[cat] + n];
}

template<class T, class CloneAllocator, class Allocator>
id_t CPtrRepository<T, CloneAllocator, Allocator>::nextInsertId()
{
	// FIXME is it possible to find ID without enlarging?
	address_t curnum = offset_[C_];
	if (curnum >= N_)
		enlarge();
	return ids_[curnum];
}

template<class T, class CloneAllocator, class Allocator>
id_t CPtrRepository<T, CloneAllocator, Allocator>::insert(T* itm,
		const category_t cat)
{
	assert(cat < C_);
	// Basic storage at the end
	id_t uid = nextInsertId();
	address_t curnum = offset_[C_];
	//	if (curnum >= N_)
	//		enlarge();
	//	id_t uid = ids_[curnum];
	items_.replace(uid, itm); // this returns auto_type pointer to the old item, released and destroyed when out of scope
	decreaseCat(curnum, cat); // Move into right class
	++nStored_;
	updateMinMaxID(uid);
	return uid;
}

template<class T, class CloneAllocator, class Allocator>
template<class U>
id_t CPtrRepository<T, CloneAllocator, Allocator>::insert(std::auto_ptr<U> itm,
		const category_t cat)
{
	return insert(itm.release(), cat);
}

template<class T, class CloneAllocator, class Allocator>
id_t CPtrRepository<T, CloneAllocator, Allocator>::insert(T* itm)
{
	return insert(itm, 0);
}

template<class T, class CloneAllocator, class Allocator>
template<class U>
id_t CPtrRepository<T, CloneAllocator, Allocator>::insert(std::auto_ptr<U> itm)
{
	return insert(itm, 0);
}

template<class T, class CloneAllocator, class Allocator>
CPtrRepository<T, CloneAllocator, Allocator>& CPtrRepository<T, CloneAllocator,
		Allocator>::operator<<(T* itm)
{
	insert(itm, 0);
	return *this;
}

template<class T, class CloneAllocator, class Allocator>
template<class U>
CPtrRepository<T, CloneAllocator, Allocator>& CPtrRepository<T, CloneAllocator,
		Allocator>::operator<<(std::auto_ptr<U> itm)
{
	insert(itm, 0);
	return *this;
}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::replace(id_t id, T* itm)
{
	assert(valid(id));
	items_.replace(id, itm);
}

template<class T, class CloneAllocator, class Allocator>
template<class U>
void CPtrRepository<T, CloneAllocator, Allocator>::replace(id_t id,
		std::auto_ptr<U> itm)
{
	assert(valid(id));
	items_.replace(id, itm.release());
}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::erase(const address_t n)
{
	assert(n < N_);
	assert(n < nStored_);
	id_t uid = ids_[n];
	items_.replace(uid, 0); // replace by null pointer, returns released auto_ptr, destroyed and freed when out of scope
	increaseCat(n, C_); // move to hidden category
	--nStored_;
	if (uid == minID_)
		updateMinID();
	if (uid == maxID_)
		updateMaxID();
}

template<class T, class CloneAllocator, class Allocator>
void CPtrRepository<T, CloneAllocator, Allocator>::erase(const id_t id)
{
	assert(valid(id));
	erase(nums_[id]);
}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::iterator CPtrRepository<
		T, CloneAllocator, Allocator>::begin()
{
	return iterator(*this, minID_);
}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::const_iterator CPtrRepository<
		T, CloneAllocator, Allocator>::begin() const
{
	return const_iterator(*this, minID_);
}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::iterator CPtrRepository<
		T, CloneAllocator, Allocator>::end()
{
	if (nStored_ > 0)
		return iterator(*this, maxID_ + 1);
	else
		return iterator(*this, maxID_);

}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::const_iterator CPtrRepository<
		T, CloneAllocator, Allocator>::end() const
{
	if (nStored_ > 0)
		return const_iterator(*this, maxID_ + 1);
	else
		return const_iterator(*this, maxID_);

}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::IndexIteratorRange CPtrRepository<
		T, CloneAllocator, Allocator>::items()
{
	return std::make_pair(begin(), end());
}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::ConstIndexIteratorRange CPtrRepository<
		T, CloneAllocator, Allocator>::items() const
{
	return std::make_pair(begin(), end());
}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::CategoryIterator CPtrRepository<
		T, CloneAllocator, Allocator>::begin(const category_t cat)
{
	assert(cat < C_);
	return CategoryIterator(*this, cat);
}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::ConstCategoryIterator CPtrRepository<
		T, CloneAllocator, Allocator>::begin(const category_t cat) const
{
	assert(cat < C_);
	return ConstCategoryIterator(*this, cat);
}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::CategoryIterator CPtrRepository<
		T, CloneAllocator, Allocator>::end(const category_t cat)
{
	assert(cat < C_);
	/*
	 * This is safe, because any empty items are guaranteed to be put in the
	 * private category C_. See increaseCat() and decreaseCat().
	 */
	return CategoryIterator(*this, cat, count_[cat]);
}

template<class T, class CloneAllocator, class Allocator>
typename CPtrRepository<T, CloneAllocator, Allocator>::ConstCategoryIterator CPtrRepository<
		T, CloneAllocator, Allocator>::end(const category_t cat) const
{
	assert(cat < C_);
	/*
	 * This is safe, because any empty items are guaranteed to be put in the
	 * private category C_. See increaseCat() and decreaseCat().
	 */
	return ConstCategoryIterator(*this, cat, count_[cat]);
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::CategoryIteratorRange CPtrRepository<
		T, CloneAllocator, Allocator>::items(const category_t cat)
{
	return std::make_pair(begin(cat), end(cat));
}

template<class T, class CloneAllocator, class Allocator>
inline typename CPtrRepository<T, CloneAllocator, Allocator>::ConstCategoryIteratorRange CPtrRepository<
		T, CloneAllocator, Allocator>::items(const category_t cat) const
{
	return std::make_pair(begin(cat), end(cat));
}

}

#endif /* CPTRREPOSITORY_H_ */

/**
 * @file util.h
 * @date 23.05.2012
 * @author gerd
 */

#ifndef MYRNG_UTIL_H_
#define MYRNG_UTIL_H_

#include <iterator>
#include <cassert>

namespace myrng
{
namespace util
{
/**
 * Get random element from container
 * @param container Random access container
 * @param rnd Random number generator
 * @return random element in @p container
 */
template<class U, class V, class RandomGen>
U& random_from(V& container, RandomGen& rnd)
{
	typedef typename V::size_type sz_t;
	sz_t from = 0, to = container.size() - 1;
	sz_t i = rnd.IntFromTo(from, to);
	return container[i];
}

/**
 * Get random element from range
 * @param begin iterator pointing to beginning of range
 * @param end iterator pointing to (past the) end of range
 * @param rnd random number generator
 * @return random iterator within range or @p end if empty range
 */
template<class _Iter, class RandomGen>
_Iter random_from(_Iter begin, _Iter end, RandomGen& rnd)
{
	if (begin == end)
		return end;
	typedef typename std::iterator_traits<_Iter>::difference_type d_t;
	d_t from = 0, to = std::distance(begin, end) - 1;
	d_t i = rnd.IntFromTo(from, to);
	std::advance(begin, i);
	assert(begin != end);
	return begin;
}

/**
 * Get random element from range
 * @param range iterator range
 * @param rnd random variates generator
 * @return random iterator within @p range or @p range.second if empty range
 */
template<class _Iter, class RandomGen>
inline _Iter random_from(std::pair<_Iter, _Iter> range, RandomGen& rnd)
{
	return random_from(range.first, range.second, rnd);
}
}
}

#endif /* UTIL_H_ */

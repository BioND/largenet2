/**
 * @file util.h
 * @date 09.12.2011
 * @author gerd
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <utility>
#include <iterator>
#include <cassert>

template<class _Iter, class RandomGen>
_Iter random_from(_Iter begin, _Iter end, RandomGen& rng)
{
	if (begin == end)
		return end;
	int i = rng.IntFromTo(0, std::distance(begin, end) - 1);
	std::advance(begin, i);
	assert(begin != end);
	return begin;
}

template<class _Iter, class RandomGen>
_Iter random_from(std::pair<_Iter, _Iter> range, RandomGen& rng)
{
	return random_from(range.first, range.second, rng);
}

#endif /* UTIL_H_ */

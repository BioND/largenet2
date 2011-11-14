/**
 * @file choosetype.h
 * @date 01.10.2009
 * @author gerd
 */

#ifndef CHOOSETYPE_H_
#define CHOOSETYPE_H_

/**
 * @cond IGNORE
 */

template<bool flag, class IsTrue, class IsFalse>
struct choose_type;

template<class IsTrue, class IsFalse>
struct choose_type<true, IsTrue, IsFalse>
{
	typedef IsTrue type;
};

template<class IsTrue, class IsFalse>
struct choose_type<false, IsTrue, IsFalse>
{
	typedef IsFalse type;
};

/**
 * @endcond IGNORE
 */

#endif /* CHOOSETYPE_H_ */

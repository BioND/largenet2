/**
 * @file repo_exceptions.h
 * @date 09.10.2009
 * @author gerd
 */

#ifndef REPO_EXCEPTIONS_H_
#define REPO_EXCEPTIONS_H_

#include <exception>

namespace repo {

class AllocException: public std::exception
{
public:
	const char* what() const throw ()
	{
		return "Could not resize repository!";
	}
};

}

#endif /* REPO_EXCEPTIONS_H_ */

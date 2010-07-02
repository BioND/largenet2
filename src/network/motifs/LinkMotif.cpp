/*
 * LinkMotif.cpp
 *
 *  Created on: 03.02.2009
 *      Author: gerd
 */

#include "LinkMotif.h"
#include <sstream>

namespace largenet
{
namespace motifs
{

std::string LinkMotif::toStr() const
{
	std::stringstream ss;
	ss << "(" << s_ << "," << t_ << ")";
	return ss.str();
}

bool operator==(const LinkMotif& A, const LinkMotif& B)
{
	return ((A.isDirected() == B.isDirected()) && A.source() == B.source()) && (A.target() == B.target());
}

bool operator<(const LinkMotif& A, const LinkMotif& B)
{
	if (A.isDirected() != B.isDirected())
	{
		if (A.isDirected())
			return true;
		else
			return false;
	}
	if (A.source() < B.source())
		return true;
	else if (A.source() > B.source())
		return false;
	else if (A.target() < B.target())
		return true;
	else
		return false;
}

}
}

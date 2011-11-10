/**
 * @file QuadLineMotif.cpp
 * @date 19.11.2010
 * @author gerd
 */

#include "QuadLineMotif.h"
#include <sstream>

namespace largenet
{

namespace motifs
{

bool operator==(const QuadLineMotif& A, const QuadLineMotif& B)
{
	return A.dir() == B.dir() && A.a() == B.a() && A.b() == B.b() && A.c()
			== B.c() && A.d() == B.d();
}

bool operator<(const QuadLineMotif& A, const QuadLineMotif& B)
{
	if (A.dir() < B.dir())
		return true;
	else if (A.dir() == B.dir())
	{
		if (A.a() < B.a())
			return true;
		else if (A.a() == B.a())
		{
			if (A.b() < B.b())
				return true;
			else if (A.b() == B.b())
			{
				if (A.c() < B.c())
					return true;
				else if (A.c() == B.c())
				{
					if (A.d() < B.d())
						return true;
				}
			}
		}
	}
	return false;
}

std::string QuadLineMotif::toStr() const
{
	std::stringstream ss;
	switch (dir_)
	{
	case NO_DIR:
		ss << "(" << a_ << "-" << b_ << "-" << c_ << "-" << d_ << ")";
		break;
	case RLINE:
		ss << "(" << a_ << ">" << b_ << ">" << c_ << ">" << d_ << ")";
		break;
	case LLINE: // should not happen anyway
		ss << "(" << a_ << "<" << b_ << "<" << c_ << "<" << d_ << ")";
		break;
	case B_IN:
		ss << "(" << a_ << ">" << b_ << "<" << c_ << "<" << d_ << ")";
		break;
	case C_IN:
		ss << "(" << a_ << ">" << b_ << ">" << c_ << "<" << d_ << ")";
		break;
	case B_OUT:
		ss << "(" << a_ << "<" << b_ << ">" << c_ << ">" << d_ << ")";
		break;
	case C_OUT:
		ss << "(" << a_ << "<" << b_ << "<" << c_ << ">" << d_ << ")";
		break;
	case B_IN_C_OUT:
		ss << "(" << a_ << ">" << b_ << "<" << c_ << ">" << d_ << ")";
		break;
	case B_OUT_C_IN:
		ss << "(" << a_ << "<" << b_ << ">" << c_ << "<" << d_ << ")";
		break;
	}
	return ss.str();
}

}

}

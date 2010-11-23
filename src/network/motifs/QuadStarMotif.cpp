/**
 * @file QuadStarMotif.cpp
 * @date 23.11.2010
 * @author gerd
 */

#include "QuadStarMotif.h"
#include <sstream>

namespace largenet
{

namespace motifs
{

bool operator==(const QuadStarMotif& A, const QuadStarMotif& B)
{
	return A.dir() == B.dir() && A.a() == B.a() && A.b() == B.b() && A.c()
			== B.c() && A.center() == B.center();
}

bool operator<(const QuadStarMotif& A, const QuadStarMotif& B)
{
	if (A.dir() < B.dir())
		return true;
	else if (A.dir() == B.dir())
	{
		if (A.center() < B.center())
			return true;
		else if (A.center() == B.center())
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
				}
			}
		}
	}
	return false;
}

std::string QuadStarMotif::toStr() const
{
	std::stringstream ss;
	switch (dir_)
	{
	case NO_DIR:
		ss << "(" << center_ << ":" << a_ << "," << b_ << "," << c_ << ")";
		break;
	case ALL_OUT:
		ss << "(" << center_ << ":>" << a_ << ",>" << b_ << ",>" << c_ << ")";
		break;
	case ALL_IN:
		ss << "(" << center_ << ":<" << a_ << ",<" << b_ << ",<" << c_ << ")";
		break;
	case AB_OUT:
		ss << "(" << center_ << ":>" << a_ << ",>" << b_ << ",<" << c_ << ")";
		break;
	case AC_OUT:
		ss << "(" << center_ << ":>" << a_ << ",<" << b_ << ",>" << c_ << ")";
		break;
	case BC_OUT:
		ss << "(" << center_ << ":<" << a_ << ",>" << b_ << ",>" << c_ << ")";
		break;
	case A_OUT:
		ss << "(" << center_ << ":>" << a_ << ",<" << b_ << ",<" << c_ << ")";
		break;
	case B_OUT:
		ss << "(" << center_ << ":<" << a_ << ",>" << b_ << ",<" << c_ << ")";
		break;
	case C_OUT:
		ss << "(" << center_ << ":<" << a_ << ",<" << b_ << ",>" << c_ << ")";
		break;
	}
	return ss.str();
}

}

}

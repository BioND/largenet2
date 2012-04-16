/**
 * @file TripleMotif.cpp
 * @date 19.11.2010
 * @author gerd
 */

#include "TripleMotif.h"
#include <sstream>

namespace largenet
{

namespace motifs
{

bool operator==(const TripleMotif& A, const TripleMotif& B)
{
	return A.dir() == B.dir() && A.left() == B.left() && A.center()
			== B.center() && A.right() == B.right();
}

bool operator<(const TripleMotif& A, const TripleMotif& B)
{
	if (A.dir() < B.dir())
		return true;
	else if (A.dir() == B.dir())
	{
		if (A.left() < B.left())
			return true;
		else if (A.left() == B.left())
		{
			if (A.center() < B.center())
				return true;
			else if (A.center() == B.center())
			{
				if (A.right() < B.right())
					return true;
			}
		}
	}
	return false;
}

std::string TripleMotif::toStr() const
{
	std::stringstream ss;
	switch (dir_)
	{
	case NO_DIR:
		ss << "(" << left_ << "-" << center_ << "-" << right_ << ")";
		break;
	case LCR:
		ss << "(" << left_ << ">" << center_ << ">" << right_ << ")";
		break;
	case RCL: // should not happen anyway
		ss << "(" << left_ << "<" << center_ << "<" << right_ << ")";
		break;
	case CLR:
		ss << "(" << left_ << "<" << center_ << ">" << right_ << ")";
		break;
	case LRC:
		ss << "(" << left_ << ">" << center_ << "<" << right_ << ")";
		break;
	}
	return ss.str();
}

}

}

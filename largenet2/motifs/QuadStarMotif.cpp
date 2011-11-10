/**
 * @file QuadStarMotif.cpp
 * @date 23.11.2010
 * @author gerd
 */

#include "QuadStarMotif.h"
#include <sstream>
#include <stdexcept>

namespace largenet
{

namespace motifs
{

QuadStarMotif::QuadStarMotif(node_state_t center, node_state_t a,
		node_state_t b, node_state_t c, Direction dir) :
	center_(center), a_(a), b_(b), c_(c), dir_(dir)
{
	// order canonically
	if (b_ < a_)
	{
		std::swap(a_, b_);
		ArrowDir a_dir = (dir_ & a_in) ? a_in : a_out;
		ArrowDir b_dir = (dir_ & b_in) ? b_in : b_out;
		int temp = (dir_ ^ a_dir) ^ b_dir;
		dir_ = static_cast<Direction> (temp | (a_dir >> 4) | (b_dir << 4));
	}
	if (c_ < b_)
	{
		std::swap(c_, b_);
		ArrowDir b_dir = (dir_ & b_in) ? b_in : b_out;
		ArrowDir c_dir = (dir_ & c_in) ? c_in : c_out;
		int temp = (dir_ ^ b_dir) ^ c_dir;
		dir_ = static_cast<Direction> (temp | (b_dir >> 4) | (c_dir << 4));
	}
	if (b_ < a_)
	{
		std::swap(a_, b_);
		ArrowDir a_dir = (dir_ & a_in) ? a_in : a_out;
		ArrowDir b_dir = (dir_ & b_in) ? b_in : b_out;
		int temp = (dir_ ^ a_dir) ^ b_dir;
		dir_ = static_cast<Direction> (temp | (a_dir >> 4) | (b_dir << 4));
	}

	// set canonical (smallest) direction for symmetric states
	if (a_ == b_)
	{
		if (b_ == c_)
		{
			if (dir_ == B_OUT || dir_ == A_OUT)
				dir_ = C_OUT;
			else if (dir_ == AB_OUT || dir_ == AC_OUT)
				dir_ = BC_OUT;
		} else if (dir_ == AC_OUT)
			dir_ = BC_OUT;
		else if (dir_ == A_OUT)
			dir_ = B_OUT;
	}
	else if (b_ == c_) // a is smaller
	{
		if (dir_ == AB_OUT)
			dir_ = AC_OUT;
		else if (dir_ == B_OUT)
			dir_ = C_OUT;
	}
}

bool operator==(const QuadStarMotif& A, const QuadStarMotif& B)
{
	return A.dir() == B.dir() && A.a() == B.a() && A.b() == B.b() && A.c()
			== B.c() && A.center() == B.center();
}

bool operator<(const QuadStarMotif& A, const QuadStarMotif& B)
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
					else if (A.c() == B.c())
					{
						if (A.dir() < B.dir())
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

/**
 * @file QuadStarMotif.h
 * @date 23.11.2010
 * @author gerd
 */

#ifndef QUADSTARMOTIF_H_
#define QUADSTARMOTIF_H_

#include "../base/types.h"
#include <string>
#include <algorithm>

namespace largenet
{

namespace motifs
{

class QuadStarMotif
{
private:
	enum ArrowDir
	{
		a_in =  0x0100,
		a_out = 0x0200, // = a_in << 1
		b_in =  0x0010, // = a_in >> 4
		b_out = 0x0020,
		c_in =  0x0001,
		c_out = 0x0002
	};
public:
	enum Direction
	{
		NO_DIR = 0,
		ALL_IN = a_in | b_in | c_in,
		C_OUT = a_in | b_in | c_out,
		B_OUT = a_in | b_out | c_in,
		BC_OUT = a_in | b_out | c_out,
		A_OUT = a_out | b_in | c_in,
		AC_OUT = a_out | b_in | c_out,
		AB_OUT = a_out | b_out | c_in,
		ALL_OUT = a_out | b_out | c_out
	};
public:
	QuadStarMotif(node_state_t center, node_state_t a, node_state_t b,
			node_state_t c, Direction dir);

	bool isSymmetric() const
	{
		return a_ == b_ && b_ == c_ && (dir_ == ALL_IN || dir_ == ALL_OUT);
	}

	bool isMirrorSymmetric() const
	{
		return (a_ == b_ && (dir_ == C_OUT || dir_ == AB_OUT || dir_ == ALL_OUT
				|| dir_ == ALL_IN)) || (a_ == c_ && (dir_ == B_OUT || dir_
				== AC_OUT || dir_ == ALL_OUT || dir_ == ALL_IN)) || (b_ == c_
				&& (dir_ == A_OUT || dir_ == BC_OUT || dir_ == ALL_OUT || dir_
						== ALL_IN));
	}

	bool isDirected() const
	{
		return dir_ != NO_DIR;
	}

	Direction dir() const
	{
		return dir_;
	}

	std::string toStr() const;
	node_state_t center() const
	{
		return center_;
	}
	node_state_t a() const
	{
		return a_;
	}
	node_state_t b() const
	{
		return b_;
	}
	node_state_t c() const
	{
		return c_;
	}

private:
	node_state_t center_, a_, b_, c_;
	Direction dir_;
};

bool operator==(const QuadStarMotif& A, const QuadStarMotif& B);
bool operator<(const QuadStarMotif& A, const QuadStarMotif& B);

inline std::ostream& operator<<(std::ostream& out, const QuadStarMotif& q)
{
	return out << q.toStr();
}
}

}

#endif /* QUADSTARMOTIF_H_ */

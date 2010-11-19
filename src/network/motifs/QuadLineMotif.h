/**
 * @file QuadLineMotif.h
 * @date 19.11.2010
 * @author gerd
 */

#ifndef QUADLINEMOTIF_H_
#define QUADLINEMOTIF_H_

#include "../base/types.h"
#include <string>
#include <algorithm>

namespace largenet
{

namespace motifs
{

class QuadLineMotif
{
private:
	enum ArrowDirs
	{
		right1 = 0x0001,
		right2 = 0x0002,
		right3 = 0x0004,
		left1 = 0x0010,
		left2 = 0x0020,
		left3 = 0x0040
	};
public:
	enum Direction
	{
		NO_DIR = 0, RLINE = right1 | right2 | right3, // a->b->c->d
		C_IN = right1 | right2 | left3, // a->b->c<-d
		B_IN_C_OUT = right1 | left2 | right3, // a->b<-c->d
		B_IN = right1 | left2 | left3, // a->b<-c<-d
		B_OUT = left1 | right2 | right3, // a<-b->c->d
		B_OUT_C_IN = left1 | right2 | left3, // a<-b->c<-d
		C_OUT = left1 | left2 | right3, // a<-b<-c->d
		LLINE = left1 | left2 | left3
	// a<-b<-c<-d
	};
public:
	QuadLineMotif(node_state_t a, node_state_t b, node_state_t c,
			node_state_t d, Direction dir) :
		a_(a), b_(b), c_(c), d_(d), dir_(dir)
	{
		if (dir_ == NO_DIR)
		{
			// store undirected motifs in ordered fashion
			if (a_ > d_)
			{
				std::swap(a_, d_);
				std::swap(b_, c_);
			}
			else if (a_ == d_)
			{
				if (b_ > c_)
					std::swap(b_, c_);
			}
		} else if (dir_ == LLINE)
		{
			std::swap(a_, d_);
			std::swap(b_, c_);
			dir_ = RLINE;
		}
	}

	bool isSymmetric() const
	{
		return dir_ == NO_DIR && a_ == d_ && b_ == c_;
	}

	bool isDirected() const
	{
		return dir_ != NO_DIR;
	}

	std::string toStr() const;

	node_state_t a() const { return a_; }
	node_state_t b() const { return b_; }
	node_state_t c() const { return c_; }
	node_state_t d() const { return d_; }
	Direction dir() const { return dir_; }
private:
	node_state_t a_, b_, c_, d_;
	Direction dir_;
};

bool operator==(const QuadLineMotif& A, const QuadLineMotif& B);
bool operator<(const QuadLineMotif& A, const QuadLineMotif& B);

inline std::ostream& operator<<(std::ostream& out, const QuadLineMotif& q)
{
	return out << q.toStr();
}

}

}

#endif /* QUADLINEMOTIF_H_ */

/**
 * @file TripleMotif.h
 * @date 19.11.2010
 * @author gerd
 */

#ifndef TRIPLEMOTIF_H_
#define TRIPLEMOTIF_H_

#include <largenet2/base/types.h>
#include <string>
#include <algorithm>
#include <iostream>

namespace largenet
{

namespace motifs
{

class TripleMotif
{
public:
	enum Direction
	{
		NO_DIR, // undirected
		LCR, // l->c->r
		CLR, // l<-c->r
		RCL, // l<-c<-r
		LRC
	// l->c<-r
	};
public:
	TripleMotif(node_state_t left, node_state_t center, node_state_t right,
			Direction dir) :
		left_(left), center_(center), right_(right), dir_(dir)
	{
		if (dir_ == NO_DIR || dir_ == CLR || dir_ == LRC)
		{
			// store symmetric directions in canonical order
			if (left_ > right_)
				std::swap(left_, right_);
		}
		else if (dir_ == RCL)
		{
			// and always store line triples as LCR
			std::swap(left_, right_);
			dir_ = LCR;
		}
	}

	node_state_t left() const { return left_; }
	node_state_t center() const { return center_; }
	node_state_t right() const { return right_; }

	std::string toStr() const;
	Direction dir() const { return dir_; }
	bool isDirected() const
	{
		return dir_ != NO_DIR;
	}
	bool isSymmetric() const
	{
		return (dir_ == NO_DIR || dir_ == CLR || dir_ == LRC) && left_
				== right_;
	}
private:
	node_state_t left_, center_, right_;
	Direction dir_;
};

bool operator==(const TripleMotif& A, const TripleMotif& B);
bool operator<(const TripleMotif& A, const TripleMotif& B);

inline std::ostream& operator<<(std::ostream& out, const TripleMotif& t)
{
	return out << t.toStr();
}

}

}

#endif /* TRIPLEMOTIF_H_ */

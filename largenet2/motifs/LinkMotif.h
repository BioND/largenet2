/*
 * LinkMotif.h
 *
 *  Created on: 03.02.2009
 *      Author: gerd
 */

#ifndef LINKMOTIF_H_
#define LINKMOTIF_H_

#include <largenet2/base/types.h>
#include <string>
#include <iostream>
#include <algorithm> // for std::swap

namespace largenet
{
namespace motifs
{

/**
 * A link motif. State fields @p a, @p b are ordered if link is undirected.
 */
class LinkMotif
{
public:
	/**
	 * Constructor.
	 * @param source Source node state
	 * @param target Target node state
	 * @param directed True if link is directed
	 */
	LinkMotif(node_state_t source, node_state_t target, bool directed = true) :
		s_(source), t_(target), directed_(directed)
	{
		if ((!directed) && (s_ > t_))
			std::swap(s_, t_);
	}

	std::string toStr() const;
	node_state_t source() const { return s_; }
	node_state_t target() const { return t_; }
	bool isDirected() const { return directed_; }
	bool isSymmetric() const { return (!directed_) && (s_ == t_); }

private:
	node_state_t s_, t_;
	bool directed_;
};

bool operator==(const LinkMotif& A, const LinkMotif& B);
bool operator<(const LinkMotif& A, const LinkMotif& B);

inline std::ostream& operator<<(std::ostream& out, const LinkMotif& t)
{
	return out << t.toStr();
}

}
}
#endif /* LINKMOTIF_H_ */

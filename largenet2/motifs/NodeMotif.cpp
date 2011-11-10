/*
 * NodeMotif.cpp
 *
 *  Created on: 03.02.2009
 *      Author: gerd
 */

#include "NodeMotif.h"
#include <sstream>

namespace largenet
{
namespace motifs
{

std::string NodeMotif::toStr() const
{
	std::stringstream ss;
	ss << "(" << n_ << ")";
	return ss.str();
}

bool operator==(const NodeMotif& A, const NodeMotif& B)
{
	return static_cast<node_state_t> (A) == static_cast<node_state_t> (B);
}

bool operator<(const NodeMotif& A, const NodeMotif& B)
{
	return static_cast<node_state_t> (A) < static_cast<node_state_t> (B);
}

std::ostream& operator<<(std::ostream& out, const NodeMotif& n)
{
	return out << n.toStr();
}

}
}

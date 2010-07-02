/*
 * NodeMotif.h
 *
 *  Created on: 03.02.2009
 *      Author: gerd
 */

#ifndef NODEMOTIF_H_
#define NODEMOTIF_H_

#include "../base/types.h"
#include <string>
#include <iostream>
#include <set>

namespace largenet
{
namespace motifs {

class NodeMotif
{
public:
	NodeMotif(node_state_t n);
	std::string toStr() const;
	operator node_state_t() const;
private:
	node_state_t n_;
};

bool operator==(const NodeMotif& A, const NodeMotif& B);
bool operator<(const NodeMotif& A, const NodeMotif& B);
std::ostream& operator<<(std::ostream& out, const NodeMotif& t);

inline NodeMotif::NodeMotif(const node_state_t n) : n_(n)
{
}

inline NodeMotif::operator node_state_t() const
{
	return n_;
}

}
}
#endif /* NODEMOTIF_H_ */

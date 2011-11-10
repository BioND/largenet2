/**
 * @file Edge.cpp
 * @date 01.09.2009
 * @author gerd
 */

#include "Edge.h"
#include "Node.h"

namespace largenet
{

Node* Edge::opposite(const Node& from) const
{
	if (&from == source_)
		return target_;
	else if (&from == target_)
		return source_;
	else
		throw(std::invalid_argument("Edge is not attached to given node."));
}

void Edge::connect()
{
	if ((source_ == 0) || (target_ == 0))
		return;
	source_->registerEdge(this);
	target_->registerEdge(this);
}

void Edge::disconnect()
{
	if (source_ != 0)
		source_->unregisterEdge(this);
	if (target_ != 0)
		target_->unregisterEdge(this);
}

}

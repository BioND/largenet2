/**
 * @file StateConsistencyListener.h
 * @date 02.11.2009
 * @author gerd
 */

#ifndef STATECONSISTENCYLISTENER_H_
#define STATECONSISTENCYLISTENER_H_

#include "base/GraphListener.h"
#include <memory>

namespace largenet {

template<class EdgeStateCalculator>
class StateConsistencyListener: public largenet::GraphListener
{
public:
	StateConsistencyListener(std::auto_ptr<EdgeStateCalculator> lsc) :
		lsc_(lsc)
	{
		if (lsc_.get() == 0)
			lsc_ = std::auto_ptr<EdgeStateCalculator>(new EdgeStateCalculator);
	}
	virtual ~StateConsistencyListener()
	{
	}

	EdgeStateCalculator& edgeStateCalculator() const { return *lsc_; }
private:
	virtual void afterEdgeAddEvent(largenet::Graph& g, largenet::Edge& e)
	{
		g.setEdgeState(e.id(), (*lsc_)(g.nodeState(e.source()->id()),
				g.nodeState(e.target()->id())));
	}
	virtual void afterNodeStateChangeEvent(largenet::Graph& g,
			largenet::Node& n, largenet::node_state_t oldState,
			largenet::node_state_t newState)
	{
		largenet::Node::edge_iterator_range out = n.outEdges();
		for (largenet::Node::edge_iterator it = out.first; it != out.second; ++it)
			g.setEdgeState((*it)->id(), (*lsc_)(g.nodeState((*it)->source()->id()),
					g.nodeState((*it)->target()->id())));
		largenet::Node::edge_iterator_range in = n.inEdges();
		for (largenet::Node::edge_iterator it = in.first; it != in.second; ++it)
			g.setEdgeState((*it)->id(), (*lsc_)(g.nodeState((*it)->source()->id()),
					g.nodeState((*it)->target()->id())));
	}
	std::auto_ptr<EdgeStateCalculator> lsc_;
};
}
#endif /* STATECONSISTENCYLISTENER_H_ */

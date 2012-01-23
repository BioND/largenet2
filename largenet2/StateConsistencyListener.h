/**
 * @file StateConsistencyListener.h
 * @date 02.11.2009
 * @author gerd
 */

#ifndef STATECONSISTENCYLISTENER_H_
#define STATECONSISTENCYLISTENER_H_

#include <largenet2/base/GraphListener.h>
#include <memory>

namespace largenet {

/**
 * Ensure edge states that are consistent with node states.
 *
 * This graph listener updates the states of all adjacent
 * edges whenever a node changes its state. The edge states are
 * computed using a user-supplied edge state calculator.
 *
 * @tparam EdgeStateCalculator Functor computing an appropriate
 * 		   edge state from given source and target node states.
 */
template<class EdgeStateCalculator>
class StateConsistencyListener: public largenet::GraphListener
{
public:
	/**
	 * Create a new StateConsistencyListener object
	 * @param lsc Pointer to an edge state calculator object. Note that
	 * 			  the listener takes ownership of the edge state calculator,
	 * 			  deleting it when the listener is destroyed.
	 */
	StateConsistencyListener(std::auto_ptr<EdgeStateCalculator> lsc) :
		lsc_(lsc)
	{
		if (lsc_.get() == 0)
			lsc_ = std::auto_ptr<EdgeStateCalculator>(new EdgeStateCalculator);
	}
	virtual ~StateConsistencyListener()
	{
	}

	/**
	 * Get the edge state calculator object used by the listener
	 * @return edge state calculator
	 */
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
		largenet::Node::edge_iterator_range un = n.undirectedEdges();
		for (largenet::Node::edge_iterator it = un.first; it != un.second; ++it)
			g.setEdgeState((*it)->id(), (*lsc_)(g.nodeState((*it)->source()->id()),
					g.nodeState((*it)->target()->id())));
	}
	std::auto_ptr<EdgeStateCalculator> lsc_;
};
}
#endif /* STATECONSISTENCYLISTENER_H_ */

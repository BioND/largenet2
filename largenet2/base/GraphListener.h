#ifndef GRAPHLISTENER_H_
#define GRAPHLISTENER_H_

#include <largenet2/base/types.h>

namespace largenet
{

class Graph;
class Node;
class Edge;

/**
 * Listener interface for listening to graph events.
 */
class GraphListener
{
public:
	GraphListener() {}
	virtual ~GraphListener() {}

	void afterNodeAdd(Graph& g, Node& n) { afterNodeAddEvent(g, n); }
	void afterEdgeAdd(Graph& g, Edge& e) { afterEdgeAddEvent(g, e); }
	void beforeNodeRemove(Graph& g, Node& n) { beforeNodeRemoveEvent(g, n); }
	void beforeEdgeRemove(Graph& g, Edge& e) { beforeEdgeRemoveEvent(g, e); }
	void beforeGraphClear(Graph& g) { beforeGraphClearEvent(g); }
	void afterNodeStateChange(Graph& g, Node& n, node_state_t oldState, node_state_t newState)
	{
		afterNodeStateChangeEvent(g, n, oldState, newState);
	}
	void afterEdgeStateChange(Graph& g, Edge& e, edge_state_t oldState, edge_state_t newState)
	{
		afterEdgeStateChangeEvent(g, e, oldState, newState);
	}

private:
	// these are not pure virtual, to ease implementing only a few methods
	virtual void afterNodeAddEvent(Graph& g, Node& n) {}
	virtual void afterEdgeAddEvent(Graph& g, Edge& e) {}
	virtual void beforeNodeRemoveEvent(Graph& g, Node& n) {}
	virtual void beforeEdgeRemoveEvent(Graph& g, Edge& e) {}
	virtual void beforeGraphClearEvent(Graph& g) {}
	virtual void afterNodeStateChangeEvent(Graph& g, Node& n, node_state_t oldState, node_state_t newState) {}
	virtual void afterEdgeStateChangeEvent(Graph& g, Edge& e, edge_state_t oldState, edge_state_t newState) {}
};

}

#endif /* GRAPHLISTENER_H_ */

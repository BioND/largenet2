#ifndef FACTORIES_H_
#define FACTORIES_H_

#include <largenet2/base/ElementFactory.h>
#include <largenet2/base/Edge.h>
#include <largenet2/base/SingleNode.h>
#include <largenet2/base/MultiNode.h>

namespace largenet
{

/**
 * Basic graph element factory template
 * @tparam NodeType type of node elements
 * @tparam EdgeType type of edge elements
 */
template<class NodeType = SingleNode, class EdgeType = Edge>
class GraphElementFactory: public ElementFactory
{
private:
	virtual NodeType* doCreateNode(node_id_t id)
	{
		return new NodeType(id);
	}

	virtual EdgeType* doCreateEdge(edge_id_t id, Node& source, Node& target, bool directed)
	{
		return EdgeType::create(id, source, target, directed);
	}
};

/**
 * Element factory for simple graphs in which no parallel edges are allowed
 */
typedef GraphElementFactory<SingleNode, Edge> SingleEdgeElementFactory;
/**
 * Element factory for non-simple graphs, in which parallel edges are allowed
 */
typedef GraphElementFactory<MultiNode, Edge> MultiEdgeElementFactory;

}

#endif /* FACTORIES_H_ */

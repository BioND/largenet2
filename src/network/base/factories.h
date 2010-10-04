/**
 * @file Factories.h
 * @date 02.11.2009
 * @author gerd
 */

#ifndef FACTORIES_H_
#define FACTORIES_H_

#include "ElementFactory.h"
#include "Edge.h"
#include "SingleNode.h"
#include "MultiNode.h"

namespace largenet
{

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

typedef GraphElementFactory<SingleNode, Edge>
		SingleUndirectedElementFactory;
typedef GraphElementFactory<MultiNode, Edge>
		MultiUndirectedElementFactory;
typedef GraphElementFactory<SingleNode, Edge>
		SingleDirectedElementFactory;
typedef GraphElementFactory<MultiNode, Edge>
		MultiDirectedElementFactory;

}

#endif /* FACTORIES_H_ */

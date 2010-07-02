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

template<class NodeType = SingleNode, class EdgeType = UndirectedEdge>
class GraphElementFactory: public ElementFactory
{
private:
	virtual NodeType* doCreateNode(node_id_t id)
	{
		return new NodeType(id);
	}

	virtual EdgeType* doCreateEdge(edge_id_t id, Node& source, Node& target)
	{
		return EdgeType::create(id, source, target);
	}

	virtual bool doDirectedEdges() const
	{
		return is_directed<EdgeType>(0);
	}
};

typedef GraphElementFactory<SingleNode, UndirectedEdge>
		SingleUndirectedElementFactory;
typedef GraphElementFactory<MultiNode, UndirectedEdge>
		MultiUndirectedElementFactory;
typedef GraphElementFactory<SingleNode, DirectedEdge>
		SingleDirectedElementFactory;
typedef GraphElementFactory<MultiNode, DirectedEdge>
		MultiDirectedElementFactory;

}

#endif /* FACTORIES_H_ */

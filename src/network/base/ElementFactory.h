/**
 * @file ElementFactory.h
 * @date 18.08.2009
 * @author gerd
 */

#ifndef ELEMENTFACTORY_H_
#define ELEMENTFACTORY_H_

#include "types.h"

namespace largenet
{

class Node;
class Edge;
//class Triple;

class ElementFactory
{
public:
	ElementFactory()
	{
	}
	virtual ~ElementFactory()
	{
	}
	Node* createNode(node_id_t id)
	{
		return doCreateNode(id);
	}
	Edge* createEdge(edge_id_t id, Node& source, Node& target, bool directed)
	{
		return doCreateEdge(id, source, target, directed);
	}
	//Triple* createTriple(edge_id_t left, edge_id_t right);	FIXME directed triples?
private:
	virtual Node* doCreateNode(node_id_t id) = 0;
	virtual Edge* doCreateEdge(edge_id_t id, Node& source, Node& target, bool directed) = 0;
};

}

#endif /* ELEMENTFACTORY_H_ */

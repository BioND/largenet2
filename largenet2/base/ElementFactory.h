/**
 * @file ElementFactory.h
 * @date 18.08.2009
 * @author gerd
 */

#ifndef ELEMENTFACTORY_H_
#define ELEMENTFACTORY_H_

#include <largenet2/base/types.h>

namespace largenet
{

class Node;
class Edge;
//class Triple;

/**
 * Basic graph element factory used to create nodes and edges as required
 */
class ElementFactory
{
public:
	/**
	 * Constructor
	 */
	ElementFactory()
	{
	}
	/**
	 * Destructor
	 */
	virtual ~ElementFactory()
	{
	}
	/**
	 * Create a new node with ID @p id
	 * @param id node ID
	 * @return pointer to the new node
	 */
	Node* createNode(node_id_t id)
	{
		return doCreateNode(id);
	}
	/**
	 * Create a new edge with ID @p id connecting @p source and @p target
	 * @param id edge ID
	 * @param source source node
	 * @param target target node
	 * @param directed create a directed edge?
	 * @return
	 */
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

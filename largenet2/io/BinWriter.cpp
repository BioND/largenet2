/**
 * @file BinWriter.cpp
 * @date 15.12.2011
 * @author gerd
 */

#include "BinWriter.h"
#include <largenet2/base/Graph.h>
#include <boost/foreach.hpp>

using namespace std;

namespace largenet
{
namespace io
{

void BinWriter::write(const Graph& g, ostream& strm)
{
	streambuf* buf = strm.rdbuf();
	node_size_t N = g.numberOfNodes();
	edge_size_t L = g.numberOfEdges();
	node_state_size_t node_states = g.numberOfNodeStates();
	edge_state_size_t edge_states = g.numberOfEdgeStates();
	buf->sputn((char*)(&N), sizeof(N));
	buf->sputn((char*)(&L), sizeof(L));
	buf->sputn((char*)(&node_states), sizeof(node_states));
	buf->sputn((char*)(&edge_states), sizeof(edge_states));

	node_id_t nid = 0;
	node_state_t nst = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		nid = n.id();
		nst = g.nodeState(nid);
		buf->sputn((char*)(&nid), sizeof(nid));
		buf->sputn((char*)(&nst), sizeof(nst));
	}
	node_id_t sid = 0, tid = 0;
	edge_state_t est = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		sid = e.source()->id();
		tid = e.target()->id();
		est = g.edgeState(e.id());
		buf->sputn((char*)(&sid), sizeof(sid));
		buf->sputn((char*)(&tid), sizeof(tid));
		buf->sputn((char*)(&est), sizeof(est));
	}
}

} /* namespace io */
} /* namespace largenet */

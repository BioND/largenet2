/**
 * @file BinReader.cpp
 * @date 16.12.2011
 * @author gerd
 */

#include "BinReader.h"
#include <largenet2.h>
#include <map>
#include <utility>

using namespace std;

namespace largenet
{
namespace io
{

Graph* largenet::io::BinReader::createFromStream(std::istream& strm)
{
	streambuf* buf = strm.rdbuf();
	node_size_t N = 0;
	edge_size_t L = 0;
	node_state_size_t node_states = 0;
	edge_state_size_t edge_states = 0;
	buf->sgetn((char*) (&N), sizeof(N));
	buf->sgetn((char*) (&L), sizeof(L));
	buf->sgetn((char*) (&node_states), sizeof(node_states));
	buf->sgetn((char*) (&edge_states), sizeof(edge_states));

	Graph* graph = new Graph(node_states, edge_states);

	typedef pair<node_id_t, node_state_t> node_info_t;
	typedef map<node_id_t, node_info_t> node_map_t;
	node_map_t node_map;
	node_info_t item(0, 0);
	node_id_t nid = 0;
	for (node_size_t i = 0; i < N; ++i)
	{
		item.second = 0;
		buf->sgetn((char*)(&nid), sizeof(nid));
		buf->sgetn((char*)(&item.second), sizeof(item.second));
		item.first = graph->addNode(item.second);
		node_map.insert(make_pair(nid, item));
	}
	node_id_t sid = 0, tid = 0;
	edge_state_t est = 0;
	edge_id_t eid = 0;
	for (edge_size_t i = 0; i < L; ++i)
	{
		buf->sgetn((char*)(&sid), sizeof(sid));
		buf->sgetn((char*)(&tid), sizeof(tid));
		buf->sgetn((char*)(&est), sizeof(est));
		eid = graph->addEdge(node_map[sid].first, node_map[tid].first, true);
		graph->setEdgeState(eid, est);
	}
	return graph;
}

} /* namespace io */
} /* namespace largenet */

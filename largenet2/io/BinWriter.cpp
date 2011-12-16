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
	strm << g.numberOfNodes() << g.numberOfEdges() << g.numberOfNodeStates();
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		strm << n.id() << g.nodeState(n.id());
	}
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		strm << e.source()->id() << e.target()->id();
	}
}

} /* namespace io */
} /* namespace largenet */

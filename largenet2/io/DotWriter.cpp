/**
 * @file DotWriter.cpp
 * @date 16.12.2011
 * @author gerd
 */

#include "DotWriter.h"
#include <largenet2.h>
#include <boost/foreach.hpp>

namespace largenet
{
namespace io
{

void DotWriter::write(const Graph& g, std::ostream& strm)
{
	// FIXME here we need a way to find out if the graph is directed or
	// undirected. We should define this on the graph-level rather than
	// allowing both directed and undirected edges in the same graph

	const char tab = '\t';
	strm << "digraph \"" << &g << "\" {\n";
	BOOST_FOREACH(const Node& n, g.nodes())
			{
				strm << tab << n.id() << " [state=" << g.nodeState(n.id())
						<< "]\n";
			}
	BOOST_FOREACH(const Edge& e, g.edges())
			{
				strm << tab << e.source()->id() << " -> " << e.target()->id()
						<< " [state=" << g.edgeState(e.id()) << "]\n";
			}
	strm << "}\n";
}

} /* namespace io */
} /* namespace largenet */

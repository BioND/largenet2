/**
 * @file EdgeListWriter.cpp
 * @date 06.10.2010
 * @author gerd
 */

#include "EdgeListWriter.h"
#include <largenet2/base/Graph.h>
#include <iostream>
#include <boost/foreach.hpp>

namespace largenet
{

namespace io
{

void EdgeListWriter::write(const Graph& g, std::ostream& strm)
{
	if (g.numberOfNodes() == 0)
		return;

	BOOST_FOREACH(const Edge& e, g.edges())
	{
		strm << e.source()->id() << "\t" << e.target()->id() << "\n";
	}
}

}

}

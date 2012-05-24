/*
 * GraphMLWriter.cpp
 *
 *  Created on: 23.05.2012
 *      Author: gerd
 */

#include "GraphMLWriter.h"
#include <largenet2/boost/largenet2_boost.h>
#include <largenet2/boost/property_graph.h>
#include <boost/graph/graphml.hpp>

namespace largenet
{
namespace io
{

void GraphMLWriter::write(const Graph& g, std::ostream& strm)
{
	boost::dynamic_properties dp;
	boost::write_graphml(strm, g, dp, true);
}

} /* namespace io */
} /* namespace largenet */

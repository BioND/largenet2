/**
 * @file DotWriter.cpp
 * @date 16.12.2011
 * @author gerd
 */

#include "DotWriter.h"
#include <largenet2.h>
#include <boost/foreach.hpp>
#include <largenet2/boost/largenet2_boost.h>
#include <largenet2/boost/property_graph.h>
#include <boost/graph/graphviz.hpp>

namespace largenet
{
namespace io
{

void DotWriter::write(const Graph& g, std::ostream& strm)
{
	boost::write_graphviz(strm, g);
}

} /* namespace io */
} /* namespace largenet */

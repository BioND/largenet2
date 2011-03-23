/*
 * InOutDegreeMatrix.cpp
 *
 *  Created on: 23.03.2011
 *      Author: gerd
 */

#include "InOutDegreeMatrix.h"
#include "measures.h"
#include <boost/foreach.hpp>

namespace largenet
{
namespace measures
{

InOutDegreeMatrix::InOutDegreeMatrix(const Graph& g) :
	mat_(maxInDegree(g) + 1, maxOutDegree(g) + 1)
{
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		mat_(n.inDegree(), n.outDegree()) += 1;
	}
}

}
}

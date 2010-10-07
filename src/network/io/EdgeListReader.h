/**
 * @file EdgeListReader.h
 * @date 06.10.2010
 * @author gerd
 */

#ifndef EDGELISTREADER_H_
#define EDGELISTREADER_H_

#include "GraphReader.h"

namespace largenet
{

namespace io
{

class EdgeListReader: public GraphReader
{
public:
	EdgeListReader() {}
	virtual ~EdgeListReader() {}
	Graph* createFromStream(std::istream& strm);
};

}

}

#endif /* EDGELISTREADER_H_ */

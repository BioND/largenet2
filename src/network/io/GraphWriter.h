/**
 * @file GraphWriter.h
 * @date 06.10.2010
 * @author gerd
 */

#ifndef GRAPHWRITER_H_
#define GRAPHWRITER_H_

#include <iostream>

namespace largenet
{

class Graph;

namespace io
{

class GraphWriter
{
public:
	GraphWriter() {}
	virtual ~GraphWriter() {}
	virtual void write(const Graph& g, std::ostream& strm) = 0;
};

}

}

#endif /* GRAPHWRITER_H_ */

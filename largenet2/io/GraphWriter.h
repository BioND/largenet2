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

/**
 * Graph writer interface
 */
class GraphWriter
{
public:
	GraphWriter() {}
	virtual ~GraphWriter() {}
	/**
	 * Write graph to stream
	 * @param g graph to write to stream
	 * @param strm stream to write to
	 */
	virtual void write(const Graph& g, std::ostream& strm) = 0;
};

}

}

#endif /* GRAPHWRITER_H_ */

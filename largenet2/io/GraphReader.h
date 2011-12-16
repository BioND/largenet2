/**
 * @file GraphReader.h
 * @date 06.10.2010
 * @author gerd
 */

#ifndef GRAPHREADER_H_
#define GRAPHREADER_H_

#include <iostream>

namespace largenet
{

class Graph;

/**
 * graph I/O functionality
 */
namespace io
{

/**
 * Graph reader interface
 */
class GraphReader
{
public:
	GraphReader() {}
	virtual ~GraphReader() {}
	/**
	 * Create a new Graph object from stream
	 * @param strm Stream to read graph data from
	 * @return pointer to new graph object
	 */
	virtual Graph* createFromStream(std::istream& strm) = 0;
};

}

}

#endif /* GRAPHREADER_H_ */

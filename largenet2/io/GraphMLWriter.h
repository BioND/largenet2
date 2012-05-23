/*
 * GraphMLWriter.h
 *
 *  Created on: 23.05.2012
 *      Author: gerd
 */

#ifndef GRAPHMLWRITER_H_
#define GRAPHMLWRITER_H_

#include <largenet2/io/GraphWriter.h>

namespace largenet
{
namespace io
{

class GraphMLWriter: public GraphWriter
{
public:
	GraphMLWriter() : GraphWriter() {}
	virtual ~GraphMLWriter() {}
	void write(const Graph& g, std::ostream& strm);
};

} /* namespace io */
} /* namespace largenet */
#endif /* GRAPHMLWRITER_H_ */

/**
 * @file EdgeListWriter.h
 * @date 06.10.2010
 * @author gerd
 */

#ifndef EDGELISTWRITER_H_
#define EDGELISTWRITER_H_

#include <largenet2/io/GraphWriter.h>

namespace largenet
{

namespace io
{

class EdgeListWriter: public GraphWriter
{
public:
	EdgeListWriter() {}
	virtual ~EdgeListWriter() {}
	void write(const Graph& g, std::ostream& strm);
};

}

}

#endif /* EDGELISTWRITER_H_ */

/**
 * @file IntervalOutput.h
 * @date 30.07.2009
 * @author gerd
 */

#ifndef INTERVALOUTPUT_H_
#define INTERVALOUTPUT_H_

#include <iostream>
#include <string>

namespace sim
{
namespace output
{

class IntervalOutput
{
public:
	IntervalOutput(std::ostream& out, double interval, std::string commentChar =
			"#");
	virtual ~IntervalOutput();
	void setCommentChar(const std::string& commentChar);
	std::string commentChar() const;
	void output(double t, bool force=false);
	void writeHeader();
protected:
	std::ostream& stream() const;
private:
	virtual void doOutput(double t) = 0;
	virtual void doWriteHeader() = 0;
	double interval_, nextOutputTime_;
	std::ostream& out_;
	std::string commentChar_;
};

inline std::ostream& IntervalOutput::stream() const
{
	return out_;
}

inline void IntervalOutput::setCommentChar(const std::string& commentChar)
{
	commentChar_ = commentChar;
}

inline std::string IntervalOutput::commentChar() const
{
	return commentChar_;
}

inline void IntervalOutput::writeHeader()
{
	doWriteHeader();
}

}
}

#endif /* INTERVALOUTPUT_H_ */

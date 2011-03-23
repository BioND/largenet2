/*
 * InOutDegreeMatrix.h
 *
 *  Created on: 22.03.2011
 *      Author: gerd
 */

#ifndef INOUTDEGREEMATRIX_H_
#define INOUTDEGREEMATRIX_H_

#include "../base/Graph.h"
#include <boost/noncopyable.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <stdexcept>
#include <iostream>

namespace largenet
{

namespace measures
{

namespace bnu = boost::numeric::ublas;

class InOutDegreeMatrix: public boost::noncopyable
{
public:
	friend std::ostream& operator<<(std::ostream& out, const InOutDegreeMatrix& m);
public:
	typedef bnu::mapped_matrix<node_size_t, bnu::row_major, bnu::map_std<
			largenet::degree_t, node_size_t> > matrix_data_t;
public:
	explicit InOutDegreeMatrix(const Graph& g);
	virtual ~InOutDegreeMatrix()
	{
	}

	node_size_t operator()(degree_t k_in, degree_t k_out) const
	{
		return mat_(k_in, k_out);
	}

private:
	matrix_data_t mat_;
};

inline std::ostream& operator<<(std::ostream& out, const InOutDegreeMatrix& m)
{
	typedef InOutDegreeMatrix::matrix_data_t::size_type sz_t;
	for (sz_t i = 0; i < m.mat_.size1(); ++i)
	{
		for (sz_t j = 0; j < m.mat_.size2() - 1; ++j)
		{
			out << m.mat_(i, j) << " ";
		}
		out << m.mat_(i, m.mat_.size2() - 1) << "\n";
	}
	return out;
}

}

}

#endif /* INOUTDEGREEMATRIX_H_ */

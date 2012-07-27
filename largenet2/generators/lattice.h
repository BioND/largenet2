#ifndef LATTICE_H_
#define LATTICE_H_

#include <vector>
#include <boost/foreach.hpp>

namespace largenet
{
namespace generators
{
namespace detail
{
template<class T>
class PeriodicGrid
{
	typedef std::vector<T> row_vector_t;
	typedef std::vector<row_vector_t> grid_t;

	typedef typename row_vector_t::reference reference;
	typedef typename row_vector_t::const_reference const_reference;

public:
	PeriodicGrid(size_t rows, size_t cols) :
			rows_(rows), cols_(cols), data_(rows)
	{
		BOOST_FOREACH(row_vector_t& row, data_)
		{
			row.resize(cols_);
		}
	}

	reference operator()(long i, long j)
	{
		return data_[wrapRow(i)][wrapCol(j)];
	}

	const_reference operator()(long i, long j) const
	{
		return data_[wrapRow(i)][wrapCol(j)];
	}

private:
	PeriodicGrid(const PeriodicGrid&);
	PeriodicGrid& operator=(const PeriodicGrid&);
	size_t wrapRow(long i) const
	{
		while (i < 0)
			i += rows_;
		while (i >= rows_)
			i -= rows_;
		return i;
	}

	size_t wrapCol(long i) const
	{
		while (i < 0)
			i += cols_;
		while (i >= cols_)
			i -= cols_;
		return i;
	}
private:
	size_t rows_, cols_;
	grid_t data_;
};
}

void vonNeumannLattice2DPeriodic(Graph& g, node_size_t rows, node_size_t cols)
{
	g.clear();
	detail::PeriodicGrid<node_id_t> grid(rows, cols);

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			grid(i, j) = g.addNode();

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
		{
			g.addEdge(grid(i, j - 1), grid(i, j), false);
			g.addEdge(grid(i, j + 1), grid(i, j), false);
			g.addEdge(grid(i - 1, j), grid(i, j), false);
			g.addEdge(grid(i + 1, j), grid(i, j), false);
		}
}

void mooreLattice2DPeriodic(Graph& g, node_size_t rows, node_size_t cols)
{
	g.clear();
	detail::PeriodicGrid<node_id_t> grid(rows, cols);
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			grid(i, j) = g.addNode();

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
		{
			g.addEdge(grid(i, j - 1), grid(i, j), false);
			g.addEdge(grid(i, j + 1), grid(i, j), false);
			g.addEdge(grid(i - 1, j), grid(i, j), false);
			g.addEdge(grid(i + 1, j), grid(i, j), false);

			g.addEdge(grid(i - 1, j - 1), grid(i, j), false);
			g.addEdge(grid(i - 1, j + 1), grid(i, j), false);
			g.addEdge(grid(i + 1, j - 1), grid(i, j), false);
			g.addEdge(grid(i + 1, j + 1), grid(i, j), false);
		}
}

}
}

#endif /* LATTICE_H_ */

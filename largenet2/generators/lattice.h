#ifndef LATTICE_H_
#define LATTICE_H_

#include <vector>
#include <boost/foreach.hpp>
#include <stdexcept>

namespace largenet
{
namespace generators
{
namespace detail
{

class NoWrapChecked
{
public:
	NoWrapChecked(size_t rows, size_t cols) :
			rows_(rows), cols_(cols)
	{
	}
	size_t wrapRow(long i) const
	{
		if (i < 0 || i > rows_)
			throw std::out_of_range("Row index out of bounds");
		else
			return i;
	}
	size_t wrapCol(long i) const
	{
		if (i < 0 || i > cols_)
			throw std::out_of_range("Column index out of bounds");
		else
			return i;
	}
protected:
	~NoWrapChecked()
	{
	}
private:
	size_t rows_, cols_;
};

class PeriodicWrap
{
public:
	PeriodicWrap(size_t rows, size_t cols) :
			rows_(rows), cols_(cols)
	{
	}
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
protected:
	~PeriodicWrap()
	{
	}
private:
	size_t rows_, cols_;
};

template<class T, class IndexWrapPolicy>
class Grid: public IndexWrapPolicy
{
	typedef std::vector<T> row_vector_t;
	typedef std::vector<row_vector_t> grid_t;

	typedef typename row_vector_t::reference reference;
	typedef typename row_vector_t::const_reference const_reference;
public:
	Grid(size_t rows, size_t cols) :
			IndexWrapPolicy(rows, cols), data_(rows)
	{
		BOOST_FOREACH(row_vector_t& row, data_)
		{
			row.resize(cols);
		}
	}

	reference operator()(long i, long j)
	{
		return data_[IndexWrapPolicy::wrapRow(i)][IndexWrapPolicy::wrapCol(j)];
	}

	const_reference operator()(long i, long j) const
	{
		return data_[IndexWrapPolicy::wrapRow(i)][IndexWrapPolicy::wrapCol(j)];
	}

private:
	Grid(const Grid&);
	Grid& operator=(const Grid&);
	grid_t data_;
};

}

void vonNeumannLattice2D(Graph&g, node_size_t rows, node_size_t cols)
{
	g.clear();
	typedef detail::Grid<node_id_t, detail::NoWrapChecked> Grid;
	Grid grid(rows, cols);

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			grid(i, j) = g.addNode();

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
		{
			if (j > 0)
				g.addEdge(grid(i, j - 1), grid(i, j), false);
			if (j < cols - 1)
				g.addEdge(grid(i, j + 1), grid(i, j), false);
			if (i > 0)
				g.addEdge(grid(i - 1, j), grid(i, j), false);
			if (i < rows - 1)
				g.addEdge(grid(i + 1, j), grid(i, j), false);
		}
}

void vonNeumannLattice2DPeriodic(Graph& g, node_size_t rows, node_size_t cols)
{
	g.clear();
	typedef detail::Grid<node_id_t, detail::PeriodicWrap> PeriodicGrid;
	PeriodicGrid grid(rows, cols);

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

void mooreLattice2D(Graph& g, node_size_t rows, node_size_t cols)
{
	g.clear();
	typedef detail::Grid<node_id_t, detail::NoWrapChecked> Grid;
	Grid grid(rows, cols);

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			grid(i, j) = g.addNode();

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
		{
			if (j > 0)
				g.addEdge(grid(i, j - 1), grid(i, j), false);
			if (j < cols - 1)
				g.addEdge(grid(i, j + 1), grid(i, j), false);
			if (i > 0)
				g.addEdge(grid(i - 1, j), grid(i, j), false);
			if (i < rows - 1)
				g.addEdge(grid(i + 1, j), grid(i, j), false);
			if (j > 0 && i > 0)
				g.addEdge(grid(i - 1, j - 1), grid(i, j), false);
			if (i > 0 && j < cols - 1)
				g.addEdge(grid(i - 1, j + 1), grid(i, j), false);
			if (i < rows - 1 && j > 0)
				g.addEdge(grid(i + 1, j - 1), grid(i, j), false);
			if (i < rows - 1 && j < cols - 1)
				g.addEdge(grid(i + 1, j + 1), grid(i, j), false);
		}
}

void mooreLattice2DPeriodic(Graph& g, node_size_t rows, node_size_t cols)
{
	g.clear();
	typedef detail::Grid<node_id_t, detail::PeriodicWrap> PeriodicGrid;
	PeriodicGrid grid(rows, cols);
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

/**
 * @file measures.cpp
 * @date 12.01.2011
 * @author gerd
 */

#include "measures.h"
#include <boost/foreach.hpp>
#include <cmath>

namespace largenet
{
namespace measures
{

degree_t maxInDegree(const Graph& g)
{
	degree_t max = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		if (max < n.inDegree())
			max = n.inDegree();
	}
	return max;
}

degree_t minInDegree(const Graph& g)
{
	degree_t min = g.numberOfEdges();
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		if (min > n.inDegree())
			min = n.inDegree();
	}
	return min;
}

degree_range_t inDegreeRange(const Graph& g)
{
	degree_t min = g.numberOfEdges(), max = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		degree_t k = n.inDegree();
		if (min > k)
			min = k;
		if (max < k)
			max = k;
	}
	return std::make_pair(min, max);
}

degree_t maxOutDegree(const Graph& g)
{
	degree_t max = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		if (max < n.outDegree())
			max = n.outDegree();
	}
	return max;
}

degree_t minOutDegree(const Graph& g)
{
	degree_t min = g.numberOfEdges();
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		if (min > n.outDegree())
			min = n.outDegree();
	}
	return min;
}

degree_range_t outDegreeRange(const Graph& g)
{
	degree_t min = g.numberOfEdges(), max = 0;
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		degree_t k = n.outDegree();
		if (min > k)
			min = k;
		if (max < k)
			max = k;
	}
	return std::make_pair(min, max);
}

/// @cond IGNORE
double std_dev_in(const Graph& g)
{
	double s = 0;
	double mean = g.numberOfEdges() / g.numberOfNodes();
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		degree_t d = n.inDegree();
		s += (d - mean) * (d - mean);
	}
	return sqrt(s);
}

double std_dev_out(const Graph& g)
{
	double s = 0;
	double mean = g.numberOfEdges() / g.numberOfNodes();
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		degree_t d = n.outDegree();
		s += (d - mean) * (d - mean);
	}
	return sqrt(s);
}
/// @endcond

double inOutDegreeCorrelation(const Graph& g)
{
	double cov = 0;
	double mean = g.numberOfEdges() / g.numberOfNodes();
	BOOST_FOREACH(const Node& n, g.nodes())
	{
		degree_t din = n.inDegree(), dout = n.outDegree();
		cov += (din - mean) * (dout - mean);
	}
	return cov / std_dev_out(g) / std_dev_in(g);
}

NeighborDegreeCorrelations neighborDegreeCorrelations(const Graph& g)
{
	double s_in_mean = 0, s_out_mean = 0, t_in_mean = 0, t_out_mean = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		s_in_mean += e.source()->inDegree();
		s_out_mean += e.source()->outDegree();
		t_in_mean += e.target()->inDegree();
		t_out_mean += e.target()->outDegree();
	}
	s_in_mean /= g.numberOfEdges();
	s_out_mean /= g.numberOfEdges();
	t_in_mean /= g.numberOfEdges();
	t_out_mean /= g.numberOfEdges();

	double cov_ii = 0, cov_io = 0, cov_oi = 0, cov_oo = 0;
	double sd_s_in = 0, sd_s_out = 0, sd_t_in = 0, sd_t_out = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		degree_t s_in = e.source()->inDegree(), s_out = e.source()->outDegree(),
				 t_in = e.target()->inDegree(), t_out = e.target()->outDegree();
		cov_ii += (s_in - s_in_mean) * (t_in - t_in_mean);
		cov_io += (s_in - s_in_mean) * (t_out - t_out_mean);
		cov_oi += (s_out - s_out_mean) * (t_in - t_in_mean);
		cov_oo += (s_out - s_out_mean) * (t_out - t_out_mean);
		sd_s_in += (s_in - s_in_mean) * (s_in - s_in_mean);
		sd_s_out += (s_out - s_out_mean) * (s_out - s_out_mean);
		sd_t_in += (t_in - t_in_mean) * (t_in - t_in_mean);
		sd_t_out += (t_out - t_out_mean) * (t_out - t_out_mean);
	}
	double s_sd_s_in = sqrt(sd_s_in), s_sd_s_out = sqrt(sd_s_out),
		   s_sd_t_in = sqrt(sd_t_in), s_sd_t_out = sqrt(sd_t_out);
	NeighborDegreeCorrelations ret =
	{
			cov_ii / (s_sd_s_in * s_sd_t_in), // r_ii
			cov_io / (s_sd_s_in * s_sd_t_out), // r_io
			cov_oi / (s_sd_s_out * s_sd_t_in), // r_oi
			cov_oo / (s_sd_s_out * s_sd_t_out) // r_oo
	};
	return ret;
}

double neighborDegreeCorrelationInIn(const Graph& g)
{
	double s_in_mean = 0, t_in_mean = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		s_in_mean += e.source()->inDegree();
		t_in_mean += e.target()->inDegree();
	}
	s_in_mean /= g.numberOfEdges();
	t_in_mean /= g.numberOfEdges();

	double cov = 0;
	double sd_s_in = 0, sd_t_in = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		degree_t s_in = e.source()->inDegree(), t_in = e.target()->inDegree();
		cov += (s_in - s_in_mean) * (t_in - t_in_mean);
		sd_s_in += (s_in - s_in_mean) * (s_in - s_in_mean);
		sd_t_in += (t_in - t_in_mean) * (t_in - t_in_mean);
	}
	return cov / (sqrt(sd_s_in) * sqrt(sd_t_in));
}

double neighborDegreeCorrelationInOut(const Graph& g)
{
	double s_in_mean = 0, t_out_mean = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		s_in_mean += e.source()->inDegree();
		t_out_mean += e.target()->outDegree();
	}
	s_in_mean /= g.numberOfEdges();
	t_out_mean /= g.numberOfEdges();

	double cov = 0;
	double sd_s_in = 0, sd_t_out = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		degree_t s_in = e.source()->inDegree(), t_out = e.target()->outDegree();
		cov += (s_in - s_in_mean) * (t_out - t_out_mean);
		sd_s_in += (s_in - s_in_mean) * (s_in - s_in_mean);
		sd_t_out += (t_out - t_out_mean) * (t_out - t_out_mean);
	}
	return cov / (sqrt(sd_s_in) * sqrt(sd_t_out));
}

double neighborDegreeCorrelationOutOut(const Graph& g)
{
	double s_out_mean = 0, t_out_mean = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		s_out_mean += e.source()->outDegree();
		t_out_mean += e.target()->outDegree();
	}
	s_out_mean /= g.numberOfEdges();
	t_out_mean /= g.numberOfEdges();

	double cov = 0;
	double sd_s_out = 0, sd_t_out = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		degree_t s_out = e.source()->outDegree(), t_out = e.target()->outDegree();
		cov += (s_out - s_out_mean) * (t_out - t_out_mean);
		sd_s_out += (s_out - s_out_mean) * (s_out - s_out_mean);
		sd_t_out += (t_out - t_out_mean) * (t_out - t_out_mean);
	}
	return cov / (sqrt(sd_s_out) * sqrt(sd_t_out));
}

double neighborDegreeCorrelationOutIn(const Graph& g)
{
	double s_out_mean = 0, t_in_mean = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		s_out_mean += e.source()->outDegree();
		t_in_mean += e.target()->inDegree();
	}
	s_out_mean /= g.numberOfEdges();
	t_in_mean /= g.numberOfEdges();

	double cov = 0;
	double sd_s_out = 0, sd_t_in = 0;
	BOOST_FOREACH(const Edge& e, g.edges())
	{
		degree_t s_out = e.source()->outDegree(), t_in = e.target()->inDegree();
		cov += (s_out - s_out_mean) * (t_in - t_in_mean);
		sd_s_out += (s_out - s_out_mean) * (s_out- s_out_mean);
		sd_t_in += (t_in - t_in_mean) * (t_in - t_in_mean);
	}
	return cov / (sqrt(sd_s_out) * sqrt(sd_t_in));
}

}
}

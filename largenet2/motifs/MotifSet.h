/*
 * MotifSet.h
 *
 *  Created on: 03.02.2009
 *      Author: gerd
 */

#ifndef MOTIFSET_H_
#define MOTIFSET_H_

#include <largenet2/motifs/detail/motif_construction.h>

namespace largenet
{
namespace motifs {


template<class Motif>
class MotifSet
{
public:
	typedef	typename std::set<Motif>::const_iterator const_iterator;
	typedef typename std::set<Motif>::const_iterator iterator;
	MotifSet(node_state_size_t states, bool directed = true);
	unsigned int size() const;
	iterator begin() const;
	iterator end() const;
private:
	std::set<Motif> motifs_;
};

template<class Motif>
MotifSet<Motif>::MotifSet(const node_state_size_t states, bool directed)
{
	detail::constructAllMotifs(motifs_, states, directed);
}

template<class Motif>
inline typename MotifSet<Motif>::iterator MotifSet<Motif>::begin() const
{
	return motifs_.begin();
}

template<class Motif>
inline typename MotifSet<Motif>::iterator MotifSet<Motif>::end() const
{
	return motifs_.end();
}

template<class Motif>
inline unsigned int MotifSet<Motif>::size() const
{
	return motifs_.size();
}

}
}
#endif /* MOTIFSET_H_ */

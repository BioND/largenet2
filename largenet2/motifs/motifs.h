/*
 * motifs.h
 *
 *  Created on: 03.02.2009
 *      Author: gerd
 */

#ifndef MOTIFS_H_
#define MOTIFS_H_

#include <largenet2/motifs/NodeMotif.h>
#include <largenet2/motifs/LinkMotif.h>
#include <largenet2/motifs/TripleMotif.h>
#include <largenet2/motifs/QuadLineMotif.h>
#include <largenet2/motifs/QuadStarMotif.h>
#include <largenet2/motifs/MotifSet.h>

namespace largenet
{
namespace motifs
{
typedef MotifSet<NodeMotif> NodeMotifSet;
typedef MotifSet<LinkMotif> LinkMotifSet;
typedef MotifSet<TripleMotif> TripleMotifSet;
typedef MotifSet<QuadLineMotif> QuadLineMotifSet;
typedef MotifSet<QuadStarMotif> QuadStarMotifSet;
}
}

#endif /* MOTIFS_H_ */

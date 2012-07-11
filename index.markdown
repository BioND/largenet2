---
layout: index
title: About
---
# Largenet2 adaptive-network simulation library
The `largenet2` library is a collection of C++ classes providing a framework for the 
simulation of large discrete [adaptive networks][1]. It provides data structures
for an in-memory representation of _directed or undirected_ networks, in which every
node and link can have an integer-valued state.

Efficient access to (random) nodes and links as well as (random) nodes and links
with a given state value is provided. A limited number of graph-theoretical measures
is implemented, such as the (state-resolved) in- and out-degree distributions and the
degree correlations (same-node and nearest-neighbor).  

The `largenet2` library has been developed by [Gerd Zschaler](http://www.pks.mpg.de/~zschaler).

[1]: http://dx.doi.org/10.1098/rsif.2007.1229 "T. Gross and B. Blasius (2008), J. R. Soc. Interface, 5, 259"

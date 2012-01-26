# A C++ library for the efficient simulation of large dynamic network models
The `largenet2` library is a collection of C++ classes providing a framework for the 
simulation of large discrete [adaptive networks][1]. It provides data structures
for an in-memory representation of _directed or undirected_ networks, in which every
node and link can have an integer-valued state.

Efficient access to (random) nodes and links as well as (random) nodes and links
with a given state value is provided. A limited number of graph-theoretical measures
is implemented, such as the (state-resolved) in- and out-degree distributions and the
degree correlations (same-node and nearest-neighbor).  

The `largenet2` library has been developed by [Gerd Zschaler](http://www.pks.mpg.de/~zschaler).
It is a major rewrite of the original `largenet` library, which only supported undirected
networks.

Most of this work is licensed under the Creative Commons CC-BY-NC license. See COPYING
for details.

For installation instructions, see INSTALL. For examples how to use the library, see the 
`examples` directory.

The `largenet2` library has been used for simulations of [neural networks][2] and
adaptive network models of [opinion formation][3]. 

[1]: http://dx.doi.org/10.1098/rsif.2007.1229 "T. Gross and B. Blasius (2008), J. R. Soc. Interface, 5, 259"
[2]: http://www.biond.org/node/164 "F. Droste (2010), Diploma thesis, HU Berlin"
[3]: http://arxiv.org/abs/1110.1336 "G. Zschaler et al. (2011), submitted"

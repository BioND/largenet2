ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = largenet-@PACKAGE_VERSION@.pc

EXTRA_DIST = largenet-@PACKAGE_VERSION@.pc README.md Doxyfile

lib_LTLIBRARIES = liblargenet2-0.1.la
liblargenet2_0_1_la_LDFLAGS = -version-info 0:0:0

liblargenet2_0_1_la_SOURCES = \
		largenet2/measures/measures.cpp \
		largenet2/measures/InOutDegreeMatrix.cpp \
		largenet2/measures/counts.cpp \
		largenet2/io/EdgeListWriter.cpp \
		largenet2/io/EdgeListReader.cpp \
		largenet2/sim/output/IntervalOutput.cpp \
		largenet2/sim/output/Outputter.cpp \
		largenet2/motifs/QuadLineMotif.cpp \
		largenet2/motifs/TripleMotif.cpp \
		largenet2/motifs/detail/motif_construction.cpp \
		largenet2/motifs/LinkMotif.cpp \
		largenet2/motifs/NodeMotif.cpp \
		largenet2/motifs/QuadStarMotif.cpp \
		largenet2/base/Edge.cpp \
		largenet2/base/converters.cpp \
		largenet2/base/SingleNode.cpp \
		largenet2/base/Graph.cpp \
		largenet2/base/MultiNode.cpp


nobase_include_HEADERS = \
		largenet2.h \
		largenet2/generators/generators.h \
		largenet2/measures/DegreeDistribution.h \
		largenet2/measures/measures.h \
		largenet2/measures/counts.h \
		largenet2/measures/InOutDegreeMatrix.h \
		largenet2/util/choosetype.h \
		largenet2/io/GraphReader.h \
		largenet2/io/EdgeListReader.h \
		largenet2/io/GraphWriter.h \
		largenet2/io/EdgeListWriter.h \
		largenet2/sim/gillespie/MaxMethod.h \
		largenet2/sim/gillespie/DirectMethod.h \
		largenet2/sim/SimApp.h \
		largenet2/sim/output/IntervalOutput.h \
		largenet2/sim/output/DegDistOutput.h \
		largenet2/sim/output/TimeSeriesOutput.h \
		largenet2/sim/output/Outputter.h \
		largenet2/sim/SimOptions.h \
		largenet2/StateConsistencyListener.h \
		largenet2/motifs/QuadLineMotif.h \
		largenet2/motifs/TripleMotif.h \
		largenet2/motifs/LinkMotif.h \
		largenet2/motifs/NodeMotif.h \
		largenet2/motifs/detail/motif_construction.h \
		largenet2/motifs/motifs.h \
		largenet2/motifs/QuadStarMotif.h \
		largenet2/motifs/MotifSet.h \
		largenet2/base/Graph.h \
		largenet2/base/types.h \
		largenet2/base/factories.h \
		largenet2/base/exceptions.h \
		largenet2/base/MultiNode.h \
		largenet2/base/repo/CPtrRepository.h \
		largenet2/base/repo/repo_iterators.h \
		largenet2/base/repo/repo_types.h \
		largenet2/base/repo/repo_exceptions.h \
		largenet2/base/repo/CRepository.h \
		largenet2/base/ElementFactory.h \
		largenet2/base/SingleNode.h \
		largenet2/base/converters.h \
		largenet2/base/GraphListener.h \
		largenet2/base/Edge.h \
		largenet2/base/graph_iterators.h \
		largenet2/base/Node.h \
		largenet2/base/node_iterators.h
		

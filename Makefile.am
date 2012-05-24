ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = largenet2.pc

EXTRA_DIST = largenet2.pc README.md Doxyfile

lib_LTLIBRARIES = liblargenet2-@PACKAGE_VERSION@.la
liblargenet2_@PACKAGE_VERSION@_la_CPPFLAGS = $(BOOST_CPPFLAGS)
liblargenet2_@PACKAGE_VERSION@_la_LDFLAGS = -version-info 0:0:0

if HAVE_GRAPHML
GRAPHML_SRC = \
		largenet2/io/GraphMLWriter.cpp
GRAPHML_HPP = \
		largenet2/io/GraphMLWriter.h
else
GRAPHML_SRC = 
GRAPHML_HPP = 
endif

liblargenet2_@PACKAGE_VERSION@_la_SOURCES = \
		largenet2/measures/measures.cpp \
		largenet2/measures/InOutDegreeMatrix.cpp \
		largenet2/measures/counts.cpp \
		largenet2/io/EdgeListWriter.cpp \
		largenet2/io/EdgeListReader.cpp \
		largenet2/io/BinWriter.cpp \
		largenet2/io/BinReader.cpp \
		largenet2/io/DotWriter.cpp \
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
		largenet2/base/MultiNode.cpp \
		$(GRAPHML_SRC)

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
		largenet2/io/BinWriter.h \
		largenet2/io/BinReader.h \
		largenet2/io/DotWriter.h \
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
		largenet2/base/Node.h \
		largenet2/base/node_iterators.h \
		largenet2/boost/largenet2_boost.h \
		largenet2/boost/property_graph.h \
		$(GRAPHML_HPP)

check_PROGRAMS = \
		boost_test \
		io_test \
		base_tests

boost_test_SOURCES = tests/boost/largenet2_boost_test.cpp
io_test_SOURCES = tests/io/io_test.cpp
io_test_LDADD = liblargenet2-@PACKAGE_VERSION@.la

base_tests_SOURCES = \
	tests/base/base_tests.cpp \
	tests/base/repo/test_types.h \
	tests/base/repo/CPtrRepository_test.cpp \
	tests/base/Edge_test.cpp \
	tests/base/graph_iterators_test.cpp
	
base_tests_LDADD = liblargenet2-@PACKAGE_VERSION@.la
base_tests_CPPFLAGS = -DBOOST_TEST_DYN_LINK $(BOOST_CPPFLAGS)
base_tests_LDFLAGS = $(BOOST_LDFLAGS) -lboost_unit_test_framework

TESTS = \
		base_tests \
		boost_test \
		io_test

if HAVE_DOXYGEN

DOCDIR = doc
MOSTLYCLEANFILES = -r $(DOCDIR)
	
doxygen-doc: $(DOCDIR)/doxygen.stamp 

$(DOCDIR)/doxygen.stamp: Doxyfile
	$(DOXYGEN) $(DOXYFLAGS) $<
	echo Timestamp > $@

endif

if BUILD_EXAMPLES

noinst_PROGRAMS = votermodel
votermodel_LDADD = liblargenet2-@PACKAGE_VERSION@.la
votermodel_CPPFLAGS = $(BOOST_CPPFLAGS) 
votermodel_SOURCES = \
		examples/votermodel/vm.cpp \
		examples/votermodel/VoterModel.h \
		examples/votermodel/RandomVariates.h \
		examples/votermodel/util.h \
		examples/votermodel/WELLEngine.h \
		examples/votermodel/WELLEngine.cpp 
		
endif
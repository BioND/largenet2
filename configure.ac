AC_PREREQ([2.61])
AC_INIT([largenet2], [0.3])
AC_CANONICAL_SYSTEM
AM_PROG_AR
AM_INIT_AUTOMAKE([1.11 -Wall -Werror foreign silent-rules subdir-objects])
LT_PREREQ([2.2])
LT_INIT([disable-static])

AC_CONFIG_MACRO_DIR([m4])

AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_TRY_DOXYGEN
BOOST_REQUIRE([1.36.0])
BOOST_FOREACH
BOOST_FUNCTION
BOOST_TEST
#BOOST_GRAPH

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([floor pow sqrt])

# Sanity check
AC_CONFIG_SRCDIR([largenet2/base/Graph.h])

# provide --enable-examples option
AC_ARG_ENABLE([examples],
		      [AS_HELP_STRING([--enable-examples],
			  				  [build examples (default: no)])],
     		  [case "${enableval}" in
				yes) examples=true ;;
				no)  examples=false ;;
				*) AC_MSG_ERROR([bad value ${enableval} for --enable-examples]) ;;
     		   esac],
     		   [examples=false])
AM_CONDITIONAL([BUILD_EXAMPLES], [test x$examples = xtrue])

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])

# configure --enable-boost [=no]
AC_ARG_ENABLE([boost_graph],
  [AS_HELP_STRING([--enable-boost_graph], [Enable Boost Graph bindings (default=no)])],
  [boost_graph="$withval"],
  [boost_graph=no])

AM_CONDITIONAL([USE_BOOST_GRAPH], [test "x$boost_graph" = "xyes"])

# configure option --enable-debug [=no]
AC_ARG_ENABLE([debug],
			   [AS_HELP_STRING([--enable-debug], [Enable debug mode (default=no)])],
			   [debug="$withval"],
			   [debug=no])


AM_CONDITIONAL([DEBUGMODE], [test "x$debug" = "xyes"])

AM_CONDITIONAL([HAVE_GRAPHML], [test "x$BOOST_VERSION" \> "x1.48.0"])

# Output files
AC_CONFIG_FILES([Makefile
                largenet2.pc
                Doxyfile])

AC_CONFIG_HEADERS([config.h])

AC_OUTPUT

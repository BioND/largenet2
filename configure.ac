AC_PREREQ([2.67])
AC_INIT([largenet2], [0.1])
AM_INIT_AUTOMAKE([1.11 -Wall -Werror foreign silent-rules subdir-objects])
LT_PREREQ([2.2])
LT_INIT([disable-static])

AC_CONFIG_MACRO_DIR([m4])

AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_INSTALL

# Checks for header files
# boost etc
#AC_CHECK_HEADERS_ONCE([boost/foreach.hpp
#					   boost/ptr_container/ptr_vector.hpp
#					   boost/noncopyable.hpp
#					   boost/call_traits.hpp
#					   boost/unordered_set.hpp])

AX_BOOST_BASE([1.36.0])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([floor pow sqrt])

# Sanity check
AC_CONFIG_SRCDIR([largenet2/base/Graph.h])

# provide --enable-examples option
#AC_ARG_ENABLE([examples],
#		      [AS_HELP_STRING([--enable-examples],
#			  				  [build examples (default: no)])],
#     		  [case "${enableval}" in
#				yes) examples=true ;;
#				no)  examples=false ;;
#				*) AC_MSG_ERROR([bad value ${enableval} for --enable-examples]) ;;
#     		   esac],
#     		   [examples=false])
#AM_CONDITIONAL([BUILD_EXAMPLES], [test x$examples = xtrue])

# Output files
AC_CONFIG_FILES([Makefile]
                [largenet2-0.1.pc:largenet2.pc.in])

AC_CONFIG_HEADERS([config.h])

AC_OUTPUT
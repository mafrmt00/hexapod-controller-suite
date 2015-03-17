AC_INIT([Hexa_Backend], [1.0], [bug-automake@gnu.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
# Turn off shared libraries during beta-testing, since they
# make the build process take too long.
AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AM_PROG_LIBTOOL
AC_PROG_LIBTOOL
BOOST_REQUIRE
BOOST_SERIALIZATION([sd])
AC_CONFIG_FILES([
 Makefile
 Hexa_Backend/Makefile
])
AC_OUTPUT
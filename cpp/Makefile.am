lib_LTLIBRARIES = lib@PACKAGE_NAME@.la
lib@PACKAGE_NAME@_la_CXXFLAGS = -Wall -I$(top_srcdir)/inc $(PROJECTDEPS_CFLAGS) $(BOOST_CPPFLAGS)
lib@PACKAGE_NAME@_la_LDFLAGS = $(PROJECTDEPS_LDFLAGS) $(BOOST_LDFLAGS) $(BOOST_THREAD_LIB) $(BOOST_SYSTEM_LIB)

libdir = $(spkg_lib_dir)
fftlib_src = \
src/Autocorrelate.cpp \
src/fft.cpp \
src/firfilter.cpp
lib@PACKAGE_NAME@_la_SOURCES = $(fftlib_src)

incdir = $(spkg_include_dir)
fftlib_inc = \
inc/Autocorrelate.h \
inc/fftw_allocator.h \
inc/fft.h \
inc/firfilter.h
dist_inc_DATA = $(fftlib_inc)

xmldir = $(spkg_dir)
dist_xml_DATA = ../@PACKAGE_NAME@.spd.xml

pkgconfigdir = $(spkg_pkgconfig_dir)
dist_pkgconfig_DATA = @PACKAGE_NAME@.pc

distclean-local:
	rm -f config.*
	rm -rf autom4te.cache
	rm -f acinclude.m4
	rm -f aclocal.m4
	rm -f configure
	rm -f depcomp
	rm -f install-sh
	rm -f ltmain.sh
	rm -f Makefile
	rm -f Makefile.in
	rm -f missing
	rm -rf .deps
	rm -rf .libs
	rm -f *.o
	rm -f *.lo
	rm -f fftlib.pc
	rm -f libfftlib.la
	rm -f libtool


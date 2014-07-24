#
# This file is protected by Copyright. Please refer to the COPYRIGHT file distributed with this 
# source distribution.
# 
# This file is part of REDHAWK Basic Components fftlib library.
# 
# REDHAWK Basic Components fcalc is free software: you can redistribute it and/or modify it under the terms of 
# the GNU Lesser General Public License as published by the Free Software Foundation, either 
# version 3 of the License, or (at your option) any later version.
# 
# REDHAWK Basic Components fcalc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
# PURPOSE.  See the GNU Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License along with this 
# program.  If not, see http://www.gnu.org/licenses/.
#
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


# This file is protected by Copyright. Please refer to the COPYRIGHT file 
# distributed with this source distribution.
#
# This file is part of REDHAWK Basic Components rh.fftlib library.
#
# REDHAWK Basic Components rh.fftlib library is free software: you can redistribute
# it and/or modify it under the terms of the GNU General Public License as 
# published by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# REDHAWK Basic Components rh.fftlib library is distributed in the hope that it 
# will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this 
# program.  If not, see http://www.gnu.org/licenses/.
#
AC_INIT(rh.fftlib, 2.0.0)
AM_INIT_AUTOMAKE(nostdinc)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
LT_INIT([disable-static])

AC_CORBA_ORB
OSSIE_CHECK_OSSIE
RH_SOFTPKG_PREFIX([rh.fftlib],[cpp])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Dependencies
PKG_CHECK_MODULES([REDHAWK], [ossie >= 2.0])
PKG_CHECK_MODULES([PROJECTDEPS],   [fftw3 >= 3.0 fftw3f >= 3.0])
RH_SOFTPKG_CXX([/deps/rh/dsp/dsp.spd.xml],[cpp],[2.0])
OSSIE_ENABLE_LOG4CXX
AX_BOOST_BASE([1.41])
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_REGEX

AC_CONFIG_FILES([Makefile rh.fftlib.pc])
AC_OUTPUT

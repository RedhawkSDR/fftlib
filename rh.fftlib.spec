#
# This file is protected by Copyright. Please refer to the COPYRIGHT file distributed with this
# source distribution.
#
# This file is part of REDHAWK Basic Components rh.fftlib shared library.
#
# REDHAWK Basic Components rh.fftlib shared library is free software: you can redistribute it and/or modify it under the terms of
# the GNU General Public License as published by the Free Software Foundation, either
# version 3 of the License, or (at your option) any later version.
#
# REDHAWK Basic Components rh.fftlib shared library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this
# program.  If not, see http://www.gnu.org/licenses/.
#
# By default, the RPM will install to the standard REDHAWK SDR root location (/var/redhawk/sdr)
%{!?_sdrroot: %define _sdrroot /var/redhawk/sdr}
%define _prefix %{_sdrroot}/dom/deps/rh/fftlib

# Point install paths to locations within our target SDR root
%define _libdir        %{_prefix}/cpp/lib
%define _sysconfdir    %{_prefix}/etc
%define _localstatedir %{_prefix}/var
%define _mandir        %{_prefix}/man
%define _infodir       %{_prefix}/info

Name:           rh.fftlib
Version:        2.1.0
Release:        2%{?dist}
Summary:        REDHAWK shared library %{name}

Group:          REDHAWK/Shared Libraries
License:        GPLv3+
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  redhawk-devel >= 2.0
BuildRequires:  fftw-devel >= 3
BuildRequires:  autoconf automake libtool

BuildRequires:  rh.dsp-devel >= 2.0
Requires:       rh.dsp >= 2.0

Obsoletes:      fftlib < 2.0.0

%description
REDHAWK shared library %{name}
 * Commit: __REVISION__
 * Source Date/Time: __DATETIME__

%package devel
Summary:        REDHAWK shared library %{name}
Group:          REDHAWK/Shared Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       fftw-devel >= 3
Requires:       rh.dsp-devel >= 2.0
Obsoletes:      fftlib-devel < 2.0.0

%description devel
Libraries and header files for REDHAWK shared library %{name}

%prep
%setup -q


%build
# Implementation cpp
pushd cpp
./reconf
%configure --with-sdr=%{_sdrroot}
make %{?_smp_mflags}
popd


%install
rm -rf $RPM_BUILD_ROOT
# Implementation cpp
pushd cpp
make install DESTDIR=$RPM_BUILD_ROOT
popd


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,redhawk,redhawk,-)
%dir %{_sdrroot}/dom/deps/rh
%dir %{_sdrroot}/dom/deps/rh/fftlib
%{_prefix}/fftlib.spd.xml
%{_prefix}/cpp
%exclude %{_libdir}/libfftlib.la
%exclude %{_libdir}/libfftlib.so
%exclude %{_libdir}/pkgconfig

%files devel
%defattr(-,redhawk,redhawk,-)
%{_libdir}/libfftlib.la
%{_libdir}/libfftlib.so
%{_libdir}/pkgconfig
%{_prefix}/include

%changelog
* Wed Jun 21 2017 Ryan Bauman - 2.0.1-1
- Update version post release
* Wed Jun 21 2017 Ryan Bauman - 2.0.0-2
- Mass rebuild for REDHAWK 2.1.1


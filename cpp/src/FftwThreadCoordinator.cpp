/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file distributed with this
 * source distribution.
 *
 * This file is part of REDHAWK Basic Components fftlib library.
 *
 * REDHAWK Basic Components fftlib library is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * REDHAWK Basic Components fftlib library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this
 * program.  If not, see http://www.gnu.org/licenses/.
 */

#include "FftwThreadCoordinator.h"

namespace {
    static boost::once_flag fftw_coordinator_init  = BOOST_ONCE_INIT;
    static boost::once_flag fftwf_coordinator_init = BOOST_ONCE_INIT;
    static boost::scoped_ptr<FftwThreadCoordinator>  fftw_coordinator_inst(0);
    static boost::scoped_ptr<FftwfThreadCoordinator> fftwf_coordinator_inst(0);
} // end anon namespace

FftwThreadCoordinator* getFftwCoordinator () {
    boost::call_once(fftw_coordinator_init, &FftwThreadCoordinator::_create_instance);
    return fftw_coordinator_inst.get();
}
FftwfThreadCoordinator* getFftwfCoordinator () {
    boost::call_once(fftwf_coordinator_init, &FftwfThreadCoordinator::_create_instance);
    return fftwf_coordinator_inst.get();
}

// FftwThreadCoordinator implementation
void FftwThreadCoordinator::_create_instance () {
    fftw_coordinator_inst.reset(new FftwThreadCoordinator());
}
FftwThreadCoordinator::FftwThreadCoordinator () {
    boost::mutex::scoped_lock lock(plan_mutex);
    ::fftw_cleanup();
}
FftwThreadCoordinator::~FftwThreadCoordinator () {
    boost::mutex::scoped_lock lock(plan_mutex);
    ::fftw_cleanup();
}
boost::mutex& FftwThreadCoordinator::getPlanMutex () {
    return plan_mutex;
}

// FftwfThreadCoordinator implementation
void FftwfThreadCoordinator::_create_instance () {
    fftwf_coordinator_inst.reset(new FftwfThreadCoordinator());
}
FftwfThreadCoordinator::FftwfThreadCoordinator () {
    boost::mutex::scoped_lock lock(plan_mutex);
    ::fftwf_cleanup();
}
FftwfThreadCoordinator::~FftwfThreadCoordinator () {
    boost::mutex::scoped_lock lock(plan_mutex);
    ::fftwf_cleanup();
}
boost::mutex& FftwfThreadCoordinator::getPlanMutex () {
    return plan_mutex;
}


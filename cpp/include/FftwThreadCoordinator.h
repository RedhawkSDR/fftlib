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

#ifndef FFTW_THREAD_COORDINATOR_H_
#define FFTW_THREAD_COORDINATOR_H_

#include "fftw3.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>

/** Prevent thread safety issues with fftw
 *  Use fftw_thread_coordinator::getCoordinator() for fftw
 *  Use fftwf_thread_coordinator::getCoordinator() for fftwf
 *  Lock the boost::mutex provided by coord->getPlanMutex() prior to calling fftw plan methods
 */

namespace fftw_thread_coordinator {
    class FftwThreadCoordinator;
    FftwThreadCoordinator* getCoordinator ();

    // FftwThreadCoordinator definition
    class FftwThreadCoordinator {
        friend FftwThreadCoordinator* getCoordinator();
    public:
        ~FftwThreadCoordinator ();
        boost::mutex& getPlanMutex ();
    private:
        static void _create_instance ();
        FftwThreadCoordinator ();
        boost::mutex plan_mutex;
    }; // end FftwThreadCoordinator class
} // end fftw_thread_coordinator namespace

namespace fftwf_thread_coordinator {
    class FftwfThreadCoordinator;
    FftwfThreadCoordinator* getCoordinator ();

    // FftwfThreadCoordinator definition
    class FftwfThreadCoordinator {
        friend FftwfThreadCoordinator* getCoordinator();
    public:
        ~FftwfThreadCoordinator ();
        boost::mutex& getPlanMutex ();
    private:
        static void _create_instance ();
        FftwfThreadCoordinator ();
        boost::mutex plan_mutex;
    }; // end FftwfThreadCoordinator class
} // end fftwf_thread_coordinator namespace

#endif /* FFTW_THREAD_COORDINATOR_H_ */

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


class FftwThreadCoordinator {
public:
	FftwThreadCoordinator () {
		_fftw_cleanup();
	}
	~FftwThreadCoordinator () {
		_fftw_cleanup();
	}
	boost::mutex& getPlanMutex() {
		return plan_mutex;
	}
private:
	void _fftw_cleanup() {
		boost::mutex::scoped_lock lock(plan_mutex);
		::fftw_cleanup();
	}
	boost::mutex plan_mutex;
};

class FftwfThreadCoordinator {
public:
	FftwfThreadCoordinator () {
		_fftwf_cleanup();
	}
	~FftwfThreadCoordinator () {
		_fftwf_cleanup();
	}
	boost::mutex& getPlanMutex() {
		return plan_mutex;
	}
private:
	void _fftwf_cleanup() {
		boost::mutex::scoped_lock lock(plan_mutex);
		::fftwf_cleanup();
	}
	boost::mutex plan_mutex;
};


namespace fftwf_thread_coordinator {
	namespace {
		static boost::once_flag coordinatorInit = BOOST_ONCE_INIT;
		static boost::scoped_ptr<FftwfThreadCoordinator> coordinatorInstance(0);
		static void initializeCoordinator() {
			FftwfThreadCoordinator* coord = new FftwfThreadCoordinator();
			coordinatorInstance.reset(coord);
		}
		FftwfThreadCoordinator* getCoordinator() {
			boost::call_once(coordinatorInit, &initializeCoordinator);
			return coordinatorInstance.get();
		}
    }
}

namespace fftw_thread_coordinator {
    namespace {
		static boost::once_flag coordinatorInit = BOOST_ONCE_INIT;
		static boost::scoped_ptr<FftwThreadCoordinator> coordinatorInstance(0);
		static void initializeCoordinator() {
			FftwThreadCoordinator* coord = new FftwThreadCoordinator();
			coordinatorInstance.reset(coord);
		}
		FftwThreadCoordinator* getCoordinator() {
			boost::call_once(coordinatorInit, &initializeCoordinator);
			return coordinatorInstance.get();
		}
    }
}

#endif /* FFTW_THREAD_COORDINATOR_H_ */

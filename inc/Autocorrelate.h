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

#ifndef AUTOCORRELATE_H_
#define AUTOCORRELATE_H_

#include "fft.h"
#include "framebuffer.h"
#include "vectormean.h"
#include "DataTypes.h"

class Autocorrelator
{
public:

	enum OUTPUT_TYPE {STANDARD, ROTATED, SUPERIMPOSED};

	Autocorrelator(RealVector& realOutput, size_t correlationSize, long overlap, size_t numAverages, OUTPUT_TYPE outType, bool zeroMean=true, bool zeroCenter=false) :
		correlationSize_(correlationSize),
		fftSize_(getFftSize()),
		outputType_(outType),
		zeroMean_(zeroMean),
		zeroCenter_(zeroCenter),
		realOutput_(realOutput),
		realInputFft_(framedTimeDomain_, fftData_, fftSize_, false),
		realOutputFft_(autocorrelationOutput_, fftData_, fftSize_, false),
		realFramer_(correlationSize, overlap),
		vecMean_(numAverages, autocorrelationRotated_, autocorrelationAverage_)
	{
		std::cout << "using correlationSize of " << correlationSize << " fftSize of " << fftSize_ << std::endl;
		//framedTimeDomain_.resize(fftSize_,0.0);
	}

	void run(RealVector& realInput);
	void flush();
	void setCorrelationSize(size_t size);
	void setOverlap(long overlap);
	void setNumAverages(size_t numAverages);
	void setOutputType(OUTPUT_TYPE outType);
	void setZeroMean(bool zeroMean);
	void setZeroCenter(bool zeroCenter);

private:
	template<typename T>
	void appendOutput(T& inVec);
	size_t getFftSize();

	size_t correlationSize_;
	size_t fftSize_;
	OUTPUT_TYPE outputType_;
	bool zeroMean_;
	bool zeroCenter_;

	RealVector& realOutput_;
	RealFFTWVector framedTimeDomain_;
	ComplexFFTWVector fftData_;
	RealFFTWVector autocorrelationOutput_;
	RealVector autocorrelationRotated_;
	RealVector autocorrelationAverage_;
	std::vector<framebuffer<RealVector::iterator>::frame> realFrames_;

	//foward fft
	RealFwdFft realInputFft_;
	RealRevFft realOutputFft_;
	framebuffer<RealVector::iterator> realFramer_;
	VectorExponentialAvg<float> vecMean_;

};

#endif /* AUTOCORRELATE_H_ */

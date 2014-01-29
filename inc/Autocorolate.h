/*
 * autocorolate.h
 *
 *  Created on: Jan 29, 2014
 *      Author: bsg
 */

#ifndef AUTOCOROLATE_H_
#define AUTOCOROLATE_H_

#include "fft.h"
#include "framebuffer.h"
#include "vectormean.h"
#include "DataTypes.h"

class Autocorolator
{
public:

	enum OUTPUT_TYPE {STANDARD, ROTATED, SUPERIMPOSED};

	Autocorolator(RealVector& realOutput, size_t corelationSize, long overlap, size_t numAverages, OUTPUT_TYPE outType, bool zeroMean=true, bool zeroCenter=false) :
		corelationSize_(corelationSize),
		fftSize_(getFftSize()),
		outputType_(outType),
		zeroMean_(zeroMean),
		zeroCenter_(zeroCenter),
		realOutput_(realOutput),
		realInputFft_(framedTimeDomain_, fftData_, fftSize_,false),
		realOutputFft_(autocorolationOutput_, fftData_, fftSize_,false),
		realFramer_(corelationSize, overlap),
		vecMean_(numAverages, autocorolationRotated_, autocorolationAverage_)
	{
		std::cout<<"using corelationSize of " <<corelationSize<< " fftSize of "<<fftSize_<<std::endl;
		//framedTimeDomain_.resize(fftSize_,0.0);
	}

	void run(RealVector& realInput);
	void setCorelationSize(size_t size);
	void setOverlap(long overlap);
	void setNumAverages(size_t numAverages);
	void setOutputType(OUTPUT_TYPE outType);
	void setZeroMean(bool zeroMean);
	void setZeroCenter(bool zeroCenter);

private:
	template<typename T>
	void appendOutput(T& inVec);
	size_t getFftSize();

	size_t corelationSize_;
	size_t fftSize_;
	OUTPUT_TYPE outputType_;
	bool zeroMean_;
	bool zeroCenter_;

	RealVector& realOutput_;
	RealFFTWVector framedTimeDomain_;
	ComplexFFTWVector fftData_;
	RealFFTWVector autocorolationOutput_;
	RealVector autocorolationRotated_;
	RealVector autocorolationAverage_;
	std::vector<framebuffer<RealVector::iterator>::frame> realFrames_;

    //foward fft
	RealFwdFft realInputFft_;
	RealRevFft realOutputFft_;
	framebuffer<RealVector::iterator> realFramer_;
	VectorExponentialAvg<float> vecMean_;

};

#endif /* AUTOCOROLATE_H_ */

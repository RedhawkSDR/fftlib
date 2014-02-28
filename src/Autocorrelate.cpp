/*
 * Autocorrelate.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: bsg
 */
#include "Autocorrelate.h"
#include "zeromean.h"

void Autocorrelator::run(RealVector& realInput)
{
	realOutput_.clear();
	realFramer_.newData(realInput,realFrames_);
	size_t maxOutputFrames;
	if (realFrames_.size()> vecMean_.getAvgNum())
		maxOutputFrames =(realFrames_.size() - vecMean_.getAvgNum() -1)/vecMean_.getAvgNum()+1;
	else
		maxOutputFrames=1;
	size_t outFrameSize =2*correlationSize_-1;
	if (outputType_==SUPERIMPOSED)
		outFrameSize=correlationSize_;
	realOutput_.reserve(maxOutputFrames*outFrameSize);
	autocorrelationRotated_.resize(outFrameSize);

	//scale the gain by 1 over the fftSize since the fftw introduces the gain
	float scale = 1.0/fftSize_;
	for (std::vector<framebuffer<RealVector::iterator>::frame>::iterator frame = realFrames_.begin(); frame !=realFrames_.end(); frame++)
	{
		// Taking zero meam in time domain to avoid spectral leakage issues
		// Where large d.c. values blead in and effect bins close to d.c
		if (zeroMean_)
		{
			framedTimeDomain_.resize(std::distance(frame->begin, frame->end));
			zeroMean(frame->begin, frame->end, framedTimeDomain_.begin());
		}
		else
			framedTimeDomain_.assign(frame->begin, frame->end);
		// take the fft
		realInputFft_.run();
		// take the norm of the fft output
		for (ComplexFFTWVector::iterator i= fftData_.begin(); i != fftData_.end(); i++)
			*i= std::norm(*i);
		// take the ifft
		realOutputFft_.run();

		// set up our output

		// The algorithm introduces a phase shift which rotates the output data compared to the standard correlation output type.
		// If the fftSize > 2*correlationSize-1 we introduce zeros at the center of the inverse fft output.
		// Specifically, the first "correlationSize_" points and the last "correlationSize_-1" points are valid
		// and the rest of the points (in the middle) are the zero-padded data.
		// This is "opposite" how we want the data for standard but in the correct orientation for SUPERIMPOSED or ROTATED output types.
		// We solve this problem by doing two different loops to arrange the data.
		// The output iterators change position depending on which output mode we are in,
		// but we always do the first part of the inverse ifft data first and the 2nd part of the ifft data second

		RealVector::iterator out;
		if (outputType_==Autocorrelator::ROTATED || outputType_== Autocorrelator::SUPERIMPOSED)
			out=autocorrelationRotated_.begin();
		else
			out=autocorrelationRotated_.begin()+correlationSize_-1;

		size_t startIndex=0;
		//if zeroCenter has been requested - then grant the request here and upadte the iterators to start on the 2nd element
		if (zeroCenter_)
		{
			startIndex=1;
			*out=0;
			out++;
		}
		//copy & scale the data
		for(RealFFTWVector::iterator in = autocorrelationOutput_.begin()+startIndex; in != autocorrelationOutput_.begin()+correlationSize_; in++, out++)
		{
			*out = (*in)*scale;
		}
		// adjust the startIndex to grab the last correlationSize_-1 points from the inverse fft data in the 2nd loop
		// the "center" spike is not included since it was included in the first loop
		startIndex=fftSize_-(correlationSize_-1);
		//now do the other section.  We do different things depending on which mode we are in
		if (outputType_==Autocorrelator::ROTATED || outputType_ == Autocorrelator::STANDARD)
		{
			//if we are in standard mode we must reset the output iterator to the right place
			if (outputType_==Autocorrelator::STANDARD)
				out = autocorrelationRotated_.begin();
			for(RealFFTWVector::iterator in = autocorrelationOutput_.begin()+startIndex; in != autocorrelationOutput_.end(); in++, out++)
			{
				*out = (*in)*scale;
			}
		}
		else //SUPERIMPOSED
		{
			//use a reverse output iterator for the output so that the data is done in the opposite direction
			RealVector::reverse_iterator rout = autocorrelationRotated_.rbegin();
			//do the loop but add the data to that which we previously copied for the SUPERIMPOSED output
			for(RealFFTWVector::iterator in = autocorrelationOutput_.begin()+startIndex; in != autocorrelationOutput_.end(); in++, rout++)
			{
				*rout += (*in)*scale;
			}
		}

		//do averaging if required
		if (vecMean_.getAvgNum() >1)
		{
			if (vecMean_.run())
			{
				appendOutput(autocorrelationAverage_);
			}
		}
		else
		{
			appendOutput(autocorrelationRotated_);
		}
	}
}

void Autocorrelator::setCorrelationSize(size_t size)
{
	if (size !=correlationSize_)
	{
		correlationSize_ = size;
		fftSize_ = getFftSize();
		realInputFft_.setLength(fftSize_);
		realOutputFft_.setLength(fftSize_);
		realFramer_.setFrameSize(correlationSize_);
	}
}

void Autocorrelator::setOverlap(long overlap)
{
	if (overlap !=realFramer_.getOverlap())
	{
		realFramer_.setOverlap(overlap);
	}
}

void Autocorrelator::setNumAverages(size_t numAverages)
{
	vecMean_.setAvgNum(numAverages);
}

void Autocorrelator::setOutputType(OUTPUT_TYPE outType)
{
	if (outType != outputType_)
	{
		outputType_ = outType;
		vecMean_.clear();
	}
}

void Autocorrelator::setZeroMean(bool zeroMean)
{
	if (zeroMean_ != zeroMean)
	{
		zeroMean_ = zeroMean;
		vecMean_.clear();
	}
}


void Autocorrelator::setZeroCenter(bool zeroCenter)
{
	if (zeroCenter_ != zeroCenter)
	{
		zeroCenter_ = zeroCenter;
		vecMean_.clear();
	}
}

template<typename T>
void Autocorrelator::appendOutput(T& inVec)
{
	for (typename T::iterator i = inVec.begin(); i!=inVec.end(); i++)
	{
		realOutput_.push_back(*i);
	}
}

size_t Autocorrelator::getFftSize()
{
	size_t out=2;
	size_t minFftSize = 2*correlationSize_-1;
	while (minFftSize>=out)
		out*=2;
	return out;
}



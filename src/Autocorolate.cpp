/*
 * Autocorolate.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: bsg
 */
#include "Autocorolate.h"
#include "zeromean.h"

void Autocorolator::run(RealVector& realInput)
{
	realOutput_.clear();
	realFramer_.newData(realInput,realFrames_);
	size_t maxOutputFrames;
	if (realFrames_.size()> vecMean_.getAvgNum())
		maxOutputFrames =(realFrames_.size() - vecMean_.getAvgNum() -1)/vecMean_.getAvgNum()+1;
	else
		maxOutputFrames=1;
	size_t outFrameSize =2*corelationSize_-1;
	if (outputType_==SUPERIMPOSED)
		outFrameSize=corelationSize_;
	realOutput_.reserve(maxOutputFrames*outFrameSize);
	autocorolationRotated_.resize(outFrameSize);

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
		//take the fft
		realInputFft_.run();
		//take the absolute value of the fft output
		for (ComplexFFTWVector::iterator i= fftData_.begin(); i != fftData_.end(); i++)
			*i= std::norm(*i);
		//take the ifft
		realOutputFft_.run();

		//set up our output
		//if we are rotating it means the user wants to display the autocorolation in the
		//non-standard way
		//where the 0 offset bin chorosponds to 0 instead of the center

		//do first section of output data
		RealVector::iterator out;
//		if (rotate_)
//			out=autocorolationRotated_.end()-corelationSize_+1;
//		else
//			out=autocorolationRotated_.begin();
//		std::cout<<"outputType_ = "<<outputType_<<std::endl;
//		std::cout<<"Autocorolator::SUPERIMPOSED = "<<Autocorolator::SUPERIMPOSED<<std::endl;
		if (outputType_==Autocorolator::ROTATED || outputType_==Autocorolator::STANDARD)
		{
			if (outputType_==ROTATED)
				out=autocorolationRotated_.end()-corelationSize_+1;
			else
				out=autocorolationRotated_.begin();

			for(RealFFTWVector::iterator in = autocorolationOutput_.end()-corelationSize_+1; in != autocorolationOutput_.end(); in++, out++)
			{
				*out = (*in)*scale;
			}
			if (outputType_==Autocorolator::ROTATED)
				out = autocorolationRotated_.begin();
			size_t startIndex=0;
			if (zeroCenter_)
			{
				startIndex=1;
				*out=0;
				out++;
			}
			for(RealFFTWVector::iterator in = autocorolationOutput_.begin()+startIndex; in != autocorolationOutput_.begin()+corelationSize_; in++, out++)
			{
				*out = (*in)*scale;
			}

		}
		else
		{
			out =autocorolationRotated_.end()-1;
			for(RealFFTWVector::iterator in = autocorolationOutput_.end()-corelationSize_+1; in != autocorolationOutput_.end(); in++, out--)
			{
				*out = (*in)*scale;
			}
			if (zeroCenter_)
			{
				autocorolationRotated_[0]=0;
			}
			else
				autocorolationRotated_[0]=autocorolationOutput_[0];
			out = autocorolationRotated_.begin()+1;
			for(RealFFTWVector::iterator in = autocorolationOutput_.begin()+1; in != autocorolationOutput_.begin()+corelationSize_; in++, out++)
			{
				*out += (*in)*scale;
			}
		}

		//do averaging if required
		if (vecMean_.getAvgNum() >1)
		{
			if (vecMean_.run())
			{
				appendOutput(autocorolationAverage_);
			}
		}
		else
		{
			appendOutput(autocorolationRotated_);
		}
	}
}

void Autocorolator::setCorelationSize(size_t size)
{
	if (size !=corelationSize_)
	{
		corelationSize_ = size;
		fftSize_ = getFftSize();
		realInputFft_.setLength(fftSize_);
		realOutputFft_.setLength(fftSize_);
		realFramer_.setFrameSize(corelationSize_);
	}
}

void Autocorolator::setOverlap(long overlap)
{
	if (overlap !=realFramer_.getOverlap())
	{
		realFramer_.setOverlap(overlap);
	}
}

void Autocorolator::setNumAverages(size_t numAverages)
{
	vecMean_.setAvgNum(numAverages);
}

void Autocorolator::setOutputType(OUTPUT_TYPE outType)
{
	if (outType != outputType_)
	{
		outputType_ = outType;
		vecMean_.clear();
	}
}

void Autocorolator::setZeroMean(bool zeroMean)
{
	if (zeroMean_ != zeroMean)
	{
		zeroMean_ = zeroMean;
		vecMean_.clear();
	}
}


void Autocorolator::setZeroCenter(bool zeroCenter)
{
	if (zeroCenter_ != zeroCenter)
	{
		zeroCenter_ = zeroCenter;
		vecMean_.clear();
	}
}

template<typename T>
void Autocorolator::appendOutput(T& inVec)
{
	for (typename T::iterator i = inVec.begin(); i!=inVec.end(); i++)
	//for (typename T::iterator i = inVec.begin(); i!=inVec.begin()+2*corelationSize_-1; i++)
	{
		realOutput_.push_back(*i);
	}
}

size_t Autocorolator::getFftSize()
{
	size_t out=2;
	size_t minFftSize = 2*corelationSize_-1;
	while (minFftSize>=out)
		out*=2;
	return out;
}



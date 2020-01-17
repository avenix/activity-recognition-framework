/**
 @file
 @author  Juan Haladjian <juan.haladjian@gmail.com>
 @brief This file contains the types used by the ARF. These types can be easily adapted to each application
 
 ARF MIT License
 Copyright (c) <2019> <Juan Haladjian>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial
 portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef ARFTypedefs_h
#define ARFTypedefs_h

#include "ARFException.h"

namespace ARF {

//forecasts
template <typename T> class Vector;
template <typename T> class Matrix;

//typedefs
typedef float Float;
typedef unsigned int UINT;


//Activity Recognition Chain:
//stages: Data Acquisition -> Preprocessing -> Feature Extraction -> Classification
//types: SensorSample -> Signal -> Feature -> FeatureVector -> ClassificationResult
typedef Vector<Float> SensorSample; //A single sensor reading (e.g. ax,ay,az,gx,gy,gz)

class DataIterator;
typedef DataIterator Signal;//A one-dimensional signal (e.g. several ax readings)

typedef Float Feature;//A feature describing a Signal (e.g. the mean of a Signal)

typedef Vector<Float> FeatureVector;//A vector of features (e.g. mean, std, corr)

typedef uint8_t ClassificationResult;//the result of a classifier (e.g. running)

//interfaces
template <typename T> class Iterable {
public:
	virtual const T& operator()(const UINT rowIdx, const UINT colIdx) const {
		throw ARFException("ARFTypedefs::Iterable operator() called on Iterable()");
	}
	virtual const T& operator()(const UINT idx) const {
		throw ARFException("ARFTypedefs::Iterable operator() called on Iterable()");
	}
	virtual const T& operator[](const UINT idx) const {
		throw ARFException("ARFTypedefs::Iterable operator() called on Iterable()");
	}
	virtual UINT getSize() const = 0;
};

}

#endif /* ARFTypedefs_h */

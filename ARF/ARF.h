/**
@file
@author  Juan Haladjian <juan.haladjian@gmail.com>
@brief This is the main ARF header. You should include this to access all the ARF classes in your project.
 
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

#ifndef ARF_h
#define ARF_h

//include data structures
#include "dataStructures/Data.h"
#include "dataStructures/Value.h"
#include "dataStructures/Vector.h"
#include "dataStructures/Matrix.h"
#include "dataStructures/MatrixView.h"
#include "dataStructures/RingBuffer.h"

//include the typedefs
#include "utils/ARFTypedefs.h"

//include the core files
#include "algorithms/core/Algorithm.h"

//include the data acquisition files
#include "algorithms/1-dataAcquisition/RingBufferAlgorithm.h"

//include the preprocessing files
#include "algorithms/2-preprocessing/Magnitude.h"

//include the event detection files
#include "algorithms/3-eventDetection/PeakDetector.h"

//include the feature extraction files
#include "algorithms/4-featureExtraction/Minimum.h"
#include "algorithms/4-featureExtraction/Mean.h"

//include the utility files
#include "algorithms/other/MatrixSelector.h"
#include "algorithms/other/RingBufferSelector.h"

#endif /* ARF_h */

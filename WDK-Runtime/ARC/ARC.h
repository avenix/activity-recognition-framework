/**
@file
@author  Juan Haladjian <juan.haladjian@gmail.com>

ARC MIT License
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

@brief This is the main ARC header. You should include this to access all the ARC classes in your project.
*/
#ifndef ARC_h
#define ARC_h

//include the core files
#include "algorithms/core/Algorithm.h"

//include the data acquisition files
#include "algorithms/1-dataAcquisition/RingBuffer.h"

//include the preprocessing files
#include "algorithms/2-preprocessing/Magnitude.h"

//include the event detection files
#include "algorithms/3-eventDetection/PeakDetector.h"

//include the segmentation files
#include "algorithms/4-segmentation/FixedSegmentation.h"

//include the feature extraction files
#include "algorithms/5-featureExtraction/Minimum.h"
#include "algorithms/5-featureExtraction/Mean.h"

//include the utility files
#include "algorithms/other/AxisSelector.h"
#include "algorithms/other/RangeSelector.h"

#endif /* ARC_h */

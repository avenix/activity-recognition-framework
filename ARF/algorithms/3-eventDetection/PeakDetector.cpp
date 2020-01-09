/** 
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

#include "PeakDetector.h"
#include "../../dataStructures/Matrix.h"
#include "../../dataStructures/Value.h"

namespace ARF {

PeakDetector::PeakDetector(float minPeakHeight, int minPeakDistance) :
minPeakHeight(minPeakHeight),
minPeakDistance(minPeakDistance) {
	
}

/**
 Checks if the current sample is a peak based on the class parameters
 
 @param data A Matrix containing the magnitude of the current sample
 @return Returns the current sample if it was detected as a peak. Otherwise returns nullptr.
 */
Data* PeakDetector::execute(Data* data) {
	Value * value = (Value*) data;
	
	samplesSinceLastPeak += 1;
	
	if (lastPeakValue > 0 && samplesSinceLastPeak >= minPeakDistance) {
		lastPeakValue = 0.0;
		samplesSinceLastPeak = -1;
		return data;
	}
	
	float sampleMagnitude = value->getValue();
	
	if (sampleMagnitude >= minPeakHeight) {
		if (sampleMagnitude > lastPeakValue || samplesSinceLastPeak >= minPeakDistance) {
			lastPeakValue = sampleMagnitude;
			samplesSinceLastPeak = 0;
		}
	}
	return nullptr;
}

}

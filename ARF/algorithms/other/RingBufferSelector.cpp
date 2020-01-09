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

#include "RingBufferSelector.h"

namespace ARF {

/**
 Returns a RingBufferSelector that can access a selection of the data in the ringBuffer
 
 @param ringBuffer The ring buffer that will be accessed
 @param ringBufferRange The range of values of the ringBuffer that will be accessed
 */
RingBufferSelector::RingBufferSelector(RingBuffer<SensorSample> * ringBuffer, const RingBufferRange & ringBufferRange) :
ringBuffer(ringBuffer), ringBufferRange(ringBufferRange){ }

/**
 Returns a RingBufferSelector that can access a selection of the data in the ringBuffer
 
 @param ringBuffer The ring buffer that will be accessed
 @param startIdx The first index that should be accessed in the ringBuffer
 @param nSamples The number of samples that should returned from ringBuffer
 */
RingBufferSelector::RingBufferSelector(RingBuffer<SensorSample> * ringBuffer, const UINT startIdx, const UINT nSamples) : ringBuffer(ringBuffer), ringBufferRange(startIdx,nSamples){ }

/**
 Returns a RingBufferSelector that can access a selection of the data in the matrix passed as input parameter
 
 @param data The RingBufferView object from which data can be accessed
 @return A MatrixView object, which is able to access the rows between [startRow, endRow] and {data in the
 */
Data* RingBufferSelector::execute(Data * data) {
		
	return new RingBufferView(ringBuffer,
									 ringBufferRange.startIdx,
									 ringBufferRange.nSamples);
}

}

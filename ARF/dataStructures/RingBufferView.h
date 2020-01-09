/**
 @file
 @author  Juan Haladjian <juan.haladjian@gmail.com>
 @brief
 
 
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

#ifndef ARF_RING_BUFFER_VIEW_H
#define ARF_RING_BUFFER_VIEW_H

#include "RingBuffer.h"
#include "../utils/ARFTypedefs.h"

namespace ARF {

struct RingBufferRange {
	UINT startIdx; ///< The starting index to be accessed
	UINT nSamples; ///< The number of samples that will be accessed
	
	/**
	 Returns a RingBufferRange describing a range of values in a RingBuffer
	 
	 @param startIdx the starting index to be accessed
	 @param nSamples the number of samples to be accessed
	 */
	RingBufferRange(UINT startIdx, UINT nSamples) :
	startIdx(startIdx), nSamples(nSamples){ }
	
};

class RingBufferView : public Data{
	
private:
	const RingBuffer<SensorSample> * ringBuffer; ///< The ringBuffer that will be accessed
	RingBufferRange ringBufferRange; ///< The range of values to access
	
public:
	/**
	 Returns a RingBufferView ready to access values in a ring buffer
	 
	 @param ringBuffer the ring buffer to be accessed
	 @param startIdx the starting index to be accessed
	 @param nSamples the number of samples to be accessed
	 */
	RingBufferView(RingBuffer<SensorSample> * ringBuffer, UINT startIdx, UINT nSamples) :
	ringBuffer(ringBuffer), ringBufferRange({startIdx, nSamples}){ }
	
	/**
	 Returns a RingBufferView ready to access values in a ring buffer
	 
	 @param rhs the ring buffer that will be copied
	 */
	RingBufferView(const RingBufferView & rhs) :
	ringBuffer(rhs.getRingBuffer()), ringBufferRange(rhs.getRingBufferRange()){ }
	
	/**
	 Clones the data object
	 @return the cloned object
	 */
	RingBufferView * clone() override {
		return new RingBufferView(*this);
	}
	
	/**
	 Returns the value at the input index
	 
	 @param idx the vector index of the element that should be returned
	 @return returns the value at index idx
	 */
	const SensorSample& operator[](const UINT idx) const{
		return (*ringBuffer)[idx];
	}
	
	/**
	 Returns the value at the input index
	 
	 @return returns the number of values that will be accessed
	 */
	UINT size() const{
		return ringBufferRange.nSamples;
	}
	
	/**
	 Returns the pointer to the ring buffer
	 
	 @return returns the pointer to the ring buffer
	 */
	const RingBuffer<SensorSample> * getRingBuffer() const{
		return ringBuffer;
	}
	
	/**
	 Returns the ring buffer range
	 
	 @return returns the ring buffer range
	 */
	const RingBufferRange& getRingBufferRange() const{
		return ringBufferRange;
	}
};

}

#endif /* ARF_RING_BUFFER_VIEW_H */

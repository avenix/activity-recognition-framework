/**
 @file
 @author  Juan Haladjian <juan.haladjian@gmail.com>
 @brief The RingBuffer is a generic ring buffer data structure. As it is a subclass of Algorithm, it implements the execute() method. The execute() method receives a pointer to a SensorSample (typedef Vector<Float>), which it stores in the data property (Matrix<Float). The execute() method outputs a pointer to a SensorSample depending on the notificationOffset and notificationInterval properties. The notificationInterval determines how often samples are output. A notificationInterval = 1 causes the execute() method to output a SensorSample every time the execute() method is invoked. The notificationOffset can be used to control which sample is output. A notificationOffset = 0 causes the last sample added to the RingBuffer to be output by it. If the notificationOffset > 0, the RingBuffer contains samples that arrived later in time than the output sample. This can be useful in combination with an event detection algorithm. A typical segmentation strategy when working with sensor data is the sliding window. To achieve a sliding window with size 512 with 50% olapping, the RingBuffer can be configured using numRows = 512, notificationInterval = 256 and notificationOffset = 0.
 
 
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

#ifndef ARF_RING_BUFFER_H
#define ARF_RING_BUFFER_H

#include "../utils/ARFException.h"
#include "../utils/ARFConstants.h"
#include "../utils/ARFTypedefs.h"

namespace ARF {

template <typename T>
class RingBuffer {
	
private:
	T * data; ///< The pointer containing the data
	UINT size; ///< The amount of elements currently in the ringBuffer
	UINT capacity; ///< The capacity of the RingBuffer
	UINT endIdx; ///< The index of the last element in the RingBuffer
	
public:
	
	/**
	 Main constructor of the ring buffer
	 
	 @param capacity the number of elements the ring buffer should store
	 */
	RingBuffer(UINT capacity) : capacity(capacity), size(0), endIdx(0){
		
		if (capacity == 0){
			throw ARFException("RingBuffer::RingBuffer() capacity should not be zero");
		}
		
		//data = Vector<T>(capacity);
		data = new T[capacity];
	}
	
	/**
	 Main destructor of the ring buffer
	 */
	~RingBuffer(){
		delete[] data;
	}
	/**
	 Adds an element to the ringBuffer
	 
	 @param rhs the element to append to the ring buffer
	 */
	void add(const T &rhs){
		
		data[endIdx] = rhs;
		
		//increase ring buffer size by one
		if (size < capacity) {
			size++;
		}
		
		//increase endIdx by one
		endIdx++;
		if (endIdx == capacity) {
			endIdx = 0;
		}
	}
	
	/**
	 Retrieves the amount of elements in the RingBuffer
	 
	 @return the size of the RingBuffer
	 */
	inline UINT getSize() const{
		return size;
	}
	
	/**
	 Retrieves the amount of elements in the RingBuffer
	 
	 @return the size of the RingBuffer
	 */
	inline UINT getCapacity() const{
		return capacity;
	}
	
	/**
	 Retrieves the index of the last element + 1
	 
	 @return the endIdx
	 */
	inline UINT getEndIdx() const{
		return endIdx;
	}
	
	/**
	 Retrieves the index of the first element in the RingBuffer
	 
	 @return the index of the first element
	 */
	inline UINT getFirstElementIdx() const{
		int firstIdx = endIdx - size;
		if(firstIdx < 0)
			firstIdx += capacity;
		return (UINT) firstIdx;
	}
	
	/**
	 Retrieves the first element in the RingBuffer
	 
	 @return the first element
	 */
	inline T getFirstElement() const{
		UINT firstIdx = getFirstElementIdx();
		return data[firstIdx];
	}
	
	/**
	 Retrieves the last element in the RingBuffer
	 
	 @return the last element
	 */
	inline T getLastElement() const{
		UINT lastIdx = getEndIdx();
		return data[lastIdx];
	}
	
	/**
	 Retrieves an element from the ring buffer
	 
	 @param idx the index of the element you want
	 @return the SensorSample
	 */
	T getElementAtIdx(UINT idx) const{
		UINT firstIdx = getFirstElementIdx();
		int actualIdx = idx + firstIdx;
		if(actualIdx > capacity){
			actualIdx -= capacity;
		}
		return data[actualIdx];
	}
};

}

#endif //ARF_RINGBUFFER_H

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

#ifndef ARF_DATA_ITERATOR_H
#define ARF_DATA_ITERATOR_H

#include "RingBuffer.h"
#include "../utils/ARFTypedefs.h"

namespace ARF {

struct IterableRange {
	UINT startIdx; ///< The starting index to be accessed
	UINT nElements; ///< The number of elements that will be accessed
	
	/**
	 Returns a RingBufferRange describing a range of values in a RingBuffer
	 
	 @param startIdx the starting index to be accessed
	 @param nElements the number of elements to be accessed
	 */
	IterableRange(UINT startIdx, UINT nElements) :
	startIdx(startIdx), nElements(nElements){ }
};

template <typename T>
class DataIterator : public Data {
	
private:
	const Iterable<T> * iterable; ///< The iterable that will be accessed
	IterableRange iterableRange; ///< The range of values to access
	
public:
	/**
	 Returns a DataIterator ready to access values in an iterable
	 
	 @param iterable the iterable to be accessed
	 @param startIdx the starting index to be accessed
	 @param nElements the number of elements to be accessed
	 */
	DataIterator(Iterable<T> * iterable, UINT startIdx, UINT nElements) :
	iterable(iterable), iterableRange({startIdx, nElements}){ }
	
	/**
	 Clones the data object
	 @return the cloned object
	 */
	DataIterator * clone() override {
		return new DataIterator(*this);
	}
	
	/**
	 Returns the value at the input index
	 
	 @param idx the vector index of the element that should be returned
	 @return returns the value at index idx
	 */
	const T& operator[](const UINT idx) const{
		return (*iterable)[idx + iterableRange.startIdx];
	}
	
	/**
	 Returns the number of elements that will be accessed
	 
	 @return the number of elements that will be accessed
	 */
	UINT size() const{
		return iterableRange.nElements;
	}
	
	/**
	 Returns a pointer to the iterable
	 
	 @return returns a pointer to the iterable
	 */
	const Iterable<T> * getIterable() const{
		return iterable;
	}
	
	/**
	 Returns the iterable range
	 
	 @return returns the iterable range
	 */
	const IterableRange& getIterableRange() const{
		return iterableRange;
	}
};

}

#endif /* ARF_DATA_ITERATOR_H */

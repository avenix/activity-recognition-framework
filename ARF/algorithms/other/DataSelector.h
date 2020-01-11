/**
 @file
 @author  Juan Haladjian <juan.haladjian@gmail.com>
 @brief The DataSelector can access a selection of the data in a collection (e.g. vector or ringBuffer) without having to rellocate memory
 
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

#ifndef ARF_DATA_SELECTOR_H
#define ARF_DATA_SELECTOR_H

#include "../core/Algorithm.h"
#include "../../dataStructures/DataIterator.h"
#include "../../dataStructures/DataIterator2D.h"
#include "../../utils/ARFTypedefs.h"

namespace ARF {

template <typename T>
class DataSelector : public Algorithm {
	
private:
	Iterable<T> * iterable;
	
	IterableRange iterableRange;
	IterableRange2D iterableRange2D;
	
	bool use2DRange;
	
public:
	/**
	 Main constructor for the DataSelector to return elements from a 1D iterator
	 
	 @param iterable The collection that will be accessed
	 @param startIdx The first index that should be accessed in the ringBuffer
	 @param nElements The number of elements that should returned from ringBuffer
	 */
	DataSelector(Iterable<T> * iterable, const UINT startIdx, const UINT nElements) :
	iterable(iterable), iterableRange(startIdx,nElements), use2DRange(false) { }
	
	/**
	 Main constructor for the DataSelector to return elements from a 2D iterator
	 
	 @param iterable The collection that will be accessed
	 @param startRow The first row that should be accessed in the 2D iterator
	 @param endRow The last row that should returned in the 2D iterator
	 @param columnIndices The columns to be returned
	 */
	DataSelector(Iterable<T> * iterable, UINT startRow, UINT endRow, const std::vector<uint8_t> &columnIndices) :
	iterable(iterable), iterableRange2D(startRow,endRow,columnIndices), use2DRange(true){ }
	
	/**
	 Returns a DataIterator that can access a selection of the data in the container defined in the 'iterable' property,
	 or in the input parameter in case the 'iterable' property is nil
	 
	 @param data A nil pointer or an Iterable from which data can be accessed
	 @return A DataIterator object
	 */
	Data * execute(Data * data) override {
		//Iterable<T> * it = (iterable == nullptr) ? (Iterable<T> *) data : iterable;
		
		if(iterable->getSize() < iterableRange.nElements){
			throw ARFException("DataSelector::execute() cannot retrieve more elements than available in the container\n");
			return nullptr;
		}
		
		if(use2DRange){
			return new DataIterator2D<T>(iterable, iterableRange2D);
		} else {
			return new DataIterator<T>(iterable, iterableRange.startIdx, iterableRange.nElements);
		}
	}
};

}

#endif //ARF_DATA_SELECTOR_H

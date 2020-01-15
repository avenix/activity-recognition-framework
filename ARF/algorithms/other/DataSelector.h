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
#include "../../dataStructures/DataIterator.h"
#include "../../utils/ARFTypedefs.h"

namespace ARF {

class DataSelector : public Algorithm {
	
private:
	Iterable<SensorSample> * iterable;
	IterableRange iterableRange;
	
public:
	/**
	 Main constructor for the DataSelector to return elements from a 2D iterator
	 
	 @param iterable The collection of SensorSamples that will be accessed
	 @param startRow The first row that should be accessed in the 2D iterator
	 @param endRow The last row that should returned in the 2D iterator
	 @param columnIndices The columns to be returned
	 */
	DataSelector(Iterable<SensorSample> * iterable, const UINT startRow, const UINT endRow, const Vector<uint8_t> &columnIndices) : iterable(iterable), iterableRange(startRow, endRow, columnIndices){ }
	
	/**
	 Returns a DataIterator that can access a selection of the data in the container defined in the 'iterable' property,
	 or in the input parameter in case the 'iterable' property is nil
	 
	 @param data A nil pointer or an Iterable from which data can be accessed
	 @return A DataIterator object
	 */
	Data * execute(Data * data) override {
		return new DataIterator(iterable, iterableRange);
	}
};

}

#endif //ARF_DATA_SELECTOR_H

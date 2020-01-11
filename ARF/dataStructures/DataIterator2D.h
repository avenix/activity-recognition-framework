/**
 @file
 @author  Juan Haladjian <juan.haladjian@gmail.com>
 @brief The MatrixView is a pointer to a portion of a Matrix. This makes it possible to pass references of data instead of copying the data
 
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

#ifndef ARF_DATA_ITERATOR_2D_H
#define ARF_DATA_ITERATOR_2D_H

#import <vector>
#include "Data.h"
#include "../utils/ARFTypedefs.h"

namespace ARF {

struct IterableRange2D {
	UINT startRow;
	UINT endRow;
	std::vector<uint8_t> columnIndices;
	
	IterableRange2D(UINT startRow, UINT endRow) :
	startRow(startRow), endRow(endRow){ }
	
	IterableRange2D(UINT startRow, UINT endRow,
						 const std::vector<uint8_t> &columnIndices) :
	startRow(startRow), endRow(endRow), columnIndices(columnIndices) { }
};

template <typename T>
class DataIterator2D : public Data {
	
private:
	const Iterable<T> * iterable; ///< The iterable that will be accessed
	IterableRange2D iterableRange;
	
public:
	
	DataIterator2D(Iterable<T> * matrix, UINT startRow, UINT endRow, const std::vector<uint8_t> &columnIndices) :
	iterable(iterable), iterableRange({startRow, endRow, columnIndices}){
	}
	
	DataIterator2D(Iterable<T> * matrix, IterableRange2D iterableRange) :
	iterable(iterable), iterableRange(iterableRange){
	}
	
	DataIterator2D(const DataIterator2D<T> & rhs) :
	iterable(rhs.getIterable()), iterableRange(rhs.getIterableRange()){
	}
	
	/**
	 Clones the data object
	 @return the cloned object
	 */
	DataIterator2D<T> * clone() override {
		return new DataIterator2D(*this);
	}
	
	const Iterable<T> * getIterable() const{
		return iterable;
	}
	
	const IterableRange2D& getMatrixRange() const{
		return iterableRange;
	}
	
	void setColumnIndices(const std::vector<uint8_t> &newColumnIndices) {
		iterableRange.columnIndices = newColumnIndices;
	}
	
	void setRowRange(UINT newStartRow, UINT newEndRow) {
		iterableRange.startRow = newStartRow;
		iterableRange.endRow = newEndRow;
	}
	
	UINT getStartRow(){
		return iterableRange.startRow;
	}
	
	UINT getEndRow(){
		return iterableRange.endRow;
	}
	
	UINT getNumRows() {
		return iterableRange.endRow - iterableRange.startRow + 1;
	}
	
	UINT getNumColumns() {
		return iterableRange.columnIndices.size();
	}
	
	/**
	 Returns the number of elements that will be accessed
	 
	 @return the number of elements that will be accessed
	 */
	inline UINT getSize() const{
		return getNumRows() * getNumColumns();
	}
	
	/**
	 Returns a pointer to the data at row r
	 
	 @param rowIdx the index of the row, should be in the range [0 rows)
	 @param colIdx the index of the column, should be in the range [0 columns)
	 @return a pointer to the data at row r
	 */
	inline const T& operator()(const UINT rowIdx, const UINT colIdx) const override {
		UINT iterableRowIdx = rowIdx + iterableRange.startRow;
		UINT iterableColumnIdx = iterableRange.columnIndices[colIdx];
		return iterable[iterableRowIdx][iterableColumnIdx];
	}
};

}

#endif //ARF_DATA_ITERATOR_2D_H

/**
 @file
 @author Juan Haladjian <juan.haladjian@gmail.com>
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
#include "../utils/ARFException.h"

namespace ARF {

struct IterableRange2D {
	UINT startRow;
	UINT endRow;
	std::vector<uint8_t> columnIndices;
	
	IterableRange2D(UINT startRow=0, UINT endRow=0) :
	startRow(startRow), endRow(endRow){ }
	
	IterableRange2D(UINT startRow, UINT endRow,
						 const std::vector<uint8_t> &columnIndices) :
	startRow(startRow), endRow(endRow), columnIndices(columnIndices) { }
};

class DataIterator2D : public Data, public Iterable2D<Float> {

private:
	const Iterable<SensorSample> * iterable; ///< The iterable that will be accessed
	IterableRange2D iterableRange;
	
public:
	
	DataIterator2D(Iterable<SensorSample> * iterable, UINT startRow, UINT endRow, const std::vector<uint8_t> &columnIndices) :
	iterable(iterable), iterableRange({startRow, endRow, columnIndices}){
	}
	
	DataIterator2D(Iterable<SensorSample> * iterable, IterableRange2D iterableRange) :
	iterable(iterable), iterableRange(iterableRange){
	}
	
	DataIterator2D(const DataIterator2D & rhs) :
	iterable(rhs.getIterable()), iterableRange(rhs.getIterableRange()){
	}
	
	/**
	 Clones the data object
	 @return the cloned object
	 */
	Data * clone() override {
		return new DataIterator2D(*this);
	}
	
	const Iterable<SensorSample> * getIterable() const{
		return iterable;
	}
	
	const IterableRange2D& getIterableRange() const{
		return iterableRange;
	}
	
	void setColumnIndices(const std::vector<uint8_t> &newColumnIndices) {
		iterableRange.columnIndices = newColumnIndices;
	}
	
	void setRowRange(UINT newStartRow, UINT newEndRow) {
		iterableRange.startRow = newStartRow;
		iterableRange.endRow = newEndRow;
	}
	
	UINT getStartRow() const{
		return iterableRange.startRow;
	}
	
	UINT getEndRow() const{
		return iterableRange.endRow;
	}
	
	UINT getNumRows() const {
		return iterableRange.endRow - iterableRange.startRow + 1;
	}
	
	UINT getNumColumns() const{
		return (UINT) iterableRange.columnIndices.size();
	}
	
	/**
	 Returns the number of elements that will be accessed
	 
	 @return the number of elements that will be accessed
	 */
	inline UINT getSize() const override{
		return getNumRows() * getNumColumns();
	}
	
	/**
	 Returns a reference to the data at (rowIdx, colIdx)
	 
	 @param rowIdx the index of the row, should be in the range [0 rows)
	 @param colIdx the index of the column, should be in the range [0 columns)
	 @return a reference to the data at (rowIdx,colIdx)
	 */
	inline const Float& operator()(const UINT rowIdx, const UINT colIdx) const override {
		return getDataAtIdx(rowIdx, colIdx);
	}
	
	/**
	 Returns the value at the input index
	 
	 @param rowIdx the vector index of the element that should be returned
	 @return returns the value at index idx
	 */
	const Float& getDataAtIdx(const UINT rowIdx, const UINT colIdx) const {
		UINT iterableRowIdx = rowIdx + iterableRange.startRow;
		UINT iterableColumnIdx = iterableRange.columnIndices[colIdx];
		return (*iterable)[iterableRowIdx][iterableColumnIdx];
	}
	
	/**
	 Returns the value at the input index
	 
	 @param idx the vector index of the element that should be returned
	 @return returns the value at index idx
	 */
	const Float& operator[](const UINT idx) const{
		return getDataAtIdx(idx);
	}
	
	/**
	 Returns the value at the input index
	 
	 @param idx the vector index of the element that should be returned
	 @return returns the value at index idx
	 */
	const Float& getDataAtIdx(const UINT idx) const {
		
		if(getNumRows() == 1){
			UINT columnIdx = iterableRange.columnIndices[idx];
			return (*iterable)[iterableRange.startRow][columnIdx];
		} else if(getNumColumns() == 1){
			UINT columnIdx = iterableRange.columnIndices[0];
			return (*iterable)[iterableRange.startRow + idx][columnIdx];
		} else {
			throw ARFException("DataIterator::getDataAtIdx() when accessing data with a single index, the iterable range should be a column vector or a row vector");
		}
	}
};

}

#endif //ARF_DATA_ITERATOR_2D_H

/**
 @file
 @author  Juan Haladjian <juan.haladjian@gmail.com>
 
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
 
 @brief This is the main ARF header. You should include this to access all the ARF classes in your project.
 */

#ifndef ARF_DATAACCESSOBJECT_H
#define ARF_DATAACCESSOBJECT_H

#import <vector>

#include "Data.h"
#include "../utils/ARFTypedefs.h"

namespace ARF {

template <typename T>
class MatrixView : public Data {
private:
	UINT startRow;
	UINT endRow;
	std::vector<uint8_t> columnIndices;
	Matrix<T> * matrix;
	
public:
	MatrixView(Matrix<T> * matrix, UINT startRow, UINT endRow) :
	matrix(matrix), startRow(startRow), endRow(endRow) {
	}
	
	MatrixView(Matrix<T> * matrix, UINT startRow, UINT endRow, const std::vector<uint8_t> &columnIndices) :
	matrix(matrix), startRow(startRow), endRow(endRow), columnIndices(columnIndices) {
	}
	
	void setColumnIndices(const std::vector<uint8_t> &newColumnIndices) {
		columnIndices = newColumnIndices;
	}
	
	void setRowRange(UINT newStartRow, UINT newEndRow) {
		startRow = newStartRow;
		endRow = newEndRow;
	}
	
	UINT getStartRow(){
		return startRow;
	}
	
	UINT getEndRow(){
		return endRow;
	}
	
	UINT getNumRows() {
		return endRow - startRow + 1;
	}
	
	UINT getNumColumns() {
		return columnIndices.size();
	}
	
	/**
	 Returns a pointer to the data at row r
	 
	 @param r the index of the row, should be in the range [0 rows-1]
	 @return a pointer to the data at row r
	 */
	inline T* operator[](const unsigned int r){
		return matrix[r + startRow];
	}
	
	/**
	 Returns a const pointer to the data at row r
	 
	 @param r the index of the row, should be in the range [0 rows-1]
	 @return a const pointer to the data at row r
	 */
	inline const T* operator[](const unsigned int r) const{
		return matrix[r];
	}
};

}

#endif //ARF_DATAACCESSOBJECT_H

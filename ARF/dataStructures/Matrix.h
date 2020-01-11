/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>, Juan Haladjian <juan.haladjian@gmail.com>
 @version 2.0
 @brief Generic 2D matrix data structure.
 */

/*
 GRT MIT License
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>
 
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

#ifndef Matrix_h
#define Matrix_h

#include "Vector.h"

namespace ARF {

template <class T> class Matrix : public Data, public Iterable2D<T>{
public:
	/**
	 Default Constructor
	 */
	Matrix(){
		rows = 0;
		cols = 0;
		size = 0;
		capacity = 0;
		dataPtr = NULL;
		rowPtr = NULL;
	}
	
	/**
	 Constructor, sets the size of the matrix to [rows cols]
	 
	 @param rows: sets the number of rows in the matrix, must be a value greater than zero
	 @param cols: sets the number of columns in the matrix, must be a value greater than zero
	 */
	Matrix(const unsigned int rows,const unsigned int cols){
		dataPtr = NULL;
		rowPtr = NULL;
		resize(rows,cols);
	}
	
	/**
	 Constructor, sets the size of the matrix to [rows cols] and initalizes all the data to data
	 
	 @param rows: sets the number of rows in the matrix, must be a value greater than zero
	 @param cols: sets the number of columns in the matrix, must be a value greater than zero
	 @param data: default value that will be used to initalize all the values in the matrix
	 */
	Matrix(const unsigned int rows,const unsigned int cols, const T &data ){
		dataPtr = NULL;
		rowPtr = NULL;
		resize(rows,cols,data);
	}
	
	/**
	 Copy Constructor, copies the values from the rhs Matrix to this Matrix instance
	 
	 @param rhs: the Matrix from which the values will be copied
	 */
	Matrix(const Matrix &rhs){
		this->dataPtr = NULL;
		this->rowPtr = NULL;
		this->rows = 0;
		this->cols = 0;
		this->size = 0;
		this->capacity = 0;
		this->copy( rhs );
	}
	
	/**
	 Copy Constructor, copies the values from the input vector to this Matrix instance.
	 The input vector must be a vector< vector< T > > in a [rows cols] format.  The number of
	 columns in each row must be consistent.  Both the rows and columns must be greater than 0.
	 
	 @param data: the input data which will be copied to this Matrix instance
	 */
	Matrix(const Vector<Vector<T>> &data){
		this->dataPtr = NULL;
		this->rowPtr = NULL;
		this->rows = 0;
		this->cols = 0;
		this->size = 0;
		this->capacity = 0;
		
		unsigned int tempRows = data.getSize();
		unsigned int tempCols = 0;
		
		//If there is no data then return
		if( tempRows == 0 ) return;
		
		//Check to make sure all the columns are the same size
		for(unsigned int i=0; i<tempRows; i++){
			if( i == 0 ) tempCols = data[i].getSize();
			else{
				if( data[i].getSize() != tempCols ){
					return;
				}
			}
		}
		
		if( tempCols == 0 ) return;
		
		//Resize the matrix and copy the data
		if( resize(tempRows,tempCols) ){
			for(unsigned int i=0; i<tempRows; i++){
				for(unsigned int j=0; j<tempCols; j++){
					dataPtr[(i*cols)+j] = data[i][j];
				}
			}
		}
	}
	
	/**
	 Destructor, cleans up any memory
	 */
	virtual ~Matrix(){
		clear();
	}
	
	/**
	 Clones the data object
	 @return the cloned object
	 */
	Matrix * clone() override {
		return new Matrix(*this);
	}
	
	/**
	 Defines how the data from the rhs Matrix should be copied to this Matrix
	 
	 @param rhs: another instance of a Matrix
	 @return returns a reference to this instance of the Matrix
	 */
	Matrix& operator=(const Matrix &rhs){
		if(this!=&rhs){
			this->clear();
			this->copy( rhs );
		}
		return *this;
	}
	
	/**
	 Returns a pointer to the data at row r
	 
	 @param r: the index of the row you want, should be in the range [0 rows-1]
	 @return a pointer to the data at row r
	 */
	inline T* operator[](const unsigned int r){
		return rowPtr[r];
	}
	
	/**
	 Returns a const pointer to the data at row r
	 
	 @param r: the index of the row you want, should be in the range [0 rows-1]
	 @return a const pointer to the data at row r
	 */
	inline const T* operator[](const unsigned int r) const{
		return rowPtr[r];
	}
	
	/**
	 Returns a const pointer to the data at row r
	 
	 @param r: the index of the row you want, should be in the range [0 rows-1]
	 @return a const pointer to the data at row r
	 */
	inline const T* operator()(const UINT rowIdx, const UINT colIdx) const override{
		return rowPtr[rowIdx][colIdx];
	}
	
	/**
	 Gets a row vector [1 cols] from the Matrix at the row index r
	 
	 @param r: the index of the row you want, should be in the range [0 rows-1]
	 @return returns a row vector from the Matrix at the row index r
	 */
	Vector<T> getRowVector(const unsigned int r) const{
		Vector<T> rowVector(cols);
		for(unsigned int c = 0; c < cols; c++)
			rowVector[c] = dataPtr[r * cols + c];
		return rowVector;
	}
	
	/**
	 Gets a column vector [rows 1] from the Matrix at the column index c
	 
	 @param c: the index of the column you want, should be in the range [0 cols-1]
	 @return returns a column vector from the Matrix at the column index c
	 */
	Vector<T> getColVector(const unsigned int c) const{
		Vector<T> columnVector(rows);
		for(unsigned int r = 0; r < rows; r++)
			columnVector[r] = dataPtr[r*cols+c];
		return columnVector;
	}
	
	/**
	 Resizes the Matrix to the new size of [r c].  If [r c] matches the previous size then the matrix will not be resized but the function will return true.
	 
	 @param r: the number of rows, must be greater than zero
	 @param c: the number of columns, must be greater than zero
	 @return returns true or false, indicating if the resize was successful
	 */
	virtual bool resize(const unsigned int r, const unsigned int c){
		
		if( r + c == 0 ){
			return false;
		}
		
		//If the rows and cols are unchanged then do not resize the data
		if( r == rows && c == cols ){
			return true;
		}
		
		//Clear any previous memory
		clear();
		
		if( r > 0 && c > 0 ){
			try{
				rows = r;
				cols = c;
				size = r * c;
				capacity = r;
				
				dataPtr = new T[size];
				rowPtr = new T*[rows];
				
				if( dataPtr == NULL ){
					rows = 0;
					cols = 0;
					size = 0;
					capacity = 0;
					return false;
				}
				
				if( rowPtr == NULL ){
					rows = 0;
					cols = 0;
					size = 0;
					capacity = 0;
					return false;
				}
				
				//Setup the row pointers
				unsigned int i=0;
				T * p = &(dataPtr[0]);
				for(i=0; i < rows; i++){
					rowPtr[i] = p;
					p += cols;
				}
				
				return true;
				
			} catch( std::exception& e ){
				clear();
				return false;
			} catch( ... ){
				clear();
				return false;
			}
		}
		return false;
	}
	
	/**
	 Resizes the Matrix to the new size of [r c].  If [r c] matches the previous size then the matrix will not be resized but the function will return true.
	 
	 @param r: the number of rows, must be greater than zero
	 @param c: the number of columns, must be greater than zero
	 @param value: the default value that will be set across all values in the buffer
	 @return returns true or false, indicating if the resize was successful
	 */
	virtual bool resize(const unsigned int r, const unsigned int c,const T &value){
		
		if( !resize( r, c) ){
			return false;
		}
		
		return setAll( value );
	}
	
	/**
	 Copies the data from the rhs matrix to this matrix.
	 
	 @param rhs: the matrix you want to copy into this matrix
	 @return returns true or false, indicating if the copy was successful
	 */
	virtual bool copy( const Matrix<T> &rhs ){
		
		if( this != &rhs ){
			
			if( this->size != rhs.size ){
				if( !this->resize( rhs.rows, rhs.cols ) ){
					return false;
				}
			}
			
			//Copy the data
			unsigned int i = 0;
			for(i=0; i<size; i++){
				this->dataPtr[i] = rhs.dataPtr[i];
			}
		}
		
		return true;
	}
	
	/**
	 Sets all the values in the Matrix to the input value
	 
	 @param value: the value you want to set all the Matrix values to
	 @return returns true or false, indicating if the set was successful
	 */
	bool setAll(const T &value){
		if(dataPtr!=NULL){
			unsigned int i =0;
			for(i=0; i<size; i++)
				dataPtr[i] = value;
			return true;
		}
		return false;
	}
	
	/**
	 Sets all the values in the row at rowIndex with the values in the vector called row.
	 The size of the row vector must match the number of columns in this Matrix.
	 
	 @param row: the vector of row values you want to add
	 @param rowIndex: the row index of the row you want to update, must be in the range [0 rows]
	 @return returns true or false, indicating if the set was successful
	 */
	bool setRowVector(const Vector<T> &row,const unsigned int rowIndex){
		if(dataPtr == NULL) return false;
		if(row.size() != cols) return false;
		if(rowIndex >= rows) return false;
		
		unsigned int j = 0;
		for(j = 0; j < cols; j++)
			dataPtr[ rowIndex * cols + j ] = row[ j ];
		return true;
	}
	
	/**
	 Sets all the values in the column at colIndex with the values in the vector called column.
	 The size of the column vector must match the number of rows in this Matrix.
	 
	 @param column: the vector of column values you want to add
	 @param colIndex: the column index of the column you want to update, must be in the range [0 cols]
	 @return returns true or false, indicating if the set was successful
	 */
	bool setColVector(const Vector<T> &column,const unsigned int colIndex){
		if(dataPtr == NULL) return false;
		if(column.size() != rows) return false;
		if(colIndex >= cols) return false;
		
		for(unsigned int i=0; i<rows; i++)
			dataPtr[ i * cols + colIndex ] = column[ i ];
		return true;
	}
	
	
	/**
	 This function reserves a consistent block of data so new rows can more effecitenly be pushed_back into the Matrix.
	 The capacity variable represents the number of rows you want to reserve, based on the current number of columns.
	 
	 @param capacity: the new capacity value
	 @return returns true if the data was reserved, false otherwise
	 */
	bool reserve( const unsigned int capacity ){
		
		//If the number of columns has not been set, then we can not do anything
		if(cols == 0) return false;
		
		//Reserve the data and copy and existing data
		unsigned int i=0;
		T* tmpDataPtr = new T[ capacity * cols ];
		T** tmpRowPtr = new T*[ capacity ];
		if( tmpDataPtr == NULL || tmpRowPtr == NULL ){//If NULL then we have run out of memory
			return false;
		}
		
		//Setup the row pointers
		T *p = &(tmpDataPtr[0]);
		for(i = 0; i < capacity; i++){
			tmpRowPtr[i] = p;
			p += cols;
		}
		
		//Copy the existing data into the new memory
		for(i = 0; i < size; i++)
			tmpDataPtr[i] = dataPtr[i];
		
		//Delete the original data and copy the pointer
		delete[] dataPtr;
		delete[] rowPtr;
		dataPtr = tmpDataPtr;
		rowPtr = tmpRowPtr;
		
		//Store the new capacity
		this->capacity = capacity;
		
		//Store the size
		size = rows * cols;
		
		return true;
	}
	
	/**
	 Cleans up any dynamic memory and sets the number of rows and columns in the matrix to zero
	 @return returns true if the data was cleared successfully
	 */
	bool clear(){
		if(dataPtr != NULL){
			delete[] dataPtr;
			dataPtr = NULL;
		}
		
		if(rowPtr != NULL){
			delete[] rowPtr;
			rowPtr = NULL;
		}
		
		rows = 0;
		cols = 0;
		size = 0;
		capacity = 0;
		return true;
	}
	
	/**
	 Gets the number of rows in the Matrix
	 
	 @return returns the number of rows in the Matrix
	 */
	inline unsigned int getNumRows() const{ return rows; }
	
	/**
	 Gets the number of columns in the Matrix
	 
	 @return returns the number of columns in the Matrix
	 */
	inline unsigned int getNumCols() const{ return cols; }
	
	/**
	 Gets the capacity of the Matrix. This is the number of rows that have been reserved for the Matrix.
	 You can control the capacity using the reserve function
	 
	 @return returns the number of columns in the Matrix
	 */
	inline unsigned int getCapacity() const{ return capacity; }
	
	/**
	 Gets the size of the Matrix. This is rows * size.
	 
	 @return returns the number of columns in the Matrix
	 */
	inline UINT getSize() const override{ return size; }
	
	/**
	 Gets a pointer to the row buffer
	 
	 @return returns the row pointer
	 */
	T** getDataPointer() const{
		if( rowPtr == NULL ){
			return NULL;
		}
		return &(rowPtr[0]);
	}
	
	/**
	 Gets a pointer to the main data pointer
	 
	 @return returns a pointer to the raw data
	 */
	T* getData() const {
		return dataPtr;
	}
	
private:
	unsigned int rows;      ///< The number of rows in the Matrix
	unsigned int cols;      ///< The number of columns in the Matrix
	unsigned int size;      ///< Stores rows * cols
	unsigned int capacity;  ///< The capacity of the Matrix, this will be the number of rows, not the actual memory size
	T *dataPtr;             ///< A pointer to the raw data
	T **rowPtr;             ///< A pointer to each row in the data
};

}


#endif /* Matrix_h */

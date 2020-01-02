/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>
 @version 1.0
 
 @brief The Vector class is a basic class for storing any type of data.  The default Vector is an interface for std::vector, but the idea is
 this can easily be changed when needed (e.g., when running the GRT on an embedded device with limited STL support). This class is a template and can therefore be used with any generic data type.
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

#ifndef VECTOR_H
#define VECTOR_H

#include <iterator>     // std::front_inserter
#include <algorithm>    // std::copy
#include <vector>
#include "../utils/ARFTypedefs.h"

namespace ARF {

template <typename T> class Vector : public Data{
private:
	std::vector<T> data;
	
public:
	
	/**
	 Constructor, sets the size of the vector
	 
	 @param size the size of the vector
	 */
	Vector(const unsigned int size = 0) : data(std::vector<T>(size)){}
	
	/**
	 Constructor, sets the size of the vector and sets all elements to value
	 
	 @param size the size of the vector
	 */
	Vector(const unsigned int size, const T &value) : data(std::vector< T >(size, value)){}
	
	/**
	 Copy Constructor, copies the values from the rhs Vector to this Vector instance
	 
	 @param rhs the Vector from which the values will be copied
	 */
	Vector(const Vector &rhs){
		unsigned int N = rhs.size();
		if( N > 0 ){
			resize(N);
			std::copy(rhs.begin(), rhs.end(), data.begin());
		} else {
			clear();
		}
	}
	
	/**
	 Constructor, copies the content from the raw rhs array into this Vector instance
	 
	 @param rhs the raw data from which the values will be copied
	 @param size the size of the vector
	 */
	Vector(const T * rhs, UINT size) {
		if(size > 0){
			resize(size);
			std::copy(rhs, rhs + size, data.begin());
		} else {
			clear();
		}
	}
	
	/**
	 Copy Constructor, copies the values from the rhs std::vector to this Vector instance
	 
	 @param rhs the base class instance from which the values will be copied
	 */
	Vector(const std::vector<T> &rhs){
		unsigned int N = rhs.size();
		if(N > 0){
			resize(N);
			std::copy( rhs.begin(), rhs.end(), data.begin() );
		} else {
			clear();
		}
	}
	
	/**
	 Destructor, cleans up any memory
	 */
	virtual ~Vector(){ }
	
	/**
	 Defines how the data from the rhs Vector should be copied to this Vector
	 
	 @param rhs another instance of a Vector
	 @return returns a reference to this instance of the Vector
	 */
	Vector& operator=(const Vector &rhs){
		if(this != &rhs){
			UINT N = rhs.size();
			if(N > 0){
				resize(N);
				std::copy( rhs.begin(), rhs.end(), data.begin() );
			} else {
				clear();
			}
		}
		return *this;
	}
	
	/**
	 Defines how the data from the rhs std::vector instance should be copied to this Vector
	 
	 @param rhs another instance of a Vector
	 @return returns a reference to this instance of the Vector
	 */
	Vector& operator=(const std::vector<T> &rhs){
		if(this != &rhs){
			unsigned int N = rhs.size();
			if(N > 0){
				resize(N);
				std::copy( rhs.begin(), rhs.end(), data.begin() );
			} else {
				clear();
			}
		}
		return *this;
	}
	
	/**
	 Returns the value at the input index
	 
	 @param idx the vector index of the element that should be returned
	 @return returns the value at index idx
	 */
	inline T operator[](const unsigned int idx){
		return data[idx];
	}
	
	/**
	 Returns the value at the input index
	 
	 @param idx the vector index of the element that should be returned
	 @return returns the value at index idx
	 */
	inline const T operator[](const unsigned int idx) const{
		return data[idx];
	}
	
	/**
	 Erases the content of the vector
	 */
	void clear(){
		data.clear();
	}
	
	/**
	 Defines how the vector should be resized
	 
	 @param newSize the new size of the vector
	 @return returns true if the vector was resized correctly, false otherwise
	 */
	virtual bool resize(const unsigned int newSize){
		data.resize(newSize);
		return size() == newSize;
	}

	/**
	 Defines how the vector should be resized, this will also set all the values in the vector to [value]
	 
	 @param newSize the new size of the vector
	 @param value the value that will be copied to all elements in the vector
	 @return returns true if the vector was resized correctly, false otherwise
	 */
	virtual bool resize(const unsigned int newSize, const T &value){
		data.resize(newSize, value);
		return size() == newSize;
	}
	
	/**
	 Copies the data from the rhs vector to this vector.
	 
	 @param rhs the vector you want to copy into this vector
	 @return returns true or false, indicating if the copy was successful
	 */
	virtual bool copy(const Vector<T> &rhs){
		
		if(this != &rhs){
			unsigned int N = rhs.size();
			if( N > 0 ){
				resize(N);
				std::copy( rhs.begin(), rhs.end(), data.begin() );
			}
		}
		
		return true;
	}
	
	/**
	Returns an iterator pointing to the first element in the vector.
	
	@return returns the iterator
	*/
	typename std::vector<T>::iterator begin(){
		return data.begin();
	}
	
	/**
	Returns a constant iterator pointing to the first element in the vector.
	
	@return returns the iterator
	*/
	typename std::vector<T>::const_iterator begin() const{
		return data.begin();
	}
	
	/**
	Returns an iterator referring to the past-the-end element in the vector container.
	
	@return returns the iterator
	*/
	typename std::vector<T>::iterator end(){
		return data.end();
	}
	
	/**
	Returns an iterator referring to the past-the-end element in the vector container.
	
	@return returns the iterator
	*/
	typename std::vector<T>::const_iterator end() const{
		return data.end();
	}
	
	/**
	Adds a new element at the end of the vector, after its current last element. The content of val is copied to the new element.
	
	@param val the value to add to the vector
	*/
	void push_back(const T& val){
		data.push_back(val);
	}
	
	/**
	Adds a new element at the end of the vector, after its current last element. The content of val is moved to the new element.
	
	@param val the value to add to the vector
	*/
	void push_back(T&& val){
		data.push_back(val);
	}
	
	/**
	 Sets all the values in the Vector to the input value
	 
	 @param value the value you want to set all the Vector values to
	 @return returns true or false, indicating if the set was successful
	 */
	bool fill(const T &value){
		
		if(size() == 0) return false;
		
		std::fill(data.begin(),data.end(),value);
		
		return true;
	}
	
	/**
	 Sets all the values in the Vector to the input value
	 
	 @param value the value you want to set all the Vector values to
	 @return returns true or false, indicating if the set was successful
	 */
	bool setAll(const T &value){
		return fill(value);
	}
	
	/**
	 Gets the size of the Vector
	 
	 @return returns the size of the Vector
	 */
	inline UINT size() const{ return static_cast<UINT>(data.size()); }
	
	/**
	 Gets a pointer to the first element in the vector
	 
	 @return returns a pointer to the raw data
	 */
	T* getData() {
		if(size() == 0) return NULL;
		return &(data)[0];
	}
	
	/**
	 Gets a pointer to the first element in the vector
	 
	 @return returns a pointer to the raw data
	 */
	const T* getData() const {
		if(size() == 0 ) return NULL;
		return &(data)[0];
	}
	
};

}

#endif //ARF_VECTOR_H

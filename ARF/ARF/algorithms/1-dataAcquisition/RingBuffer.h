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

#ifndef ARF_RINGBUFFER_H
#define ARF_RINGBUFFER_H

#include "../core/Algorithm.h"
#include "../../dataStructures/Matrix.h"
#include "../../utils/ARFException.h"
#include "../../utils/ARFConstants.h"
#include "../../utils/ARFTypedefs.h"

namespace ARF {

template <typename T>
class RingBuffer : public Algorithm {
	
private:
	Matrix<T> data;
	UINT size;
	UINT endIdx;
	UINT notificationOffset;
	UINT notificationInterval;
	UINT notificationCount;
	
public:
	
	RingBuffer(UINT numRows, UINT numColumns, UINT notificationInterval = 1,
				  UINT notificationOffset = 0) :
	size(0), endIdx(0), notificationInterval(notificationInterval),
	notificationOffset(notificationOffset), notificationCount(0){
		
		if (numRows == 0){
			throw ARFException("RingBuffer::RingBuffer() numRows should not be zero");
		}
		
		if (numColumns == 0){
			throw ARFException("RingBuffer::RingBuffer() numColumns should not be zero");
		}
		
		if (notificationInterval < 1){
			throw ARFException("RingBuffer::RingBuffer() notificationInterval should be bigger than 1");
		}
		
		if(notificationOffset < 0 || notificationOffset > numRows){
			throw ARFException("RingBuffer::RingBuffer() eventOffset should be in the range: [0,numRows]");
		}
		
		data = Matrix<Float>(numRows, numColumns);
	}
	
	/**
	 Adds the input SensorSample (i.e. a Vector<Float>) to the ring buffer and
	 outputs a SensorSample or NULL. The RingBuffer produces an output every
	 notificationInterval samples added to it
	 
	 @param sample the sample to append to the ring buffer
	 @return outputs the sample at index 'n - notificationOffset' where n is the
	 index of the last element in the RingBuffer
	 */
	Data* execute(Data* sample) override {
		
		//add the sample to the ring buffer
		addSample(*((SensorSample*) sample));
		
		//check if an output should be produced
		notificationCount++;
		if(notificationCount == notificationInterval){
			notificationCount = 0;
			
			return (Data*) getCurrentSample();
		}
		
		return nullptr;
	}
	
	bool addSample(const SensorSample &sample){
		
		//check if sample is valid
		if(sample.size() != data.getNumCols()){
			throw ARFException("RingBuffer::addSample() invalid sample size");
			return false;
		}
		
		//copy the sample into the data matrix
		for (int i = 0; i < sample.size(); i++) {
			data[endIdx][i] = sample[i];
		}
		
		//increase ring buffer size by one
		int numRows = data.getNumRows();
		if (size < numRows) {
			size++;
		}
		
		//increase endIdx by one
		endIdx++;
		if (endIdx == numRows) {
			endIdx = 0;
		}
		
		return true;
	}
	
	const SensorSample * getCurrentSample(){

		//check if there are enough samples in the buffer
		if(notificationOffset < size) {
			int eventIdx = endIdx - notificationOffset;
			if (eventIdx < 0) {
				eventIdx += data.getNumRows();
			}
			
			return new SensorSample(data[eventIdx],data.getNumCols());
		}
		return nullptr;
	}
	
	Matrix<Float>* getMatrix(int startRow, int startCol, int endRow, int endCol){
		{
			int numRows = abs(startRow - endRow);
			int numCols = abs(startCol - endCol);
			Matrix<Float> * matrix = new Matrix<Float>(numRows,numCols);
			
			return matrix;
		}
	}
	
	UINT getSize(){
		return size;
	}
	
	UINT getNotificationOffset(){
		return notificationOffset;
	}
	
	void setNotificationOffset(UINT offset){
		notificationOffset = offset;
	}
	
	SensorSample& getSampleAtRow(UINT rowIdx){
		data.getRowVector(rowIdx);
	}
};

}

#endif //ARF_RINGBUFFER_H

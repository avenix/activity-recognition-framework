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

#ifndef ARF_RING_BUFFER_ALGORITHM_H
#define ARF_RING_BUFFER_ALGORITHM_H

#include "../core/Algorithm.h"
#include "../../dataStructures/Matrix.h"
#include "../../utils/ARFException.h"
#include "../../utils/ARFConstants.h"
#include "../../utils/ARFTypedefs.h"
#include "../../dataStructures/RingBuffer.h"

namespace ARF {

class RingBufferAlgorithm : public Algorithm {
	
private:
	RingBuffer<SensorSample> * ringBuffer; ///< The ring buffer containing the data
	UINT notificationInterval; ///< The number of samples after which the RingBuffer outputs each sample
	UINT notificationOffset; ///< The amount of samples between the last sample added to the RingBuffer and the sample output
	UINT notificationCount; ///< The number of samples since the last notification
	
	/**
	 Retrieves the sample the RingBuffer should output, typically the last sample added, but can be an older sample if the notificationOffset > 0
	 
	 @return a pointer to the retrieved SensorSample
	 */
	SensorSample * getNotificationSample() const{
		
		int eventIdx = ringBuffer->getEndIdx() - notificationOffset - 1;
		if (eventIdx < 0) {
			eventIdx += ringBuffer->getCapacity();
		}
		
		return new SensorSample(ringBuffer->getElementAtIdx(eventIdx));
	}
	
public:
	/**
	 Main constructor of the ring buffer
	 
	 @param ringBuffer the pre-allocated ring buffer
	 @param notificationInterval the number of samples between notifications emitted by the ringBuffer
	 @param notificationOffset the number of samples after which the ringBuffer emits the first notification
	 */
	RingBufferAlgorithm(RingBuffer<SensorSample> * ringBuffer, UINT notificationInterval = 1,
							  UINT notificationOffset = 0) : ringBuffer(ringBuffer),
	notificationInterval(notificationInterval), notificationOffset(notificationOffset), notificationCount(0) {
		
		if (notificationInterval < 1){
			throw ARFException("RingBuffer::RingBuffer() notificationInterval should be bigger than 1");
		}
		
		if(notificationOffset < 0 || notificationOffset > ringBuffer->getCapacity()){
			throw ARFException("RingBuffer::RingBuffer() eventOffset should be in the range: [0,ringBuffer->getCapacity()]");
		}
	}
	
	/**
	 Main constructor of the ring buffer, that allocates memory for the ring buffer itself
	 
	 @param numElements the number of sensor readings the ring buffer should store
	 @param notificationInterval the number of samples between notifications emitted by the ringBuffer
	 @param notificationOffset the number of samples after which the ringBuffer emits the first notification
	 */
	RingBufferAlgorithm(UINT numElements, UINT notificationInterval = 1,
							  UINT notificationOffset = 0) :
	RingBufferAlgorithm(new RingBuffer<SensorSample>(numElements),notificationInterval,notificationOffset){
		
		if (numElements == 0){
			throw ARFException("RingBuffer::RingBuffer() numElements should not be zero");
		}
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
		addSample((SensorSample*) sample);
		
		//check if an output should be produced
		notificationCount++;
		if(notificationCount == notificationInterval){
			notificationCount = 0;
			
			//check if there are enough samples in the buffer
			if(notificationOffset < ringBuffer->getSize()) {
				
				return (Data*) getNotificationSample();
			}
		}
		
		return nullptr;
	}
	
	/**
	 Adds a sample to the ringBuffer
	 
	 @param sample the sample to append to the ring buffer
	 */
	void addSample(SensorSample *sample){
		ringBuffer->add(*sample);
	}
	
	/**
	 Retrieves the current size of the RingBuffer
	 
	 @return the size of the RingBuffer
	 */
	UINT getSize(){
		return ringBuffer->getSize();
	}
	
	/**
	 Retrieves the notificationOffset property
	 
	 @return the notificationOffset of the RingBuffer
	 */
	UINT getNotificationOffset(){
		return notificationOffset;
	}
	
	/**
	 Sets the notificationOffset property
	 
	 @param offset the new notificationOffset you want to set
	 */
	void setNotificationOffset(UINT offset){
		notificationOffset = offset;
	}
	
	/**
	 Retrieves an element from the ring buffer
	 
	 @param sampleIdx the index of the sensor sample you want
	 @return the SensorSample
	 */
	SensorSample getElementAtIdx(UINT sampleIdx) const{
		return ringBuffer->getElementAtIdx(sampleIdx);
	}
};

}

#endif //ARF_RINGBUFFER_H

#include <gtest/gtest.h>
#include "ARF.h"

using namespace ARF;


 TEST(RingBufferAlgorithm, InitialState) {
 //create a ring buffer with capacity for 10 samples
 RingBufferAlgorithm ringBuffer(10);
 
 EXPECT_EQ(ringBuffer.getSize(),0);
 }
 

TEST(RingBufferAlgorithm, Execute) {
	//default ring buffer (notificationInterval = 1 and notificationOffset = 0)
	RingBufferAlgorithm ringBufferAlgorithm(10);
	ringBufferAlgorithm.setNotifyWhenFull(false);
	
	//add a sample
	Float sampleValue = 4.5;
	SensorSample inputSample(1,sampleValue);
	SensorSample * outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample);
	
	EXPECT_EQ(ringBufferAlgorithm.getSize(),1);
	Float outputValue = (*outputSample)[0];
	EXPECT_EQ(outputValue,sampleValue);
}


TEST(RingBufferAlgorithm, NotificationInterval) {
	//create ring buffer with 10 rows and notificationInterval = 3
	RingBufferAlgorithm ringBufferAlgorithm(10,3);
	ringBufferAlgorithm.setNotifyWhenFull(false);
	
	for(int i = 1 ; i < 3 ; i++){
		SensorSample inputSample1(1,1);
		SensorSample * outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample1);
		EXPECT_EQ(outputSample,nullptr);
		
		SensorSample inputSample2(1,2);
		outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample2);
		EXPECT_EQ(outputSample,nullptr);
		
		SensorSample inputSample3(1,3);
		outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample3);
		EXPECT_EQ((*outputSample)[0],3);
	}
}


TEST(RingBufferAlgorithm, NotificationOffset) {
	//capacity = 10, notificationInterval = 1, notificationOffset = 2
	RingBufferAlgorithm ringBufferAlgorithm(10,1,2);
	ringBufferAlgorithm.setNotifyWhenFull(false);
	
	//add samples
	SensorSample inputSample1(1,1);
	SensorSample inputSample2(1,2);
	SensorSample inputSample3(1,3);
	SensorSample inputSample4(1,4);
	
	SensorSample * outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample1);
	EXPECT_EQ(outputSample,nullptr);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample2);
	EXPECT_EQ(outputSample,nullptr);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample3);
	EXPECT_EQ((*outputSample)[0],1);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample4);
	EXPECT_EQ((*outputSample)[0],2);
}

TEST(RingBufferAlgorithm, NotifyWhenFull) {
	//capacity = 10, notificationInterval = 1, notificationOffset = 2
	RingBufferAlgorithm ringBufferAlgorithm(5);
	ringBufferAlgorithm.setNotifyWhenFull(true);
	
	//add samples
	SensorSample inputSample1(1,1);
	SensorSample inputSample2(1,2);
	SensorSample inputSample3(1,3);
	SensorSample inputSample4(1,4);
	SensorSample inputSample5(1,5);
	
	SensorSample * outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample1);
	EXPECT_EQ(outputSample,nullptr);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample2);
	EXPECT_EQ(outputSample,nullptr);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample3);
	EXPECT_EQ(outputSample,nullptr);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample4);
	EXPECT_EQ(outputSample,nullptr);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample5);
	EXPECT_EQ((*outputSample)[0],5);
}


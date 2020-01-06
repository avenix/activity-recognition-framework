#include <gtest/gtest.h>
#include "ARF.h"

using namespace ARF;


TEST(RingBufferAlgorithm, InitialState) {
	//create a ring buffer with capacity for 10 samples
	RingBufferAlgorithm ringBuffer(10);
	
	EXPECT_EQ(0, ringBuffer.getSize());
}

TEST(RingBufferAlgorithm, Execute) {
	//default ring buffer (notificationInterval = 1 and notificationOffset = 0)
	RingBufferAlgorithm ringBufferAlgorithm(10);
	
	//add a sample
	Float sampleValue = 4.5;
	SensorSample inputSample(1,sampleValue);
	SensorSample * outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample);
	
	EXPECT_EQ(1, ringBufferAlgorithm.getSize());
	EXPECT_EQ(sampleValue, (*outputSample)[0]);
}


TEST(RingBufferAlgorithm, NotificationInterval) {
	//create ring buffer with 10 rows, 1 column and notificationInterval = 3
	RingBufferAlgorithm ringBufferAlgorithm(10,3);
	
	for(int i = 1 ; i < 3 ; i++){
		SensorSample inputSample1(1,1);
		SensorSample * outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample1);
		EXPECT_EQ(nullptr, outputSample);
		
		SensorSample inputSample2(1,2);
		outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample2);
		EXPECT_EQ(nullptr, outputSample);
		
		SensorSample inputSample3(1,3);
		outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample3);
		EXPECT_EQ(3, (*outputSample)[0]);
	}
}

TEST(RingBufferAlgorithm, NotificationOffset) {
	//capacity = 10, notificationInterval = 1, notificationOffset = 2
	RingBufferAlgorithm ringBufferAlgorithm(10,1,2);
	
	//add a sample
	SensorSample inputSample1(1,1);
	SensorSample inputSample2(1,2);
	SensorSample inputSample3(1,3);
	SensorSample inputSample4(1,4);
	
	SensorSample * outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample1);
	EXPECT_EQ(nullptr, outputSample);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample2);
	EXPECT_EQ(nullptr, outputSample);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample3);
	EXPECT_EQ(1, (*outputSample)[0]);
	
	outputSample = (SensorSample*) ringBufferAlgorithm.execute(&inputSample4);
	EXPECT_EQ(2, (*outputSample)[0]);
}

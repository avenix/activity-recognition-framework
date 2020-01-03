#include <gtest/gtest.h>
#include "ARF.h"

using namespace ARF;

TEST(RingBuffer, InitialState) {
	//default ring buffer with notification interval = 1
	RingBuffer<Float> ringBuffer(10,1);
	
	//add a sample
	SensorSample sample(1);
	ringBuffer.addSample(sample);
	
	//get the current sample
	const SensorSample * currentSample = ringBuffer.getCurrentSample();
	
	EXPECT_EQ(1, (*currentSample)[0]);
}

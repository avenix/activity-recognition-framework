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
*/

#include <gtest/gtest.h>
#include "ARF.h"

using namespace ARF;


TEST(RingBuffer, InitialState) {
	//create a ring buffer with capacity for 10 samples
	RingBuffer<int> ringBuffer(10);
	
	EXPECT_EQ(0, ringBuffer.getSize());
}

TEST(RingBuffer, AddSample) {
	//default ring buffer (notificationInterval = 1 and notificationOffset = 0)
	RingBuffer<float> ringBuffer(10);
	
	//add a sample
	float sampleValue = 4.5;
	ringBuffer.add(sampleValue);
	
	//get the current sample
	float outputValue = ringBuffer.getFirstElement();
	
	EXPECT_EQ(1, ringBuffer.getSize());
	EXPECT_EQ(sampleValue, outputValue);
}


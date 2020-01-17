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

TEST(DataSelector, SelectSingleElement) {
	//create a ring buffer with capacity for 10 samples
	RingBuffer<SensorSample> ringBuffer(10);
	
	//add samples
	SensorSample sample0 = SensorSample(std::vector<float>{1.0,2.0,3.0});
	SensorSample sample1 = SensorSample(std::vector<float>{4.0,5.0,6.0});
	ringBuffer.add(sample0);
	ringBuffer.add(sample1);
	
	//startRow = 0, endRow = 0, columns = {0} (selects only 1 element)
	Vector<uint8_t> columns(1,0);
	auto dataSelector = DataSelector(&ringBuffer,0,0,columns);
	
	//get the DataIterator
	DataIterator * iterator = (DataIterator*) dataSelector.execute(nullptr);
	
	//test the first element can be accessed
	EXPECT_EQ(1.0, iterator->getDataAtIdx(0));
	EXPECT_EQ(1.0, (*iterator)[0]);//test also the equivalent operator
	
	//test that other elements cannot be accessed
	EXPECT_THROW(iterator->getDataAtIdx(2),ARFException);
	EXPECT_THROW(iterator->getDataAtIdx(1),ARFException);
}

TEST(DataSelector, SelectMultipleElements) {
	//create a ring buffer with capacity for 10 samples
	RingBuffer<SensorSample> ringBuffer(10);
	
	//add samples
	SensorSample sample0 = SensorSample(std::vector<float>{1.0,2.0,3.0});
	SensorSample sample1 = SensorSample(std::vector<float>{4.0,5.0,6.0});
	SensorSample sample2 = SensorSample(std::vector<float>{7.0,8.0,9.0});
	ringBuffer.add(sample0);
	ringBuffer.add(sample1);
	ringBuffer.add(sample2);
	
	//select columns 0 and 1
	Vector<uint8_t> columns(2,0);
	columns[0] = 0;
	columns[1] = 1;
	
	//select sample1 and sample2. Results in a matrix: [4,5;7,8]
	auto dataSelector = DataSelector(&ringBuffer,1,2,columns);
	
	//get the DataIterator
	DataIterator& iterator = *((DataIterator*) dataSelector.execute(nullptr));
	EXPECT_EQ(iterator(0,0),4.0);
	EXPECT_EQ(iterator(0,1),5.0);
	EXPECT_EQ(iterator(1,0),7.0);
	EXPECT_EQ(iterator(1,1),8.0);
	EXPECT_THROW(iterator(1,2),ARFException);
	EXPECT_THROW(iterator(1,2),ARFException);
}


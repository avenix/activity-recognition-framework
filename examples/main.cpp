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

#include <iostream>
#include <vector>

#include "ARF.h"
#include "DataSet.h"

using namespace ARF;

int main(int argc, const char * argv[]) {
	
	//instantiate algorithms
	auto ringBuffer = RingBuffer<SensorSample>(301);
	//auto ringBufferAlgorithm = RingBufferAlgorithm(&ringBuffer,301,1,201);
	auto ringBufferAlgorithm = RingBufferAlgorithm(&ringBuffer,2);
	//auto sampleSelector = DataSelector<SensorSample>(&ringBuffer,1,1);//startIdx = 0, nSamples = 1
	auto columnIndices = std::vector<uint8_t>{2};
	auto elementSelector = DataSelector(&ringBuffer,1,1,columnIndices);//startIdx = 0, nSamples = 1
	//auto magnitude = Magnitude();
	//auto peakDetector = new PeakDetector(0.8, 100);
	
	//build pipeline
	ringBufferAlgorithm << elementSelector;
	
	//execute pipeline
	SensorSample data = SensorSample(std::vector<float>{1.0,2.0,3.0});
	SensorSample data2 = SensorSample(std::vector<float>{4.0,5.0,6.0});
	
	//DataSet dataSet(16,"GoalkeeperDataSet","9-axis IMU data + linear acceleration + quaternion");
	//dataSet.load("../data/S1.txt");
	
	Algorithm::ExecutePipeline(&ringBufferAlgorithm,&data);
	DataIterator2D * output = (DataIterator2D *) Algorithm::ExecutePipeline(&ringBufferAlgorithm,&data2);
	Float sample = (*output)(0,0);
	
	//will return a sample
	std::cout << sample << std::endl;
	
	return 0;
}

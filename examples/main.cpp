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

#include <iostream>
using namespace std;

using namespace ARF;

int main(int argc, const char * argv[]) {
	
	//ring buffer able to hold 301 elements
	auto ringBuffer = RingBuffer<SensorSample>(301);
	auto ringBufferAlgorithm = RingBufferAlgorithm(&ringBuffer);//1,201

	//select ax,ay,az
	auto columnIndices = Vector<uint8_t>(3,0);
	columnIndices[1] = 1;
	columnIndices[2] = 2;
	auto dataSelector = DataSelector(&ringBuffer,0,0,columnIndices);

	//magnitude of ax,ay,az
	auto magnitude = Magnitude();
	
	//auto peakDetector = new PeakDetector(0.8, 100);
	
	//build pipeline
	ringBufferAlgorithm << dataSelector << magnitude;
	
	//execute pipeline
	//SensorSample sample1 = SensorSample(std::vector<float>{1.0,2.0,3.0});
	//SensorSample sample2 = SensorSample(std::vector<float>{4.0,5.0,6.0});
	
	//load some data
	DataSet dataset = DataSet("data2.txt",true);
	
	//execute algorithm for each sample
	for(int i = 0 ; i < dataset.getNumSamples() ; i++){
		
		SensorSample sample = dataset[i];
		auto output = (Value *) Algorithm::ExecutePipeline(&ringBufferAlgorithm,&sample);
		
		std::cout << output->getValue() << std::endl;
	}
	
	return 0;
}

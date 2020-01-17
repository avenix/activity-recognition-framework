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

using namespace std;
using namespace ARF;

void printRingBuffer(const RingBuffer<SensorSample> &ringBuffer){
	for(int i = 0 ; i < ringBuffer.getSize() ; i++){
		SensorSample sample = ringBuffer[i];
		for(int j = 0 ; j < 6 ; j++){
			cout << sample[j] << " ";
		}
		cout << endl;
	}
}

void printDataWithIterator(const DataIterator &dataIterator){
	for(int i = 0 ; i < dataIterator.getNumRows(); i++){
		for(int j = 0 ; j < dataIterator.getNumColumns(); j++){
			cout << dataIterator(i,j) << " ";
		}
		cout << endl;
	}
}

int main(int argc, const char * argv[]) {
	
	//ring buffer able to hold 301 elements
	RingBuffer<SensorSample> ringBuffer(301);
	RingBufferAlgorithm ringBufferAlgorithm(&ringBuffer);

	//select ax,ay,az of the last sample in the ring buffer
	//auto accelColumns = Vector<uint8_t>();
	DataSelector accelSelector(&ringBuffer,300,300,{0,1,2});

	//magnitude of ax,ay,az
	Magnitude magnitude;
	
	//minPeakHeight = 0.8, minPeakDistance = 100
	PeakDetector peakDetector(0.8, 100);
	
	//ax signal in segment 60-150
	DataSelector midAxSelector(&ringBuffer,60,150,{0});
	DataSelector midAzSelector(&ringBuffer,60,150,{2});
	DataSelector rightAySelector(&ringBuffer,180,230,{1});
	
	//feature extraction algorithms
	Mean mean;
	STD std;
	ZCR zcr;
	
	//build pipeline
	ringBufferAlgorithm << accelSelector << magnitude << peakDetector;

	//peakDetector << midAxSelector << mean;
	//peakDetector << midAzSelector << mean;
	peakDetector << midAzSelector << std;
	//peakDetector << rightAySelector << zcr;
	
	//load some data
	DataSet dataset = DataSet("test.arf",true);
	//DataSet dataset = DataSet("test.txt",true);
	//dataset.save("1-niklas.arf");
	
	//execute algorithm for each sample
	Vector<Data*> output(4);
	for(int i = 0 ; i < dataset.getNumSamples() ; i++){
		
		SensorSample sample = dataset[i];
		UINT outputCount = Algorithm::ExecutePipeline(&ringBufferAlgorithm,&sample,output);
			//printRingBuffer(ringBuffer);
			//printDataWithIterator(*output);
		
		for(int i = 0 ; i < outputCount ; i++){
			std::cout << ((Value*)output[i])->getValue() << std::endl;
		}
		
		if(outputCount > 0)
			break;
	}
	
	return 0;
}

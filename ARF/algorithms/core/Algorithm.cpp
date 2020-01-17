/**
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

#include <stack>
#include "Algorithm.h"
#include "ARFTypedefs.h"
#include "../../dataStructures/DataIterator.h"
#include "../../dataStructures/Data.h"

namespace ARF {

typedef std::shared_ptr<Data> SharedDataPtr;

const Vector<Algorithm*> & Algorithm::getNextAlgorithms() const{
	return nextAlgorithms;
}

void Algorithm::addAlgorithm(Algorithm * algorithm){
	nextAlgorithms.push_back(algorithm);
}

Algorithm& Algorithm::operator<<(Algorithm &algorithm){
	addAlgorithm(&algorithm);
	return algorithm;
}

Algorithm& Algorithm::operator<<(Algorithm &&algorithm){
	addAlgorithm(&algorithm);
	return algorithm;
}

UINT Algorithm::ExecutePipeline(Algorithm * root, Data * inputData, Vector<Data*> & outputVector) {
	std::stack<Algorithm*> algorithmStack;
	std::stack<SharedDataPtr> dataStack;
	
	//add first algorithm to algorithm stack
	algorithmStack.push(root);
	
	//add input data to data stack
	Data * input = inputData->clone();
	dataStack.push(SharedDataPtr(input));
	
	UINT outputCount = 0;
	
	while (!algorithmStack.empty()) {
		
		//get top algorithm and remove it from the stack
		root = algorithmStack.top();
		algorithmStack.pop();
		
		//get top data and remove it from the stack
		SharedDataPtr inputDataPtr = dataStack.top();
		Data * input = inputDataPtr.get();
		dataStack.pop();
		
		//execute algorithm
		Data * output = root->execute(input);
		
		//finish if the current algorithm did not produce an output
		if(output == nullptr) break;
		
		//reuse shared pointer if the same input was returned
		SharedDataPtr outputDataPtr;
		if(input == output){
			outputDataPtr = inputDataPtr;
		} else {
			outputDataPtr = SharedDataPtr(output);
		}
		
		Vector<Algorithm*> nextAlgorithms = root->getNextAlgorithms();
		if(nextAlgorithms.empty()){
			outputVector[outputCount++] = output->clone();
		} else {
			//push next algorithms to the stack backwards
			for (int i = nextAlgorithms.getSize()-1 ; i >= 0 ; i--){
				Algorithm * algorithm = nextAlgorithms[i];
				algorithmStack.push(algorithm);
				dataStack.push(outputDataPtr);
			}
		}
	}
	return outputCount;
	
}

}

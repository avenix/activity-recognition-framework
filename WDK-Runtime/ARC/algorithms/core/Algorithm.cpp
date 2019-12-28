/**
@file
@author  Juan Haladjian <juan.haladjian@gmail.com>

ARC MIT License
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

@brief This is the main ARC header. You should include this to access all the ARC classes in your project.
*/

#include <stack>
#include "Algorithm.h"
#include "../../data/DataAccessObject.h"

typedef std::shared_ptr<Data> SharedDataPtr;

/*
void Algorithm::operator<<(Computer * computer){
	nextComputers.push_back(computer);
	}
*/

const std::vector<Algorithm*> & Algorithm::getNextAlgorithms() const{
	return nextAlgorithms;
}

Data * Algorithm::ExecuteAlgorithm(Algorithm * root, Data* data) {
    std::stack<Algorithm*> executionStack;
    std::stack<SharedDataPtr> dataStack;
    executionStack.push(root);
    dataStack.push(SharedDataPtr(data));

    while (!executionStack.empty()) {
        root = executionStack.top();
        executionStack.pop();

        SharedDataPtr inputDataPtr = dataStack.top();
        dataStack.pop();
		 
        Data * input = inputDataPtr.get();
        Data * output =  root->execute(input);

		 const std::vector<Algorithm*> & nextAlgorithms = root->getNextAlgorithms();
		 
        if (nextAlgorithms.empty()) {
            DataAccessObject* dataAccessObject = (DataAccessObject*) input;
            dataAccessObject->resetIteratorIndex();
            //return output;
        }
        if (output) {
            SharedDataPtr outputDataPtr;
            if(input == output){
                outputDataPtr = inputDataPtr;
            } else {
                outputDataPtr = SharedDataPtr(output);
            }

            for (Algorithm* nextAlgorithm : nextAlgorithms) {
                executionStack.push(nextAlgorithm);
                dataStack.push(outputDataPtr);
            }
        } else {
            return nullptr;
        }
    }

    return data;
}

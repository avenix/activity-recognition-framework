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

#include "RingBuffer.h"
#include "../../data/Matrix.h"

RingBuffer::RingBuffer(int numRows, int numColumns) : numRows{numRows}, numColumns{numColumns} {
    dataMatrix = new Matrix(numRows, numColumns);
    endIdx = 0;
}

/**
    Receives a sample and stores it in a Matrix

    @param sample The current sample
    @return The current sample of the sample located at eventIdx.
*/
Data* RingBuffer::execute(Data* sample) {
    auto sampleMatrix = (Matrix*) sample;
    Matrix* outputMatrix = sampleMatrix;

    addSample(sampleMatrix);

    if (size < numRows) {
        size++;
    }

    if(eventOffset < size) {
        int eventIdx = endIdx - eventOffset;
        if (eventIdx < 0) {
            eventIdx += numRows;
        }

        for (int i = 0; i < numColumns; i++) {
            outputMatrix->data[0][i] = dataMatrix->data[eventIdx][i];
        }
    }

    endIdx++;

    if (endIdx >= numRows) {
        endIdx = 0;
    }

    return outputMatrix;
}

/**
    Adds a sample to the endIdx of the RingBuffer

    @param sample The current sample
*/
void RingBuffer::addSample(Matrix* sample) {
    for (int i = 0; i < sample->getColumns(); i++) {
        dataMatrix->data[endIdx][i] = sample->get2DFloatMatrix()[0][i];
    }
}

float RingBuffer::get(int row, int col){
    /*
    int startIdx = endIdx - size;
    if(rowIdx < 0) rowIdx += size;
    return dataMatrix->get(rowIdx,col);*/
	return 0;
}

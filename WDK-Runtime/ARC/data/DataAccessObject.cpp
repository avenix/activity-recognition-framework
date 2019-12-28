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

#include "DataAccessObject.h"

DataAccessObject::DataAccessObject(int startRow, int endRow): startRow{startRow}, endRow{endRow} { }

void DataAccessObject::updateSelection(int newStartRow, int newEndRow) {
    startRow += newStartRow;
    endRow = startRow + newEndRow;
    /*
    updatedStartRow = startRow + newStartRow;
    int size = newEndRow - newStartRow;
    updatedEndRow = (startRow + size) % ringBuffer->numRows;*/
}

void DataAccessObject::setAxesIndices(std::vector<int> newAxesIndices) {
    axesIndices = (std::move(newAxesIndices));
}

int DataAccessObject::getNumberOfElements() {

    return endRow - startRow + 1;
    /*
    if (startRow < updatedEndRow) {
        return endRow - updatedStartRow + 1;
    } else {
        return (ringBuffer->numRows - updatedStartRow) + updatedEndRow + 1;
    }*/
}

bool DataAccessObject::hasNext() {
    return iteratorIndex < getNumberOfElements();
}

float DataAccessObject::next() {
    iteratorIndex++;
    return ringBuffer->get(startRow + iteratorIndex, axesIndices.at(0));
}

void DataAccessObject::resetIteratorIndex() {
    iteratorIndex = 0;
}

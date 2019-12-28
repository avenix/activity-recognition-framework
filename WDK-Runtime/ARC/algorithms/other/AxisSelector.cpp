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

#include "AxisSelector.h"

AxisSelector::AxisSelector(int nAxes, const std::vector<int> &axesIndices): nAxes{nAxes}, axesIndices{axesIndices} {
}

/**
    Selects the axes of a sample or of multiple rows of a matrix.

    @param data A DataAccessObject or sample
    @return The DataAccessObject with updates axes or the RingBuffer with an updated axes selection
*/
Data* AxisSelector::execute(Data* data) {
    if (DataAccessObject* dataAccessObject = dynamic_cast<DataAccessObject*>(data)) {
        dataAccessObject->setAxesIndices(axesIndices);
        return dataAccessObject;
    }

    if (!ringBuffer->axesIndices.empty()) {
        ringBuffer->axesIndices.clear();
    }

    ringBuffer->axesIndices = axesIndices;

    return data;
}

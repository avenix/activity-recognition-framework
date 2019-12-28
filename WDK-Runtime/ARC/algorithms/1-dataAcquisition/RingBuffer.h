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

#ifndef ARC_RINGBUFFER_H
#define ARC_RINGBUFFER_H

#include "../core/Algorithm.h"
#include "Matrix.h"

struct RowRange {
    int start;
    int end;
};

class RingBuffer : public Algorithm {
private:
    int size = 0;
    void addSample(Matrix* sample);
    Matrix* dataMatrix;

public:
    int endIdx;
    int numRows;
    int numColumns;

    int eventOffset = 0;

    RowRange* rowRange;
    std::vector<int> axesIndices;

    RingBuffer(int nunRows, int numCols);

    Data* execute(Data* sample) override;
    float get(int row, int col);
};

#endif //ARC_RINGBUFFER_H

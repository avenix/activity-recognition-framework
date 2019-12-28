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

#include "FixedSegmentation.h"
#include "../../data/Data.h"

FixedSegmentation::FixedSegmentation(int left, int right, int minPeakDistance) :
        left{left}, right{right}, minPeakDistance{minPeakDistance} {}

/**
    Computes a segment based on the found peak

    @param data The current sameple which was detected as a peak.
    @return A new DataAccessObject which contains indices for the computed segment
*/
Data* FixedSegmentation::execute(Data* data){
    /*
    int segmentSize = left + right;

    int peakIndex;
    if (ringBuffer->endIdx < minPeakDistance) {
        int diff = minPeakDistance - ringBuffer->endIdx;
        peakIndex = ringBuffer->numRows - diff;
    } else {
        peakIndex = ringBuffer->endIdx - minPeakDistance;
    }

    int segmentStartIndex = peakIndex - left;
    if (segmentStartIndex < 0) {
        segmentStartIndex = ringBuffer->numRows + segmentStartIndex;
    }
    int segmentEndIndex = segmentStartIndex + segmentSize;
    if (segmentEndIndex > ringBuffer->numRows) {
        segmentEndIndex = segmentEndIndex - ringBuffer->numRows;
    }
*/
    int offset = ringBuffer->eventOffset;
    // double-check this line
    DataAccessObject* segmentDAO = new DataAccessObject(-left - right, 0);

    return segmentDAO;
}

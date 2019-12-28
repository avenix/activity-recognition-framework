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

#include "Magnitude.h"
#include "../../data/Value.h"
#include "../../data/Data.h"
#include "../../data/Matrix.h"
#include <cmath>

/**
    Computes the magnitude of a sample with 3 axes

    @param data A sample read from the sensors
    @return A Matrix containing the magnitude in position 0, 0
*/
Data* Magnitude::execute(Data* data) {
    auto matrix = (Matrix*) data;
    Matrix* magnitudeMatrix = new Matrix(1, 1);

    float rowResult = (matrix->data[0][0] * matrix->data[0][0]) + (matrix->data[0][1] * matrix->data[0][1]) + (matrix->data[0][2] * matrix->data[0][2]);;
    magnitudeMatrix->put(0, 0, sqrt(rowResult));
    return magnitudeMatrix;
}

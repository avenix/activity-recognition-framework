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

#include <printf.h>
#include "Matrix.h"

Matrix::Matrix(int rows, int columns): rows(rows), columns(columns) {
    auto matrix = new float*[rows];
    for(int i = 0 ; i < rows ; i++){
        matrix[i] = new float[columns];
    }
    data = matrix;
}

float** Matrix::get2DFloatMatrix() {
    return data;
}

float Matrix::get(int row, int col) {
    if (row >= rows || col >= columns) {
        // Error
        printf("[Error]: Matrix index out of bounds");
        return -1;
    }

//    int rowIdx = star
    return data[row][col];
}

void Matrix::put(int row, int col, float value) {
    data[row][col] = value;
}

int Matrix::getRows() {
    return rows;
}

int Matrix::getColumns() {
    return columns;
}

void Matrix::printValues() {
    for (int i = 0; i < rows; i++) {
        //for (int j = 0; j < columns; j++) {
            printf("Value [%d]: %f\n", i, data[i][0]);
        //}
    }
}

float** Matrix::clone() {
    float** values = new float*[rows];

    for (int i = 0; i < rows; i++) {
        values[i] = new float[columns];
        for (int j = 0; j < columns; j++) {
            values[i][j] = get2DFloatMatrix()[i][j];
        }
    }
    return values;
}

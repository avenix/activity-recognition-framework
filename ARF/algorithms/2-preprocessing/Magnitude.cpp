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

#include "Magnitude.h"
#include "../../dataStructures/Value.h"
#include "../../dataStructures/Data.h"
#include "../../dataStructures/Matrix.h"
#include <cmath>

namespace ARF {

/**
 Computes the magnitude of a sample with 3 axes
 
 @param data A vector of floats with exactly three components
 @return The magnitude of the input vector
 */
Data* Magnitude::execute(Data * data) {
	Signal * signal = (Signal*) data;
	auto val = (*signal)[0];
	
	Float result = std::sqrt((*signal)[0] * (*signal)[1] * (*signal)[2]);
	
	return new Value(result);
}

}

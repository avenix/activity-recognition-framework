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

#include "STD.h"
#include "../../dataStructures/Value.h"
#include "DataIterator.h"
#include "Mean.h"
#include <math.h>

namespace ARF {

Data* STD::execute(Data * data) {
	
	const Signal &signal = *(Signal*) data;
	
	Mean meanComputer;
	Value * output = (Value*) meanComputer.execute(data);
	Float mean = output->getValue();
	
	UINT n = signal.getSize();
	
	Float accum = 0.0;
	for(int i = 0 ; i < n ; i++){
		Float diff = signal[i] - mean;
		accum = diff * diff;
	}

	Float stdev = sqrt(accum / float(n-1));
	output->setValue(stdev);
	return output;
}

}

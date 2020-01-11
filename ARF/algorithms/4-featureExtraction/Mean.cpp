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

#include "Mean.h"
#include "../../dataStructures/Vector.h"
#include "../../dataStructures/Value.h"

namespace ARF {

/**
 Returns the mean for the currently selected data that is provided by the DAO.
 
 @param data A DataAccessObject containing an iterator
 @return The mean for the currently selected data
 */
Data* Mean::execute(Data * data) {
	Signal * signal = (Signal*) data;
	unsigned int n = signal->getSize();
	
	float sum = 0.0;
	
	for(int i = 0 ; i < n ; i++)
		sum += (*signal)[i];
	
	float mean = sum / (float)n;
	
	return new Value(mean);
}

}

/**
 @file
 @author  Juan Haladjian <juan.haladjian@gmail.com>
 @brief The Algorithm is the superclass of every algorithm available in the ARF. The Algorithm is a recursive data structure. It has an array of pointers to other algorithms, forming a directed graph. Every algorithm subclass implements the execute() method that receives and outputs a pointer to an instance of the Data class. The static method Algorithm::ExecutePipeline() traverses the entire graph invoking the execute() method of every algorithm, passing the Data produced an algorithm to the next algorithm.
 
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

#ifndef ARF_ALGORITHM_H
#define ARF_ALGORITHM_H

#include "../../dataStructures/Data.h"
#include "../../dataStructures/Vector.h"

namespace ARF {

class Algorithm {
private:
	Vector<Algorithm*> nextAlgorithms; ///< The Algorithms pointed at by this Algorithm instance
	
public:
	
	/**
	Executes the main function of this algorithm
	
	@param data the data used as input to this algorithm
	@return the output of this algorithm, or a NULL pointer if the algorithm does not return any output
	*/
	virtual Data* execute(Data* data) = 0;
	
	/**
	Virtual destructor of this algorithm
	*/
	virtual ~Algorithm(){ };
	
	/**
	Retrieves the list of algorithms pointedby this algorithm
	
	@return a vector of pointers to Algorithm instances
	*/
	const Vector<Algorithm*> & getNextAlgorithms() const;
	
	/**
	Makes this algorithm point to the algorithm passed as a parameter
	
	@param algorithm the algorithm this algorithm instance should point to
	*/
	void addAlgorithm(Algorithm * algorithm);
	
	/**
	Makes this algorithm point to the algorithm passed as a parameter
	
	@param algorithm the algorithm this algorithm instance should point to
	@return returns a pointer to the current algorithm so that several << operators can be concatenated in the same line
	*/
	Algorithm& operator<<(Algorithm &algorithm);
	
	/**
	Makes this algorithm point to the algorithm passed as a parameter
	
	@param algorithm the algorithm this algorithm instance should point to
	@return returns a pointer to the current algorithm so that several << operators can be concatenated in the same line
	*/
	Algorithm& operator<<(Algorithm &&algorithm);
	
	/**
	Performs a depth-first traversal of the directed graph that as a root the input algorithm. It invokes the execute() method of every algorithm passing as input the pointer to the data instance output by the previous algorithm's execute() method
	
	@param algorithm the root of the directed graph
	@param data the input data 	
	@param output the data produced by the leaf algorithms in the graph
	@return the number of results in the output vector
	*/
	static UINT ExecutePipeline(Algorithm * algorithm, Data * data, Vector<Data*> & output);
};

}

#endif //ARF_ALGORITHM_H

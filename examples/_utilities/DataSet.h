/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>
 */

/**
 GRT MIT License
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>
 
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

#ifndef ARF_DATA_SET_H
#define ARF_DATA_SET_H

#include <string>
#include "utils/ARFTypedefs.h"
#include "dataStructures/Vector.h"

class DataSet{
public:
	
	/**
	 Constructor, sets the name of the dataset and the number of dimensions of the training data.
	 The name of the dataset should not contain any spaces.
	 
	 @param numDimensions the number of dimensions of the training data, should be an unsigned integer greater than 0
	 @param datasetName the name of the dataset, should not contain any spaces
	 @param infoText some info about the data in this dataset, this can contain spaces
	 */
	DataSet(const ARF::UINT numDimensions, const std::string & datasetName, const std::string & infoText);
	
	/**
	 Copy Constructor, copies the ClassificationData from the rhs instance to this instance
	 @param rhs another instance of the ClassificationData class from which the data will be copied to this instance
	 */
	DataSet(const DataSet &rhs);
	
	/**
	 Default Destructor
	 */
	virtual ~DataSet();
	
	/**
	 Sets the equals operator, copies the data from the rhs instance to this instance
	 
	 @param rhs another instance of the ClassificationData class from which the data will be copied to this instance
	 @return a reference to this instance of ClassificationData
	 */
	DataSet& operator=(const DataSet &rhs);
	
	/**
	 Saves the classification data to a file.
	 If the file format ends in '.csv' then the data will be saved as comma-seperated-values, otherwise it will be saved
	 to a custom GRT file (which contains the csv data with an additional header).
	 
	 @param filename the name of the file the data will be saved to
	 @return true if the data was saved successfully, false otherwise
	 */
	bool save(const std::string &filename) const;
	
	/**
	 Load the classification data from a file.
	 If the file format ends in '.csv' then the function will try and load the data from a csv format.  If this fails then it will
	 try and load the data as a custom GRT file.
	 
	 @param filename the name of the file the data will be loaded from
	 @return true if the data was loaded successfully, false otherwise
	 */
	bool load(const std::string &filename);
	
	/**
	 Saves the labelled classification data to a custom file format.
	 
	 @param filename the name of the file the data will be saved to
	 @return true if the data was saved successfully, false otherwise
	 */
	bool saveDatasetToFile(const std::string &filename) const;
	
	/**
	 Loads the labelled classification data from a custom file format.
	 
	 @param filename the name of the file the data will be loaded from
	 @return true if the data was loaded successfully, false otherwise
	 */
	bool loadDatasetFromFile(const std::string &filename);
	
	/**
	 Saves the labelled classification data to a CSV file.
	 This will save the class label as the first column and the sample data as the following N columns, where N is the number of dimensions in the data.  Each row will represent a sample.
	 
	 @param filename the name of the file the data will be saved to
	 @return true if the data was saved successfully, false otherwise
	 */
	bool saveDatasetToCSVFile(const std::string &filename) const;
	
	/**
	 Loads the labelled classification data from a CSV file.
	 This assumes the data is formatted with each row representing a sample.
	 The class label should be the first column followed by the sample data as the following N columns, where N is the number of dimensions in the data.
	 If the class label is not the first column, you should set the 2nd argument (UINT classLabelColumnIndex) to the column index that contains the class label.
	 
	 @param filename the name of the file the data will be loaded from
	 @param classLabelColumnIndex the index of the column containing the class label. Default value = 0
	 @return true if the data was loaded successfully, false otherwise
	 */
	bool loadDatasetFromCSVFile(const std::string &filename,const ARF::UINT classLabelColumnIndex = 0);
	
	/**
	 Prints the dataset info (such as its name and infoText) and the stats (such as the number of examples, number of dimensions, number of classes, etc.)
	 to the std out.
	 
	 @return returns true if the dataset info and stats were printed successfully, false otherwise
	 */
	bool printStats() const;
	
	/**
	 Gets the name of the dataset.
	 
	 @return returns the name of the dataset
	 */
	std::string getDatasetName() const{ return datasetName; }
	
	/**
	 Gets the infotext for the dataset
	 
	 @return returns the infotext of the dataset
	 */
	std::string getInfoText() const{ return infoText; }
	
	/**
	 Gets the stats of the dataset as a string
	 
	 @return returns the stats of this dataset as a string
	 */
	std::string getStatsAsString() const;
	
	/**
	 Gets the number of dimensions of the labelled classification data.
	 
	 @return an unsigned int representing the number of dimensions in the classification data
	 */
	ARF::UINT inline getNumDimensions() const{ return numDimensions; }
	
	/**
	 Gets the number of samples in the classification data across all the classes.
	 
	 @return an unsigned int representing the total number of samples in the classification data
	 */
	ARF::UINT inline getNumSamples() const{ return totalNumSamples; }
	
	/**
	 Clears any previous training data and counters
	 */
	void clear();
	
	/**
	 Sets the number of dimensions in the training data.
	 This should be an unsigned integer greater than zero.
	 This will clear any previous training data and counters.
	 This function needs to be called before any new samples can be added to the dataset, unless the numDimensions variable was set in the
	 constructor or some data was already loaded from a file
	 
	 @param numDimensions the number of dimensions of the training data.  Must be an unsigned integer greater than zero
	 @return true if the number of dimensions was correctly updated, false otherwise
	 */
	bool setNumDimensions(ARF::UINT numDimensions);
	
	/**
	 Sets the name of the dataset.
	 There should not be any spaces in the name.
	 Will return true if the name is set, or false otherwise.
	 
	 @return returns true if the name is set, or false otherwise
	 */
	bool setDatasetName(const std::string & datasetName);
	
	/**
	 Sets the info string.
	 This can be any string with information about how the training data was recorded for example.
	 
	 @param infoText the infoText
	 @return true if the infoText was correctly updated, false otherwise
	 */
	bool setInfoText(const std::string &infoText);
	
private:
	std::string datasetName;   ///< The name of the dataset
	std::string infoText;        ///< Some infoText about the dataset
	ARF::UINT numDimensions;		///< The number of dimensions in the dataset
	ARF::UINT totalNumSamples;     ///< The total number of samples in the dataset
	ARF::Vector<ARF::SensorSample> data;  ///< The actual data
};

#endif //ARF_DATA_SET_H

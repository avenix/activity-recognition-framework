/*
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

#include <fstream>

#include "ARF.h"
#include "DataSet.h"
#include "Util.h"
#include "FileParser.h"

DataSet::DataSet(const ARF::UINT numDimensions, const std::string & datasetName, const std::string & infoText) : datasetName(datasetName),numDimensions(numDimensions), infoText(infoText), totalNumSamples(0){
	
	if(numDimensions > 0) {
		setNumDimensions(numDimensions);
	}
}

DataSet::DataSet(const DataSet &rhs){
	*this = rhs;
}

DataSet::~DataSet(){
}

DataSet& DataSet::operator=(const DataSet &rhs){
	if( this != &rhs){
		datasetName = rhs.datasetName;
		infoText = rhs.infoText;
		numDimensions = rhs.numDimensions;
		totalNumSamples = rhs.totalNumSamples;
		
		data = rhs.data;
	}
	return *this;
}

void DataSet::clear(){
	totalNumSamples = 0;
	data.clear();
}

bool DataSet::setNumDimensions(const ARF::UINT numDimensions){
	
	if( numDimensions > 0 ){
		//Clear any previous training data
		clear();
		
		//Set the dimensionality of the data
		this->numDimensions = numDimensions;
		
		return true;
	}
	
	throw ARF::ARFException("setNumDimensions(const UINT numDimensions) - The number of dimensions of the dataset must be greater than zero!");
	return false;
}

bool DataSet::setDatasetName(const std::string &datasetName){
	
	//Make sure there are no spaces in the std::string
	if( datasetName.find(" ") == std::string::npos ){
		this->datasetName = datasetName;
		return true;
	}
	
	throw ARF::ARFException("setDatasetName(const std::string datasetName) - The dataset name cannot contain any spaces!");
	return false;
}

bool DataSet::setInfoText(const std::string &rhs){
	infoText = rhs;
	return true;
}

bool DataSet::save(const std::string &filename) const{
	
	//Check if the file should be saved as a csv file
	if(Util::stringEndsWith(filename, ".csv")){
		return saveDatasetToCSVFile(filename);
	}
	
	//Otherwise save it as a custom GRT file
	return saveDatasetToFile( filename );
}

bool DataSet::load(const std::string &filename){
	
	//Check if the file should be loaded as a csv file
	if(Util::stringEndsWith( filename, ".csv")){
		return loadDatasetFromCSVFile( filename );
	}
	
	//Otherwise save it as a custom GRT file
	return loadDatasetFromFile(filename);
}

bool DataSet::saveDatasetToFile(const std::string &filename) const{
	
	std::fstream file;
	file.open(filename.c_str(), std::ios::out);
	
	if( !file.is_open() ){
		return false;
	}
	
	file << "DATA_FILE_V1.0\n";
	file << "DatasetName: " << datasetName << std::endl;
	file << "InfoText: " << infoText << std::endl;
	file << "NumDimensions: " << numDimensions << std::endl;
	file << "TotalNumSamples: " << totalNumSamples << std::endl;
	file << "Data:\n";
	
	for(ARF::UINT i=0; i<totalNumSamples; i++){
		for(ARF::UINT j=0; j<numDimensions; j++){
			file << "\t" << data[i][j];
		}
		file << std::endl;
	}
	
	file.close();
	return true;
}

bool DataSet::loadDatasetFromFile(const std::string &filename){
	
	std::fstream file;
	file.open(filename.c_str(), std::ios::in);
	clear();
	
	if( !file.is_open() ){
		throw ARF::ARFException("loadDatasetFromFile(const std::string &filename) - could not open file!");
		return false;
	}
	
	
	std::string word;
	
	//Get the name of the dataset
	file >> word;
	if(word != "DatasetName:"){
		file.close();
		throw ARF::ARFException("loadDatasetFromFile(const std::string &filename) - failed to find DatasetName header!");
		return false;
	}
	file >> datasetName;
	
	file >> word;
	if(word != "InfoText:"){
		file.close();
		ARF::ARFException("loadDatasetFromFile(const std::string &filename) - failed to find InfoText header!");
		return false;
	}
	
	//Load the info text
	file >> word;
	infoText = "";
	while( word != "NumDimensions:" ){
		infoText += word + " ";
		file >> word;
	}
	
	//Get the number of dimensions in the training data
	if( word != "NumDimensions:" ){
		file.close();
		ARF::ARFException("loadDatasetFromFile(const std::string &filename) - failed to find NumDimensions header!");
		return false;
	}
	file >> numDimensions;
	
	//Get the total number of training examples in the training data
	file >> word;
	if( word != "TotalNumTrainingExamples:" && word != "TotalNumExamples:" ){
		file.close();
		ARF::ARFException("loadDatasetFromFile(const std::string &filename) - failed to find TotalNumTrainingExamples header!");
		return false;
	}
	file >> totalNumSamples;
	
	//load the data
	ARF::SensorSample tempSample(numDimensions);
	data.resize(totalNumSamples, tempSample);
	
	for(ARF::UINT i=0; i<totalNumSamples; i++){
		ARF::UINT classLabel = 0;
		ARF::SensorSample sample(numDimensions,0);
		file >> classLabel;
		for(ARF::UINT j=0; j<numDimensions; j++){
			file >> sample[j];
		}
		data[i] = sample;
	}
	
	file.close();
	
	return true;
}

bool DataSet::saveDatasetToCSVFile(const std::string &filename) const{
	
	std::fstream file;
	file.open(filename.c_str(), std::ios::out );
	
	if( !file.is_open() ){
		return false;
	}
	
	//Write the data to the CSV file
	for(ARF::UINT i=0; i<totalNumSamples; i++){
		for(ARF::UINT j=0; j<numDimensions; j++){
			file << "," << data[i][j];
		}
		file << std::endl;
	}
	
	file.close();
	
	return true;
}

bool DataSet::loadDatasetFromCSVFile(const std::string &filename,const ARF::UINT classLabelColumnIndex){
	
	numDimensions = 0;
	datasetName = "NOT_SET";
	infoText = "";
	
	//Clear any previous data
	clear();
	
	//Parse the CSV file
	FileParser parser;
	
	if(!parser.parseCSVFile(filename,true)){
		throw ARF::ARFException("loadDatasetFromCSVFile(const std::string &filename,const UINT classLabelColumnIndex) - Failed to parse CSV file!");
		return false;
	}
	
	if(!parser.getConsistentColumnSize()){
		throw ARF::ARFException("loadDatasetFromCSVFile(const std::string &filename,const UINT classLabelColumnIndexe) - The CSV file does not have a consistent number of columns!");
		return false;
	}
	
	if(parser.getColumnSize() <= 1){
		throw ARF::ARFException("loadDatasetFromCSVFile(const std::string &filename,const UINT classLabelColumnIndex) - The CSV file does not have enough columns! It should contain at least two columns!");
		return false;
	}
	
	//Set the number of dimensions
	numDimensions = parser.getColumnSize()-1;
	
	//Reserve the memory for the data
	data.resize(parser.getRowSize(), ARF::SensorSample(numDimensions));
	
	//Loop over the samples and add them to the data set
	ARF::UINT j = 0;
	ARF::UINT n = 0;
	totalNumSamples = parser.getRowSize();
	for(ARF::UINT i=0; i<totalNumSamples; i++){
		
		//Get the sample data
		j=0;
		n=0;
		while(j != numDimensions){
			if(n != classLabelColumnIndex){
				std::string s = parser[i][n];
				ARF::Float sampleValue = Util::fromString<ARF::Float>(s);
				data[i][j++] = sampleValue;
			}
			n++;
		}
	}
	
	return true;
}

bool DataSet::printStats() const{
	
	std::cout << getStatsAsString();
	
	return true;
}

std::string DataSet::getStatsAsString() const{
	std::string statsText;
	statsText += "DatasetName:\t" + datasetName + "\n";
	statsText += "DatasetInfo:\t" + infoText + "\n";
	statsText += "Number of Dimensions:\t" + Util::toString( numDimensions ) + "\n";
	statsText += "Number of Samples:\t" + Util::toString( totalNumSamples ) + "\n";
	return statsText;
}


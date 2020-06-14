#ifndef PROCESAR_H
#define PROCESAR_H

vector<char> Strip={'"','\''};
vector<char> Split={',',';',':'};

class DataPreprocessing{
public:
	std::string filename;
	char lim;
	char div;
	bool type;
public:
	DataPreprocessing(std::string path);
	void DataRecognition();
	void DataCleaning();
	void DataIntregation();
	void DataReduction();
	void DataTransformation();
	char getlim();
	char getdiv();
};


#endif

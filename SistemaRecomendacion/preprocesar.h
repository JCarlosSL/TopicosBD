#ifndef PROCESAR_H
#define PROCESAR_H

vector<char> Strip={'"','\'','\t'};
vector<char> Split={',',';'};

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
	char getlim();
	char getdiv();
};


#endif

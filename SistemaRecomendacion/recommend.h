#ifndef Recommend_H
#define Recommend_H
#include "bits.h"

typedef std::pair<Bits,float> pbits;

class Recommender{
	public:
		map<string,Bits> user;
		map<string,Bits> object;
		map<Bits,std::map<Bits,float>> dataUsers;
		map<Bits,std::map<Bits,float>> dataSimil;
		int max=5;
		int min=0;
	public:
		Recommender(){};
		void loadData(string path,char lim);
		std::vector<std::pair<Bits,float>> computerNearestNeighbors(
				std::string iduser,int r);
		std::map<Bits,float> influences(std::string _user,int r);
		float recommender(std::map<Bits,float> inf,std::string obj);
		float computeSimilarity(std::string band1,std::string band2);
		std::pair<Bits,float> normalizar(
				std::string iduser,std::string iditem);
		void generateMatrix();
		void printMatrix();	
};


#endif

#ifndef Recommend_H
#define Recommend_H
#include "bits.h"

typedef std::pair<Bits,float> pbits;
using namespace std;

class Recommender{
	public:
		std::map<std::string,Bits> user;
		std::map<std::string,Bits> object;
		std::map<Bits,std::map<Bits,float>> dataUsers;//puntaje Usr Banda Puntaje
		float *averages;
		std::map<Bits,std::map<Bits,float>> bandaUsrPuntaje;//puntaje Banda Usr Puntaje
	
		static std::string filename;
		int maxRating=5;
		int minRating=1;
	public:
		Recommender(){};
		void loadData(string path,char lim);
		void loadDataItems(string path,char lim);
		std::vector<std::pair<Bits,float>> computerNearestNeighbors(
				std::string iduser,int r);
		std::map<Bits,float> influences(std::string _user,int r);
		float recommender(std::map<Bits,float> inf,std::string obj);
		float computeSimilarity(std::string band1,std::string band2);
		float* computeSimilarity3(Bits band1,Bits band2);
		void generateMatrix();
		void generateMatrixDisco();
		std::pair<Bits,float> normalizar(
				std::string iduser,std::string iditem);
	public:
		std::string set_directory(std::string &path);
		void printMatrix();
		void getAverage();

		float normalizerR(Bits _user,Bits item);
		float deNormalizerR(float NR);

		std::map<std::string,float> readMatrix(std::string address);
		std::map<int,float> get_item_similars(std::string address);
		std::map<int,float> get_items_similars(std::string address);
		float prediction(std::string userA, std::string item);	
};


#endif

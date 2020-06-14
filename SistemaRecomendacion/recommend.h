#ifndef Recommend_H
#define Recommend_H
#include "bits.h"

typedef std::pair<Bits,float> pbits;

class Recommender{
	public:
		map<string,Bits> user;
		map<string,Bits> object;
		map<Bits,std::map<Bits,float>> dataUsers;//puntaje Usr Banda Puntaje
		map<Bits,std::map<Bits,float>> dataSimil;
		double *averages;
		map<Bits,std::map<Bits,float>> bandaUsrPuntaje;//puntaje Banda Usr Puntaje
	
		int max=5;
		int min=0;
		static std::string filename;
		int maxRating=5;
		int minRating=0;
	public:
		Recommender(){};
		void loadData(string path,char lim);
		std::vector<std::pair<Bits,float>> computerNearestNeighbors(
				std::string iduser,int r);
		std::map<Bits,float> influences(std::string _user,int r);
		float recommender(std::map<Bits,float> inf,std::string obj);
		float computeSimilarity(std::string band1,std::string band2);
		double* computeSimilarity3(Bits band1,Bits band2);
		void generateMatrix();
		void generateMatrixDisco();
		std::pair<Bits,float> normalizar(
				std::string iduser,std::string iditem);
	private:
		void set_directory(std::string &path);
		void printMatrix();
		void getAverage();

		float normalizerR(std::string _user,std::string item);
		float deNormalizerR(float NR);

		std::map<std::string,float> readMatrix(std::string address);
		std::map<int,double> get_item_similars(std::string address);
		std::map<int,double> get_items_similars(std::string address);
		float prediction(std::string userA, std::string item);	
};


#endif

#ifndef Recommend_H
#define Recommend_H
#include "bits.h"

typedef std::pair<Bits,float> pbits;
typedef std::map<std::string,Bits> mapSBits;
typedef std::map<Bits,std::map<Bits,float>> matrixData;

class Recommender{
	public:
		mapSBits user; //id usuarios
		mapSBits object; //id objetos
		
		matrixData dataUsers;//puntaje Usr Banda Puntaje
		float *averages;
		matrixData bandaUsrPuntaje;//puntaje Banda Usr Puntaje
		std::vector<float> matrixSimilitud;
		static std::string filename; //archivo binario
		
		//books rating
		int maxRating=10;
		int minRating=0;
		
		//small y ml25 rating
		//int maxRating=5;
		//int minRating=1;
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
		void generatevectorDisco(std::string iditem);
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
		float prediction1(std::string userA, std::string item);	
	
		float* computeDev2(Bits bandaA, Bits bandaB);
		vector<vector<float>> generateMatrixRAMSlopeOne();
        std::map<int,float> predictionWSlopeOne(std::string _user, vector<vector<float>> matriz);
};


#endif

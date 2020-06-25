#ifndef Recommend_H
#define Recommend_H
#include "bits.h"

using namespace std;
typedef pair<Bits,float> pairBF;
typedef map<string,Bits> mapSBits;
typedef map<Bits,map<Bits,float>> matrixData;
typedef vector<pair<Bits,float>> distanceBF;
typedef map<Bits,float> mapBF;

class Recommender{
	public:
		mapSBits user; //id usuarios
		mapSBits object; //id objetos
		matrixData dataUsers;//puntaje Usr Banda Puntaje
		float *averages;
		matrixData bandaUsrPuntaje;//puntaje Banda Usr Puntaje
		static std::string filename; //archivo binario
		
		std::vector<float> matrixSimilitud;
		
		//books rating
		int maxRating=10;
		int minRating=0;
		
		//small y ml25 rating
		//int maxRating=5;
		//int minRating=1;
	public:
		Recommender(){};
		// cargar la data
		void loadData(string path,char lim); //cargar por usuarios
		void loadDataItems(string path,char lim); //cargar por items
		
		// calcula los K vecinos mas cercanos
		distanceBF computerNearestNeighbors(string iduser,int r);
		
		// Devuelve el vector de influencia 
		std::map<Bits,float> influences(string _user,int r);

		// recomendacion basada en usuarios	
		float recommender(mapBF inf,string obj);
		
		// coseno de similitud ajustado
		float computeSimilarity(string band1,string band2);
		float* computeSimilarity3(Bits band1,Bits band2);

		// generacion de matriz de similaridad
		void generateMatrix();
		void generateMatrixDisco();
		
		pairBF normalizar(string iduser,string iditem);

	public:
		string set_directory(string &path);
		void getAverage();

		float normalizerR(Bits _user,Bits item);
		float deNormalizerR(float NR);

		map<string,float> readMatrix(string address);
		
		map<int,float> get_items_similars(string address);
		float prediction(string userA, string item);	
		float prediction1(string userA, string item);	
	
		float* computeDev2(Bits bandaA, Bits bandaB);
		vector<vector<float>> generateMatrixRAMSlopeOne();
			map<int,float> predictionWSlopeOne(string _user, vector<vector<float>> matriz);
	
		float predictionSlopeOneRAM(string user,string item,vector<vector<float>> matriz);
};


#endif

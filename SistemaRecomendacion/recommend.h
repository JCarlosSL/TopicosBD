#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "bits.h"
#include<map>
#include<unordered_map>
#include<vector>
#include "filemanager.h"
#include "serializer.h"
#include "datasetconstants.h"
using namespace std;

class Recommender{

    public:
        enum mode{ SO = 2, AC = 3 };
        Recommender(std::string,bool,int,int);
        std::vector<std::pair<userOrItemKeyType,float>> computerNearestNeighbors(
                std::string iduser,int r);
        std::map<userOrItemKeyType,float> influences(std::string _user,int r);
        float recommender(std::map<userOrItemKeyType,float> inf,std::string obj);
        float computeSimilarity(std::string band1,std::string band2);
        float* computeSimilarity3(userOrItemKeyType band1,userOrItemKeyType band2);
        void generateMatrix();
        void generateMatrixDiscoAC();
        std::pair<userOrItemKeyType,float> normalizar(
                std::string iduser,std::string iditem);
        void serializeUpdate();
    public:
        std::string set_directory(std::string &path, mode type);
        void printMatrix();
        void getAverage();
        float normalizerR(userOrItemKeyType _user,userOrItemKeyType item);
        float deNormalizerR(float NR);

        std::map<std::string,float> readMatrix(std::string address);
        std::map<int,float> get_item_similars(std::string address);
        std::map<int,float> get_items_similars(std::string address);
        
	float predictionDisk(std::string userA, std::string item);
        float predictionAdjustCosine(std::string userA, std::string item);
        float predictionRAM(std::string userA, std::string item);

        float* computeDev2(userOrItemKeyType bandaA, userOrItemKeyType bandaB);
        vector<vector<float>> generateMatrixRAMSlopeOne(int);
            std::map<int,float> predictionWSlopeOne(std::string _user, vector<vector<float>> matriz);

        float* get_items_similarsSO(std::string address);
        void generateMatrixDiscoSO();

        float predictionSlopeOne(std::string usuario, std::string itemm);
        float predictionSlopeOneDisk(std::string usuario, std::string itemm);
        float predictionSlopeOneRAM(std::string user, std::string item, vector<vector<float>> matriz);
//		void insertUser(std::string user);
//		void insertItem(std::string item);
		void insertRatings(std::string path);
        void updateMatrix(int idItem, mode type);
        void updateMatrixAC(int idItem);
        void updateMatrixSO(int idItem);
        float errorcuadratico(string usuario);
        void getMaxItems(float perc);
        void setRowItems(size_t items);
public:
    FileManager *filemanager;
    std::string datasetName;

    //Four maps structure
    UserOrItemMap user;
    UserOrItemMap object;
    MatrixDataMap dataUsers;//puntaje Usr Banda Puntaje
    MatrixDataMap bandaUsrPuntaje;//puntaje Banda Usr Puntaje
    
    set<userOrItemKeyType> rowsItems;

    float *averages;
    std::vector<float> matrixSimilitud;
    static std::string filename;
    int maxRating;
    int minRating;
};

#endif // RECOMMENDER_H

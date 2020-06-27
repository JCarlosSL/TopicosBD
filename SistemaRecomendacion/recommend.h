#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "bits.h"
#include<map>
#include<unordered_map>
#include<vector>
#include <filemanager.h>
#include <serializerconstants.h>

typedef std::pair<Bits,float> pbits;
using namespace std;
typedef unordered_map<string, bits> typeMap1;
class Recommender{
    public:
        typeMap1 user;
        typeMap1 object;
        //typeMap3 dataUsers;
        std::map<bits,std::map<bits,float>> dataUsers;//puntaje Usr Banda Puntaje
        float *averages;
        std::map<bits,std::map<bits,float>> bandaUsrPuntaje;//puntaje Banda Usr Puntaje
        //typeMap3 bandaUsrPuntaje;
        std::vector<float> matrixSimilitud;
        static std::string filename;
        //books
        //int maxRating=10;
        //int minRating=0;

        //small y ml25
        int maxRating=5;
        int minRating=1;
    public:
        Recommender(){
           this->fileManager = new FileManager();
        };
        void loadData(string path,char lim);
        void loadDataItems(string path,char lim);
        std::vector<std::pair<bits,float>> computerNearestNeighbors(
                std::string iduser,int r);
        std::map<bits,float> influences(std::string _user,int r);
        float recommender(std::map<bits,float> inf,std::string obj);
        float computeSimilarity(std::string band1,std::string band2);
        float* computeSimilarity3(bits band1,bits band2);
        void generateMatrix();
        void generatevectorDisco(std::string iditem);
        void generateMatrixDisco();
        std::pair<bits,float> normalizar(
                std::string iduser,std::string iditem);
    public:
        std::string set_directory(std::string &path);
        void printMatrix();
        void getAverage();

        float normalizerR(bits _user,bits item);
        float deNormalizerR(float NR);

        std::map<std::string,float> readMatrix(std::string address);
        std::map<int,float> get_item_similars(std::string address);
        std::map<int,float> get_items_similars(std::string address);
        float prediction(std::string userA, std::string item);
        float prediction1(std::string userA, std::string item);

        float* computeDev2(bits bandaA, bits bandaB);
        vector<vector<float>> generateMatrixRAMSlopeOne();
            std::map<int,float> predictionWSlopeOne(std::string _user, vector<vector<float>> matriz);

        float predictionSlopeOneRAM(std::string user, std::string item, vector<vector<float>> matriz);
private:
    FileManager *fileManager;
};

#endif // RECOMMENDER_H

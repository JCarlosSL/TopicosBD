#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "bits.h"
#include<map>
#include<unordered_map>
#include<vector>
#include "filemanager.h"
#include "serializer.h"
#include "serializerconstants.h"
typedef std::pair<Bits,float> pbits;
using namespace std;
typedef unordered_map<string, userOrItemKeyType> typeMap1;
class Recommender{
    public:
        typeMap1 user;
        typeMap1 object;
        
        std::map<userOrItemKeyType,std::map<userOrItemKeyType,float>> dataUsers;//puntaje Usr Banda Puntaje
        float *averages;
        std::map<userOrItemKeyType,std::map<userOrItemKeyType,float>> bandaUsrPuntaje;//puntaje Banda Usr Puntaje

        std::vector<float> matrixSimilitud;
        static std::string filename;

        int maxRating=5;
        int minRating=1;
    public:
        Recommender(){
           this->serializer = new Serializer();
           //cout << SerializerConstants::LORDE <<endl;
           //this->filemanager=new FileManager(DataSetConstants::LORDE);
        };
        void setData(){
            //this->filemanager->unSerializeData(this->user,this->object,this->dataUsers,this->bandaUsrPuntaje);
        }
        void loadData(string path,char lim);
        void loadDataItems(string path,char lim);
        std::vector<std::pair<userOrItemKeyType,float>> computerNearestNeighbors(
                std::string iduser,int r);
        std::map<userOrItemKeyType,float> influences(std::string _user,int r);
        float recommender(std::map<userOrItemKeyType,float> inf,std::string obj);
        float computeSimilarity(std::string band1,std::string band2);
        float* computeSimilarity3(userOrItemKeyType band1,userOrItemKeyType band2);
        void generateMatrix();
        void generatevectorDisco(std::string iditem);
        void generateMatrixDisco();
        std::pair<userOrItemKeyType,float> normalizar(
                std::string iduser,std::string iditem);
    public:
        std::string set_directory(std::string &path);
        void printMatrix();
        void getAverage();

        float normalizerR(userOrItemKeyType _user,userOrItemKeyType item);
        float deNormalizerR(float NR);

        std::map<std::string,float> readMatrix(std::string address);
        std::map<int,float> get_item_similars(std::string address);
        std::map<int,float> get_items_similars(std::string address);
        float prediction(std::string userA, std::string item);
        float prediction1(std::string userA, std::string item);

        float* computeDev2(userOrItemKeyType bandaA, userOrItemKeyType bandaB);
        vector<vector<float>> generateMatrixRAMSlopeOne();
            std::map<int,float> predictionWSlopeOne(std::string _user, vector<vector<float>> matriz);

        float predictionSlopeOneRAM(std::string user, std::string item, vector<vector<float>> matriz);
private:
    Serializer *serializer;
    FileManager *filemanager;
};

#endif // RECOMMENDER_H

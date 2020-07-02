#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "serializer.h"
#include "datasetconstants.h"
#include "serializerconstants.h"
#include "tools.h"
class FileManager
{
public:
    FileManager(std::string dn)
        :datasetName(dn)
    {
        this->serializer = new Serializer();
        this->setLimit(dn);
        this->setSerializeDataPath(dn);
    }

    void setSerializeDataPath(std::string dn){
        if(dn==DataSetConstants::ANGELICA)
            this->serializeDataPath=SerializerConstants::ANGELICA;
        else if(dn==DataSetConstants::LORDE)
            this->serializeDataPath=SerializerConstants::LORDE;
        else if(dn==DataSetConstants::SLOPONE)
            this->serializeDataPath=SerializerConstants::SLOPONE;
        else if(dn==DataSetConstants::BOOKS)
            this->serializeDataPath=SerializerConstants::BOOKS;
        else if(dn==DataSetConstants::MOVIELEANS25M)
            this->serializeDataPath=SerializerConstants::MOVIELEANS_25M;
        else if(dn==DataSetConstants::MOVIELEANS27M)
            this->serializeDataPath=SerializerConstants::MOVIELEANS_27M;
        else if(dn==DataSetConstants::MOVIETV)
			this->serializeDataPath=SerializerConstants::MOVIETV;
    }

    void setLimit(std::string dn){
        if(dn==DataSetConstants::BOOKS)
            this->limit=';';
        else
            this->limit=',';
    }

    void loadDataAndSerialize(UserOrItemMap &userMap, UserOrItemMap &itemMap, MatrixDataMap &userItemMatrix, MatrixDataMap &itemUserMatrix) {
        fstream f;
        f.open(this->datasetName,std::ios::in);
        std::string temp;
        int cp=0;
        int cq=0;
        if(getline(f,temp)) cout<<"init \n";
        while(getline(f,temp)){
            vector<string> fields=split(temp,this->limit);
            auto p=userMap.find(trim(fields[0]));
            auto q=itemMap.find(trim(fields[1]));
            
            userOrItemKeyType tempp;
            userOrItemKeyType tempq;

            if(p==userMap.end()){
                tempp=cp;
                userMap[trim(fields[0])]=tempp;
                cp++;
            }
            else tempp=p->second;
            if(q==itemMap.end()){
                tempq=cq;
                itemMap[trim(fields[1])]=tempq;
                cq++;
            }
            else tempq=q->second;

            userItemMatrix[tempp][tempq]=std::stof(trim(fields[2]));
        }
        f.close();                 
        
        f.open(this->datasetName,std::ios::in);
        if(getline(f,temp)) cout<<"init \n";
        while(getline(f,temp)){
            vector<string> fields=split(temp,this->limit);
            userOrItemKeyType p=userMap[trim(fields[0])];
            userOrItemKeyType q=itemMap[trim(fields[1])];
            itemUserMatrix[q][p]=std::stof(trim(fields[2]));
        }
        f.close();
        cout<<"gg"<<endl;
        this->serializer->saveUser(userMap,this->serializeDataPath+SerializerConstants::USER);
        this->serializer->saveUser(itemMap,this->serializeDataPath+SerializerConstants::OBJECT);
        this->serializer->saveBandaUsers(userItemMatrix,this->serializeDataPath+SerializerConstants::BANDA_USERS);
        this->serializer->saveBandaUsersPuntaje(itemUserMatrix,this->serializeDataPath+SerializerConstants::BANDA_USERS_PUNTAJE);
    }

    void unSerializeData(UserOrItemMap &userMap, UserOrItemMap &itemMap, MatrixDataMap &userItemMatrix, MatrixDataMap & itemUserMatrix){
        userMap= this->serializer->recoverUser(this->serializeDataPath+SerializerConstants::USER);
        itemMap= this->serializer->recoverObject(this->serializeDataPath+SerializerConstants::OBJECT);
        userItemMatrix= this->serializer->recoverBandaUsers(this->serializeDataPath+SerializerConstants::BANDA_USERS);
        itemUserMatrix= this->serializer->recoverBandaUsersPuntaje(this->serializeDataPath+SerializerConstants::BANDA_USERS_PUNTAJE);
    }
private:  
    char limit;
    Serializer *serializer;
    std::string serializeDataPath;
    std::string datasetName;
};
#endif // FILEMANAGER_H

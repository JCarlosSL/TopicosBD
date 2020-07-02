#include "recommend.h"
#include <fstream>
#include "metrica.cpp"
#include <sys/stat.h>
#include <string>
#include <sys/types.h>
#include "tools.h"
#define epsilon 0.0000001f
typedef int idx;
std::string Recommender::filename = "sim.bin";

Recommender::Recommender(std::string dn,bool serialize=false,int minR=1,int maxR=5)
    :datasetName(dn),minRating(minR),maxRating(maxR)
{
    this->filemanager=new FileManager(this->datasetName);
    if(serialize){
        this->filemanager->loadDataAndSerialize(this->user,this->object,this->dataUsers,this->bandaUsrPuntaje);
    }
    else
        this->filemanager->unSerializeData(this->user,this->object,this->dataUsers,this->bandaUsrPuntaje);
	/*for(auto it=object.begin();it!=object.end();++it){
		if(it->second<=1000){
			cout<<it->first<<" "<<it->second<<"\n";
		}
	}*/
};


float Recommender::computeSimilarity(
    std::string band1,std::string band2){
    std::map<userOrItemKeyType,float> averages1;

    for(auto key:dataUsers){
        float sum=0.0;
        for(auto val:key.second){
            sum+=val.second;
        }
        averages1[key.first]=sum/key.second.size();
    }

	float num=0,dem1=0,dem2=0;
	auto q1=object[band1];
	auto q2=object[band2];
    for(auto key:dataUsers){
        auto p1=key.second.find(q1);
        auto p2=key.second.find(q2);
        if(p1!=key.second.end() and p2!=key.second.end()){
            float avg = averages1[key.first];
            num +=((*p1).second - avg)*((*p2).second - avg);
            dem1 +=pow((*p1).second - avg,2);
            dem2 +=pow((*p2).second - avg,2);
        }
    }
    return num/(sqrt(dem1)*sqrt(dem2));

}

void Recommender::getAverage(){
    //averages std::map<userOrItemKeyType,float> averages;
    averages = new float[user.size()]; // sin free, es para la clase Recommender
    int i=0;
    for(auto key:dataUsers){
        float sum=0.0;
        for(auto val:key.second){
            sum+=val.second;
        }
        //averages[key.first]=sum/key.second.size();
        if (key.second.size() == 0){
            averages[i]=0;
            cout<<"raro, tamaño de contenido de key cero?";
        }
        else{
            averages[i] = sum/key.second.size();
        }
        i++;
        std::cout<<i<<' '<<sum<<' '<<key.second.size()<<'\n';
    }
    std::cout<<'\n';
}

float* Recommender::computeSimilarity3(userOrItemKeyType bandaA,userOrItemKeyType bandaB){

    float *valores = new float[3];

    float num=0;
    float den1=0;
    float den2=0;

    if (bandaUsrPuntaje[bandaA].size() > bandaUsrPuntaje[bandaB].size()){
        auto aux = bandaA;
        bandaA = bandaB;
        bandaB = aux;
    }

    for(auto key:bandaUsrPuntaje[bandaA]){

        auto usr = key.first;
        float puntaje = key.second;

        if(bandaUsrPuntaje[bandaB].find(usr) !=   bandaUsrPuntaje[bandaB].end()){
            float avg = averages[usr];
            float num1 = (puntaje - avg);
            float num2 = (bandaUsrPuntaje[bandaB][usr] - avg);
            num += num1*num2;
            den1 += pow(num1,2);
            den2 += pow(num2,2);
        }
    }

    valores[0] = num;
    valores[1] = den1;
    valores[2] = den2;
    return valores;
}

void Recommender::generateMatrix(){
    int h=1;
    size_t size_file = object.size();
    int f=0;
    size_t ns=size_file*(size_file-1)/2;
    for (size_t i=size_file-1;i>0;--i){
        for(size_t j=0;j<size_file-h;++j){
            float *valores=computeSimilarity3(userOrItemKeyType(i),userOrItemKeyType(j));
            if(fabs(valores[1])<=epsilon || fabs(valores[2])<=epsilon)
                matrixSimilitud.push_back(0);
            else{
                matrixSimilitud.push_back(
                        valores[0]/(
                        sqrt(valores[1])
                        *sqrt(valores[2])));
            }
            ++f;
            delete[] valores;
        }
        h++;
    }
}
std::string Recommender::set_directory(std::string &path, mode type){
    std::string new_path="";
    if (type == AC)
        new_path = "MatrizAC";
    else
        new_path = "MatrizSO";
    std::string slash="/";
    size_t i = 0;
    for (int unit=0;unit<path.size();++unit){
        new_path += slash+path[unit];
        mkdir(new_path.c_str(),0777);
        ++i;
    }
    return new_path+slash;
}

void Recommender::generateMatrixDiscoAC(){
    size_t size_file = object.size()*3;
    
    for(int path=0;path<object.size();path++){
        std::string pathname =std::to_string(path);
        float *vectorFila = new float[size_file];
        int h=0;
        for(int j = 0 ; j < object.size()*3 ; j+=3){
            float *valores = computeSimilarity3(userOrItemKeyType(path),userOrItemKeyType(h));
            vectorFila[j] = valores[0];
            vectorFila[j+1] = valores[1];
            vectorFila[j+2] = valores[2];
            delete[] valores;
            h+=1;
        }
        //guardar a disco toda la fila ( el vectorFila )
        std::string new_path = set_directory(pathname,AC);

        fstream file;
		file.open(new_path.c_str()+this->filename,ios::out|ios::binary);
        file.write( reinterpret_cast<char *>(&vectorFila[0]), size_file*sizeof(float) );
        file.close();
        delete[] vectorFila;
        //cout<<path<<"\n";
    }
}

std::vector<std::pair<userOrItemKeyType,float>> Recommender::computerNearestNeighbors(
        std::string iduser,int r){
    auto p=user[iduser];
    std::vector<std::pair<userOrItemKeyType,float>> distances;
    float distance=0;
    for(auto key:dataUsers){
        if(key.first!=userOrItemKeyType(p)){
            distance=manhattan(dataUsers[p],dataUsers[key.first]);
            distances.push_back(std::make_pair(key.first,distance));
        }
    }
    cout<<distances[0].second<<"\n";
    sort(distances.begin(),distances.end(),sortbysec);
    if(distances.size() > r){
        return std::vector<std::pair<userOrItemKeyType,float>>(
                distances.begin(),distances.begin()+r);
    }
    else return distances;
}
std::map<userOrItemKeyType,float> Recommender::influences(
        std::string iduser,int r){
    auto nearest=computerNearestNeighbors(iduser,r);

    float n=0;
    for(auto p:nearest){
        n+=p.second;
    }
    std::map<userOrItemKeyType,float> influence;
    for(auto p:nearest){
        influence[p.first]=p.second/n;
    }
    return influence;
}
float Recommender::recommender(
    std::map<userOrItemKeyType,float> influences,std::string objeto){
    auto s=object[objeto];
    float proyeccion=0;
    for (auto p:influences){
        auto q=dataUsers[p.first].find(s);
        if(q!=dataUsers[p.first].end()){
            proyeccion+=(*q).second * p.second;
        }
    }
    return proyeccion;
}
//normalizacion
float Recommender::normalizerR(userOrItemKeyType _user,userOrItemKeyType item){
    float ratingN = 0;
    float diference = maxRating - minRating;
    ratingN = (2*(bandaUsrPuntaje[item][_user] - minRating) - diference)/diference;
    return ratingN;
}
float Recommender::deNormalizerR(float NR){
    float ratingDN = 0;
    float diference = maxRating - minRating;
    ratingDN = (0.5*((NR +1) * diference) + minRating);
    return ratingDN;
}
std::map<int, float> Recommender::get_items_similars(std::string address){
    size_t size_items = object.size()*3;
    std::fstream fin;
    std::map<int, float> similar_items;
    float *vector_items = new float[size_items];
    fin.open(address+filename, std::ios::binary | std::ios::in);
    fin.read( reinterpret_cast<char *>(&vector_items[0]), size_items*sizeof(float));
    size_t item = 0;
    for (size_t idx = 0; idx < size_items; ++idx){
        float num = vector_items[idx];
        float dem1 = vector_items[++idx];
        float dem2 = vector_items[++idx];
        float prediction;
        if (fabs(dem1) <= epsilon || fabs(dem2) <= epsilon)
            prediction = 0;
        else
            prediction = num / (sqrt(dem1) * sqrt(dem2));
        similar_items[item] = prediction;
        item += 1;
    }
    return similar_items;
}
float Recommender::prediction1(std::string userA,std::string item){
    int iditem = object[item];
    float den=0,num=0;
    for(auto p:dataUsers[user[userA]]){
        auto iditemu = p.first;
        int pitem=iditem;
        float NR = normalizerR(user[userA],iditemu);

        int pos=iditem;
        int size=object.size()-1;
        while(size>pitem and size>iditem){
                pos+=size;
                size--;
        }
        if(iditem>pitem)
                pos-=(iditem-pitem);

        float simi=0;
        float *simil =computeSimilarity3(object[item],p.first);
        if(fabs(simil[1]) <= epsilon || fabs(simil[2]) <= epsilon)
            simi=0;
        else
            simi=simil[0]/(sqrt(simil[1])*sqrt(simil[2]));

        num+=simi*NR;
        den+=fabs(simi);
    }
    if(fabs(den) <= den * epsilon)
            return 0;
    else
            return deNormalizerR(float(num/den));

    return 0;
}
float Recommender::prediction(std::string userA, std::string item){

    if (user.find(userA)==user.end() || object.find(item)==object.end())
            return -2;
    int iditem = object[item];
    string str = std::to_string(iditem);
    string address="MatrizAC/";
    string slash="/";
    
	for(auto it:str){
        address += it + slash;
    }

	cout<<" cant: "<<dataUsers[user[userA]].size()<<"\n";
    //relax
    address = address;
    std::map<int,float> items = get_items_similars(address);

    float num = 0.0, den = 0.0;
    for(auto p:dataUsers[user[userA]]){
        //for(auto key:items){
        auto idit = p.first;
        auto NR=normalizerR(user[userA],idit);

        float sim = items[idit];
        //cout<<NR<<endl;
        num += sim * NR;
        den += fabs(sim);

    }
    if(fabs(den) <= den * epsilon)
        return 0;
    else
        return deNormalizerR(float(num/den));
}

float* Recommender::computeDev2(userOrItemKeyType bandaA, userOrItemKeyType bandaB){//2 porque retorna 2 valores: dev y usuarios involucrados

    float *valores = new float[2];

    float dev=0;
    float usrInvolucrados=0;

    if (bandaUsrPuntaje[bandaA].size() > bandaUsrPuntaje[bandaB].size()){
        auto aux = bandaA;
        bandaA = bandaB;
        bandaB = aux;
    }

    for(auto key:bandaUsrPuntaje[bandaA]){

        auto usr = key.first;
        float puntaje = key.second;

        if(bandaUsrPuntaje[bandaB].find(usr) !=   bandaUsrPuntaje[bandaB].end()){
            dev += puntaje - bandaUsrPuntaje[bandaB][usr];
            usrInvolucrados += 1;
        }
    }

    if(usrInvolucrados>0)
        valores[0] = dev/usrInvolucrados;
    else
        valores[0] = 0;
    valores[1] = usrInvolucrados;

    return valores;

}

void Recommender::generateMatrixDiscoSO(){
    
    size_t size_file = object.size()*2;
    for(int path=0;path<object.size();path++){
        std::string pathname =std::to_string(path);
        float *vectorFila = new float[size_file];
        int h=0;
        for(int j = 0 ; j < object.size()*2 ; j+=2){
            float *valores = computeDev2(userOrItemKeyType(path),userOrItemKeyType(h));
            vectorFila[j] = valores[0];
            vectorFila[j+1] = valores[1];
            delete[] valores;
            h+=1;
        }
        //guardar a disco toda la fila ( el vectorFila )
        
        std::string new_path = set_directory(pathname,SO);
        
        fstream file;
		file.open(new_path.c_str()+this->filename,ios::out|ios::binary);
        file.write( reinterpret_cast<char *>(&vectorFila[0]), size_file*sizeof(float) );
        file.close();
        delete[] vectorFila;
    }
}

vector<vector<float>> Recommender::generateMatrixRAMSlopeOne(int index=-1){
    
    vector<vector<float>> matriz;
    int numItems = object.size();
    if(index==-1){
        for(int i=0; i<numItems; i++){

            vector<float> fila;

            for (int j=0; j<numItems; j++){

                fila.push_back(computeDev2(userOrItemKeyType(i), userOrItemKeyType(j))[0]);
                fila.push_back(computeDev2(userOrItemKeyType(i), userOrItemKeyType(j))[1]);

            }

            matriz.push_back(fila);

        }  
    }
    else{
    //cout << "my index" << index << endl;
    for(int i=index; i<index+1; i++){

        vector<float> fila;

        for (int j=0; j<numItems; j++){

            fila.push_back(computeDev2(userOrItemKeyType(i), userOrItemKeyType(j))[0]);
            fila.push_back(computeDev2(userOrItemKeyType(i), userOrItemKeyType(j))[1]);

        }

        matriz.push_back(fila);

    }
    }
    return matriz;
}


map<int,float> Recommender::predictionWSlopeOne(std::string _user, vector<vector<float>> matriz){
    map<int,float> recommends;
    float num=0.0;
    float den=0.0;
    for(auto key:bandaUsrPuntaje){
        if(!key.second[user[_user]]){
            for(auto key2:bandaUsrPuntaje){
                if(key2.second[user[_user]]){
                    int i = key.first;
                    int j = key2.first;
                    num += (matriz[i][j*2] + key2.second[user[_user]]) * matriz[i][(j*2)+1];
                    den += matriz[i][(j*2)+1];
                }
            }
            //cout<<num<<"!!"<<den<<endl;
            recommends[key.first] = num/den;
        }
    }
    return recommends;
}

float* Recommender::get_items_similarsSO(std::string address){
    size_t size_items = object.size()*2;
    std::fstream fin;
    float *vector_items = new float[size_items];
    fin.open(address+filename, std::ios::binary | std::ios::in);
    fin.read( reinterpret_cast<char *>(&vector_items[0]), size_items*sizeof(float));
    return vector_items;
}

float Recommender::predictionSlopeOneRAM(std::string usuario, std::string itemm){
    if ( user.find(usuario) == user.end() || object.find(itemm) == object.end() )
        return -1;
    userOrItemKeyType usr = user[usuario];
    int itemTo = object[itemm];

    string str = std::to_string(itemTo);
    string address="MatrizSO/";
    string slash="/";
    for(auto it:str){
        address += it + slash;
    }

    float* simil_items = get_items_similarsSO(address);

    float num=0;
    float den=0;

    for (auto key: dataUsers[usr]){

        int itemFrom = key.first;
        float puntaje = key.second;

        float c = simil_items[itemFrom*2+1];
        num += (simil_items[itemFrom*2] + puntaje) * c;
        den += c;
    }

    if (den==0)
        return 0;
    return num/den;
}

float Recommender::predictionSlopeOneRAM(std::string usuario, std::string itemm, vector<vector<float>> matriz){

    if ( user.find(usuario) == user.end() || object.find(itemm) == object.end() )
        return -1;

    userOrItemKeyType usr = user[usuario];
    int itemTo = object[itemm];

    float num=0;
    float den=0;

    for (auto key: dataUsers[usr]){

        int itemFrom = key.first;
        float puntaje = key.second;

        num += (matriz[itemTo][itemFrom*2] + puntaje) * matriz[itemTo][itemFrom*2+1];
        den += matriz[itemTo][itemFrom*2+1];
    }

    if (den==0)
        return 0;
    return num/den;
}

void Recommender::insertRatings(std::string path){

    char splitter = ',';
    fstream f;
    f.open(path,std::ios::in);
    std::string word;
    if(getline(f,word)); //cout<<"ignore \n";
    while(getline(f,word)){
        vector<string> dataVec = split(word,splitter);

        auto it = user.find(dataVec[0]);
        if(it != user.end()){
            //cout<<"usuario encontrado"<<endl;
            auto jt = object.find(dataVec[1]);
            if(jt != object.end()){
                //cout<<"item encontrado"<<endl;
                dataUsers[user[dataVec[0]]][object[dataVec[1]]] = stof(dataVec[2]);
                bandaUsrPuntaje[object[dataVec[1]]][user[dataVec[0]]] = stof(dataVec[2]);
            }else{
                object[dataVec[1]] = object.size();
                dataUsers[user[dataVec[0]]][object[dataVec[1]]] = stof(dataVec[2]);
                bandaUsrPuntaje[object[dataVec[1]]][user[dataVec[0]]] = stof(dataVec[2]);
            }
        }else{
            user[dataVec[0]] = user.size();
            auto kt = object.find(dataVec[1]);
            if(kt != object.end()){
                //cout<<"item encontrado"<<endl;
                dataUsers[user[dataVec[0]]][object[dataVec[1]]] = stof(dataVec[2]);
                bandaUsrPuntaje[object[dataVec[1]]][user[dataVec[0]]] = stof(dataVec[2]);
            }else{
                object[dataVec[1]] = object.size();
                dataUsers[user[dataVec[0]]][object[dataVec[1]]] = stof(dataVec[2]);
                bandaUsrPuntaje[object[dataVec[1]]][user[dataVec[0]]] = stof(dataVec[2]);
            }
        }
        // updating on similarity matrices
        //int idUser = user[dataVec[0]];
        int idItem = object[dataVec[1]];
        getAverage();
        updateMatrixAC(idItem);
        updateMatrixSO(idItem);
    }

    f.close();
}

void Recommender::serializeUpdate(){
    this->filemanager->loadDataAndSerialize(this->user,this->object,this->dataUsers,this->bandaUsrPuntaje);
}

void Recommender::updateMatrixAC(int idItem){
    updateMatrix(idItem,AC);
}

void Recommender::updateMatrixSO(int idItem){
    updateMatrix(idItem,SO);
}

void Recommender::updateMatrix(int idItem, mode type){
    //change row idItem
    size_t sizeColItem = object.size();
    std::string idItemCode;
    std::string filepath;
    streampos posItemFile = sizeof(float)*idItem*type;
    float* (Recommender::*computeSimilarity)(userOrItemKeyType,userOrItemKeyType) = nullptr;
    if (type == AC)
        computeSimilarity = &Recommender::computeSimilarity3;
    else if (type == SO)
        computeSimilarity = &Recommender::computeDev2;
    float* colItem = new float[sizeColItem*type];
    int otherItem = 0;
    for(size_t i = 0; i < sizeColItem*type; i+=type){
        float *values = new float[type];
        values = (*this.*computeSimilarity)(idItem,otherItem);
        for (size_t j = 0; j < type; ++j)
            colItem[i+j] = values[j];
        idItemCode = std::to_string(otherItem);
        filepath = set_directory(idItemCode,type);
        fstream otherItemFile;
        otherItemFile.open(filepath.c_str(),ios::out|ios::binary|ios::ate);
        otherItemFile.seekg(posItemFile,ios::beg);
        otherItemFile.write( reinterpret_cast<char *>(&values[0]), type*sizeof(float));
        otherItemFile.close();
        ++otherItem;
    }
    idItemCode = std::to_string(idItem);
    filepath = set_directory(idItemCode,type);
    fstream itemFile;
    itemFile.open(filepath.c_str(),ios::out|ios::binary|ios::ate);
    itemFile.write( reinterpret_cast<char *>(&colItem[0]), sizeColItem*type*sizeof(float) );
    itemFile.close();
    delete[] colItem;
}

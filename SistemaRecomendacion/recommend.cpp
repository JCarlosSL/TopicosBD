#include "recommend.h"
#include <fstream>
#include "tools.h"
#include "metrica.cpp"
#include <sys/stat.h>
#include <string>
#include <sys/types.h>

#define epsilon 0.0000001f

typedef int idx;
typedef vector<string> field;

const string file="Matriz/";
std::string Recommender::filename = "sim.bin";

void Recommender::loadData(string path,char lim){
	fstream f;
	f.open(path,ios::in);
	
	string temp;
	idx cu=0,ci=0;
	// quita la cabecera
	if(getline(f,temp)) cout<<"load rating users \n"; 
	
	while(getline(f,temp)){
		field fields=split(temp,lim);
		string usuario=trim(fields[0]);
		string item = trim(fields[1]);
		float rating = stof(trim(fields[2]));
		auto p=user.find(usuario);
		auto q=object.find(item);
		Bits temp_u,temp_i;
		if(p==user.end()){
			temp_u=Bits(cu);
			user[usuario]=temp_u;
			cu++;
		}
		else temp_u=p->second;
		if(q==object.end()){
			temp_i=Bits(ci);
			object[item]=temp_i;
			ci++;
		}
		else temp_i=q->second;
		dataUsers[temp_u][temp_i]=rating;
	}
	f.close();
}
void Recommender::loadDataItems(string path,char lim){
	fstream f;
	f.open(path,ios::in);
	
	string temp;
	if(getline(f,temp)) cout<<"load rating items \n"; 
	
	while(getline(f,temp)){
		field fields = split(temp,lim);
		string usuario = trim(fields[0]);
		string item = trim(fields[1]);
		Bits p=user[usuario];
		Bits q=object[item];
		bandaUsrPuntaje[q][p]=std::stof(trim(fields[2]));
		
	}
	f.close();
}

float Recommender::computeSimilarity(string band1,string band2){
	mapBF averages1;
	for(auto key:dataUsers){
		float sum=0.0;
		for(auto val:key.second){
			sum+=val.second;
		}
		averages1[key.first]=sum/key.second.size();
	}
	float num=0,dem1=0,dem2=0;
	Bits q1=object[band1];
	Bits q2=object[band2];

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
    //averages std::map<Bits,float> averages;
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
	}
}

float* Recommender::computeSimilarity3(Bits bandaA,Bits bandaB){
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
		if(bandaUsrPuntaje[bandaB].find(usr) != bandaUsrPuntaje[bandaB].end()){
			float avg = averages[usr.item.to_ulong()];
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
	size_t ns=size_file*(size_file-1)/2;
	for (size_t i=size_file-1;i>0;--i){
		for(size_t j=0;j<size_file-h;++j){
			float *valores=computeSimilarity3(Bits(i),Bits(j));
			if(fabs(valores[1])<=epsilon || fabs(valores[2])<=epsilon)
				matrixSimilitud.push_back(0);
			else{
				matrixSimilitud.push_back(
						valores[0]/(
						sqrt(valores[1])
						*sqrt(valores[2])));
			}
			delete[] valores;
		}
		h++;
	}
}



string Recommender::set_directory(std::string &path){
	string new_path="";
	string slash="/";
	size_t i = 0;
	for (int unit=0;unit<path.size();++unit){
		new_path += path[unit]+slash;
		++i;
	}
	return "Matriz/"+new_path;
}

void Recommender::generateMatrixDisco(){
	size_t size_file = object.size()*3;
	mkdir("Matriz/",0777);
	for(int path=0;path<object.size();path++){
		string pathname =to_string(path); 
		float *vectorFila = new float[size_file];
		
		int h=0;
		for(int j = 0 ; j < object.size()*3 ; j+=3){
			float *valores = computeSimilarity3(Bits(path),Bits(h));
			vectorFila[j] = valores[0];
			vectorFila[j+1] = valores[1];
			vectorFila[j+2] = valores[2];
			delete[] valores;
		h+=1;
		}
		//guardar a disco toda la fila ( el vectorFila )		
		string new_path = set_directory(pathname);
		mkdir(new_path.c_str(),0777);
		fstream file;
		file.open(new_path.c_str()+this->filename,ios::out|ios::binary);
		file.write( reinterpret_cast<char *>(&vectorFila[0]), size_file*sizeof(float) );
		file.close();
		delete[] vectorFila;
		//cout<<path<<"\n";
	}
}

vector<pairBF> Recommender::computerNearestNeighbors(string iduser,int r){

	Bits p=user[iduser];
	vector<pairBF> distances;
	float distance=0;
	for(auto key:dataUsers){
		if(key.first!=Bits(p)){
			distance=manhattan(dataUsers[p],dataUsers[key.first]);
			distances.push_back(std::make_pair(key.first,distance));
		}
	}
	sort(distances.begin(),distances.end(),sortbysec);
	if(distances.size() > r){
		return vector<pairBF>(distances.begin(),distances.begin()+r);
	}
	else
		return distances;
}


mapBF Recommender::influences(string iduser,int r){
	
	auto nearest=computerNearestNeighbors(iduser,r);

	float n=0;
	for(auto p:nearest){
		n+=p.second;
	}
	mapBF influence;
	for(auto p:nearest){
		influence[p.first]=p.second/n;
	}	
	return influence;
}

float Recommender::recommender(mapBF influences,string objeto){
	Bits s=object[objeto];
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

float Recommender::normalizerR(Bits _user,Bits item){
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

map<int, float> Recommender::get_items_similars(string address){
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
	//	cout<<prediction<<" "<<dem1<<" "<<dem2<<"\n";
	}

	return similar_items;
}   

float Recommender::prediction1(string userA,string item){
	int iditem = object[item].item.to_ulong();
	
	float den=0,num=0;

	for(auto p:dataUsers[user[userA]]){
		auto iditemu = p.first;
		int pitem=iditemu.item.to_ulong();
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
		//float simi = matrixSimilitud[pos];
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
		return deNormalizerR(num/den);

	return 0;
}



float Recommender::prediction(string userA, string item){
	
	if (user.find(userA)==user.end() || object.find(item)==object.end())
			return -2;
	
	int iditem = object[item].item.to_ulong();
	string str = std::to_string(iditem);
	string address="Matriz/";
	string slash="/";
	for(auto it:str){
		address += it + slash;
	}
	
	//relax	
	address = address;
	map<int,float> items = get_items_similars(address);
	float num = 0.0, den = 0.0;
	for(auto p:dataUsers[user[userA]]){
		auto idit = p.first;
		auto NR=normalizerR(user[userA],idit);
		
		float sim = items[idit.item.to_ulong()];
		num += sim * NR;
		den += fabs(sim);
	}
	
	if(fabs(den) <= den * epsilon)
		return 0;
	else
		return deNormalizerR(float(num/den));
}  

float* Recommender::computeDev2(Bits bandaA, Bits bandaB){//2 porque retorna 2 valores: dev y usuarios involucrados
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

vector<vector<float>> Recommender::generateMatrixRAMSlopeOne(){    
	int numItems = bandaUsrPuntaje.size();
	vector<vector<float>> matriz;
	for(int i=0; i<numItems; i++){
		vector<float> fila;
		for (int j=0; j<numItems; j++){
				fila.push_back(computeDev2(Bits(i), Bits(j))[0]);
				fila.push_back(computeDev2(Bits(i), Bits(j))[1]);
			}
			matriz.push_back(fila);
	}
		return matriz;
}

map<int,float> Recommender::predictionWSlopeOne(string _user, vector<vector<float>> matriz){
	map<int,float> recommends;
	float num=0.0;
	float den=0.0;
	for(auto key:bandaUsrPuntaje){
		if(!key.second[user[_user]]){
			for(auto key2:bandaUsrPuntaje){
				if(key2.second[user[_user]]){
					int i = key.first.item.to_ulong();
					int j = key2.first.item.to_ulong();
					num += (matriz[i][j*2] + key2.second[user[_user]]) * matriz[i][(j*2)+1];
					den += matriz[i][(j*2)+1];
				}
			}
			//cout<<num<<"!!"<<den<<endl;
			recommends[key.first.item.to_ulong()] = num/den;
		}
	}
	return recommends;
}

float Recommender::predictionSlopeOneRAM(string usuario, string itemm, vector<vector<float>> matriz){
	if ( user.find(usuario) == user.end() || object.find(itemm) == object.end() )
		return -1; 
	
	Bits usr = user[usuario];    
	int itemTo = object[itemm].item.to_ulong();
	
	float num=0;
	float den=0;
	for (auto key: dataUsers[usr]){
		int itemFrom = key.first.item.to_ulong();
		float puntaje = key.second;
		num += (matriz[itemTo][itemFrom*2] + puntaje) * matriz[itemTo][itemFrom*2+1];
		den += matriz[itemTo][itemFrom*2+1];
	}
	if (den==0)
			return 0;
		return num/den;
}


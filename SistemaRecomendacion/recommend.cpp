#include "recommend.h"
#include <fstream>
#include "tools.h"
#include "metrica.cpp"
#include <sys/stat.h>
#include <string>
#include <sys/types.h>

#define epsilon 0.0000001f

typedef int idx;


std::string Recommender::filename = "sim.bin";

void Recommender::loadData(std::string path,char lim){
	fstream f;
	f.open(path,std::ios::in);
	
	std::string temp;
	int cp=0;
	int cq=0;
	if(getline(f,temp)) cout<<"init \n"; 
	while(getline(f,temp)){
		vector<string> fields=split(temp,lim);
		auto p=user.find(trim(fields[0]));
		auto q=object.find(trim(fields[1]));
		Bits tempp;
		Bits tempq;
		if(p==user.end()){
			tempp=Bits(cp);
			user[trim(fields[0])]=tempp;
			cp++;
		}
		else tempp=p->second;
		if(q==object.end()){
			tempq=Bits(cq);
			object[trim(fields[1])]=tempq;
			cq++;
		}
		else tempq=q->second;
		dataUsers[tempp][tempq]=std::stof(trim(fields[2]));
	}
	f.close();
}
void Recommender::loadDataItems(std::string path,char lim){
	fstream f;
	f.open(path,std::ios::in);
	
	std::string temp;

	if(getline(f,temp)) cout<<"init \n"; 
	while(getline(f,temp)){
		vector<string> fields=split(temp,lim);
		Bits p=user[trim(fields[0])];
		Bits q=object[trim(fields[1])];
		bandaUsrPuntaje[q][p]=std::stof(trim(fields[2]));
		
	}
	f.close();
}

float Recommender::computeSimilarity(
	std::string band1,std::string band2){
	std::map<Bits,float> averages1;

	for(auto key:dataUsers){
		float sum=0.0;
		for(auto val:key.second){
			sum+=val.second;
		}
		averages1[key.first]=sum/key.second.size();
	}

	float num=0;
	float dem1=0;
	float dem2=0;
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
        
        if(bandaUsrPuntaje[bandaB].find(usr) !=   bandaUsrPuntaje[bandaB].end()){
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
	int i=0;
	std::string item="Kacey Musgraves";
	for(auto p:object){
			float sim=computeSimilarity(item,p.first);
			std::cout<<p.second<<" "<<sim<<"\n";
	}
	std::cout<<"finish \n";
}


std::string Recommender::set_directory(std::string &path){
	std::string new_path="";
	std::string slash="/";
	size_t i = 0;
	for (int unit=0;unit<path.size();++unit){
		new_path += path[unit]+slash;
		++i;
	}
	cout<<"a"<<endl;
	return "Matriz/"+new_path;
}

void Recommender::generatevectorDisco(std::string iditem){
	auto p=object[iditem];
	size_t size_file = object.size()*3;
	float *vectorFila = new float[size_file];
	int i=0;
	int id=p.item.to_ulong();
	std::cout<<p<<std::endl;
	std::string pathname = std::to_string(id);
	for(int j=0;j<object.size()*3;j+=3){
		float *valores = computeSimilarity3(p,Bits(i));
		vectorFila[j] = valores[0];
		vectorFila[j+1] = valores[1];
		vectorFila[j+2] = valores[2];
		delete[] valores;
		i+=1;
	}
	std::string new_path = set_directory(pathname);
	mkdir(new_path.c_str(),0777);
	fstream file;
	file.open(new_path.c_str()+this->filename,std::ios::out|std::ios::binary);
	file.write(reinterpret_cast<char *>(&vectorFila[0]),size_file*sizeof(float));
	file.close();
	delete[] vectorFila;
}

void Recommender::generateMatrixDisco(){
	size_t size_file = object.size()*3;
	mkdir("Matriz/",0777);
	for(int path=0;path<object.size();path++){
		std::string pathname =std::to_string(path); 
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
				
		std::string new_path = set_directory(pathname);
		mkdir(new_path.c_str(),0777);
		fstream file;
		file.open(new_path.c_str()+this->filename,std::ios::out|std::ios::binary);
		file.write( reinterpret_cast<char *>(&vectorFila[0]), size_file*sizeof(float) );
		file.close();

		delete[] vectorFila;
		cout<<path<<"\n";
	}
}


std::vector<std::pair<Bits,float>> Recommender::computerNearestNeighbors(
		std::string iduser,int r){
	auto p=user[iduser];
	std::vector<std::pair<Bits,float>> distances;
	float distance=0;
	for(auto key:dataUsers){
		if(key.first!=Bits(p)){
			distance=manhattan(dataUsers[p],dataUsers[key.first]);
			distances.push_back(std::make_pair(key.first,distance));
		}
	}
	sort(distances.begin(),distances.end(),sortbysec);
	if(distances.size() > r){
		return std::vector<std::pair<Bits,float>>(
				distances.begin(),distances.begin()+r);
	}
	else return distances;
}


std::map<Bits,float> Recommender::influences(
		std::string iduser,int r){
	auto nearest=computerNearestNeighbors(iduser,r);

	float n=0;
	for(auto p:nearest){
		n+=p.second;
	}
	std::map<Bits,float> influence;
	for(auto p:nearest){
		influence[p.first]=p.second/n;
	}	
	return influence;
}

float Recommender::recommender(
	std::map<Bits,float> influences,std::string objeto){

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
		//	cout<<prediction<<" "<<dem1<<" "<<dem2<<"\n";
		}

		return similar_items;
}   

float Recommender::prediction(std::string userA, std::string item){
       int iditem = object[item].item.to_ulong();
       string str = std::to_string(iditem);
	string address="matriz/";
	string slash="/";
	for(auto it:str){
		address += it + slash;
	}

	//relax	
	address = address;
	std::map<int,float> items = get_items_similars(address);

/*	
	for(auto it:items){
		std::cout<<it.first<<" "<<it.second<<"\n";
	}*/

	float num = 0.0, den = 0.0;
	for(auto p:dataUsers[user[userA]]){
    	//for(auto key:items){
		auto idit = p.first;
		auto NR=normalizerR(user[userA],idit);
		
		float sim = items[idit.item.to_ulong()];
		cout<<NR<<endl;
		num += sim * NR;
		den += fabs(sim);

    }
	if(fabs(den) <= den * epsilon)
		return 0;
	else
		return deNormalizerR(float(num/den));
}  


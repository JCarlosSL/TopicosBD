#include "recommend.h"
#include <fstream>
#include "tools.h"
#include "metrica.cpp"
#include <sys/stat.h>
#include <string>

#define epsilon 0.0000001f

typedef int idx;


std::string Recommender::filename = "sim.bin";

void Recommender::loadData(std::string path,char lim){
	fstream f;
	f.open(path,std::ios::in);
	
	std::string temp;
	int cp=0;
	int cq=0;
	Bits tempp;
	Bits tempq;
	if(getline(f,temp)) cout<<"init \n"; 
	while(getline(f,temp)){
		vector<string> fields=split(temp,lim);
		std::map<std::string,Bits>::iterator p=user.find(trim(fields[0]));
		std::map<std::string,Bits>::iterator q=object.find(trim(fields[1]));
		if(p==user.end()){
			user[trim(fields[0])]=Bits(cp);
			tempp=Bits(cp);
			cp++;
		}
		else tempp=p->second;
		if(q==object.end()){
			object[trim(fields[1])]=Bits(cq);
			tempq=Bits(cq);
			cq++;
		}
		else tempq=q->second;
		dataUsers[tempp][tempq]=std::stof(trim(fields[2]));
	}
	f.close();
}

float Recommender::computeSimilarity(
	std::string band1,std::string band2){
	std::map<Bits,float> averages;

	for(auto key:dataUsers){
		float sum=0.0;
		for(auto val:key.second){
			sum+=val.second;
		}
		averages[key.first]=sum/key.second.size();
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
			float avg = averages[key.first];
			num +=((*p1).second - avg)*((*p2).second - avg);
			dem1 +=pow((*p1).second - avg,2);
			dem2 +=pow((*p2).second - avg,2);
		}
	}
	return num/(sqrt(dem1)*sqrt(dem2));

}

void Recommender::getAverage(){
    //averages std::map<Bits,float> averages;
    averages = new double[user.size()]; // sin free, es para la clase Recommender
    int i=0;
    for(auto key:dataUsers){
		double sum=0.0;
		for(auto val:key.second){
			sum+=val.second;
		}	    
		//averages[key.first]=sum/key.second.size();
		if (key.second.size() == 0){
		    averages[i]=0;
		    cout<<"raro, tamaño de contenido de key cero?";
		}
		else
		    averages[i] = sum/key.second.size();
		i++;
	}
}

double* Recommender::computeSimilarity3(Bits bandaA,Bits bandaB){
	
	double *valores = new double[3];
	
	double num=0;
	double den1=0;
	double den2=0;
	    
    if (bandaUsrPuntaje[bandaA].size() > bandaUsrPuntaje[bandaB].size()){
        auto aux = bandaA;
        bandaA = bandaB;
        bandaB = aux;
    }
    
    for(auto key:bandaUsrPuntaje[bandaA]){
    
        auto usr = key.first;
        float puntaje = key.second;
        
        if(bandaUsrPuntaje[bandaB].find(usr) !=   bandaUsrPuntaje[bandaB].end()){
            double avg = averages[usr.item.to_ulong()];
            double num1 = (puntaje - avg);
            double num2 = (bandaUsrPuntaje[bandaB][usr] - avg);
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
/*
void Recommender::generateMatrix(){
	int i=0;
	for(auto p=object.begin();p!=object.end();){
		++p;
		auto q=p;
		std::cout<<i<<std::endl;
		for(;q!=object.end() ;++q){
			float sim=computeSimilarity(p->first,q->first);
			dataSimil[p->second][q->second]=sim;
			std::cout<<sim<<" "<<p->first<<" "<<q->first<<"\n";
		}
		++i;
	}
}
*/

std::string Recommender::set_directory(std::string &path){
	std::string new_path="";
	std::string slash="/";
	size_t i = 0;
	for (int unit=0;unit<path.size();++unit){
		new_path += path[unit]+slash;
		++i;
	}
	return "matriz/" +new_path;
}

void Recommender::generateMatrixDisco(){
<<<<<<< HEAD
  	idx path=0;
=======
        int path = 0;
>>>>>>> e4850056a66b8a0821b8c016714e2ab4b680f8db
	size_t size_file = object.size()*3;
	for(auto p=object.begin();p!=object.end();++p){

		std::string pathname =std::to_string(path); 
		double *vectorFila = new double[size_file];
		int j=0;

		for(auto q=object.begin();q!=object.end() ;++q){
	        double *valores = computeSimilarity3(p->second,q->second);
	        vectorFila[j] = valores[0];
	        vectorFila[j+1] = valores[1];
	        vectorFila[j+2] = valores[2];
	        j +=3;
	        delete[] valores;
		}
		//guardar a disco toda la fila ( el vectorFila )
				
		std::string new_path=set_directory(pathname);
		mkdir(new_path.c_str(),0777);
		ofstream file;
		file.open(new_path.c_str()+this->filename, std::ios::out|std::ios::in | std::ios::binary);
		file.write( reinterpret_cast<char *>(&vectorFila[0]), size_file*sizeof(double) );
		file.close();

		delete[] vectorFila;
		path++;
		
		//cout<<path<<"\n";
	}
}


std::vector<std::pair<Bits,float>> Recommender::computerNearestNeighbors(
		std::string iduser,int r){
	auto p=user[iduser];
	std::vector<std::pair<Bits,float>> distances;
	float distance=0;
	for(auto key:dataUsers){
		if(key.first!=p){
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

float Recommender::normalizerR(std::string _user, std::string item){
    float ratingN = 0;
    float diference = maxRating - minRating;
    ratingN = (2*(dataUsers[user[_user]][object[item]] - minRating) - diference)/diference;
    return ratingN;
}   
    
float Recommender::deNormalizerR(float NR){
    float ratingDN = 0;
    float diference = maxRating - minRating;
    ratingDN = (0.5*((NR +1) * diference) + minRating);
    return ratingDN;
}   

std::map<int, double> Recommender::get_items_similars(std::string address){
    size_t size_items = object.size()*3;

		std::fstream fin;
		std::map<int, double> similar_items;
		double *vector_items = new double[size_items];
		
		fin.open(address+Recommender::filename, std::ios::binary);
		fin.read( reinterpret_cast<char *>(&vector_items[0]), size_items*sizeof(double));
		
		size_t item = 0;
		for (size_t idx = 0; idx < size_items; ++idx){
			
			double dem1 = vector_items[++idx];
			double dem2 = vector_items[++idx];
			double prediction;

			if (fabs(dem1) <= epsilon || fabs(dem2) <= epsilon)
				prediction = 0;
			else
				prediction = vector_items[idx] / (sqrt(dem1) * sqrt(dem2));
				
			similar_items[item] = prediction;
			item += 1;
		}

		return similar_items;
}   

float Recommender::prediction(std::string userA, std::string item){
    string str = object[item].item.to_string();
	string address;
	for(auto it:str){
		address += it + "/";
	}
	address = address + "p.gbin";

	std::map<int,double> items = get_items_similars(address);
    
	float num = 0, den = 0;
    for(auto key:items){
        num += key.second * normalizerR(userA,item);
        den += key.second * normalizerR(userA,item);
    }
    if(fabs(den) <= den * epsilon)
		return 0;
	else
    	return deNormalizerR(num/den);
}   

#include "recommend.h"
#include <fstream>
#include "tools.h"
#include "metrica.cpp"

void Recommender::loadData(std::string path){
	fstream f;
	f.open(path,std::ios::in);
	
	std::string temp;
	int cp=0;
	int cq=0;
	Bits tempp;
	Bits tempq;
	if(getline(f,temp)) cout<<"init \n"; 
	while(getline(f,temp)){
		vector<string> fields=split(temp,',');
		auto p=user.find(fields[0]);
		auto q=object.find(fields[1]);
		if(p==user.end()){
			user[fields[0]]=Bits(cp);
			tempp=Bits(cp);
			cp++;
		}
		else tempp=p->second;
		if(q==object.end()){
			object[fields[1]]=Bits(cq);
			tempq=Bits(cq);
			cq++;
		}
		else tempq=q->second;
		dataUsers[tempp][tempq]=std::stof(fields[2]);
	}
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

std::pair<Bits,float> Recommender::normalizar(std::string iduser,std::string iditem){
	auto idu=user[iduser];
	auto idit=object[iditem];
	float val=(2*(dataUsers[idu][idit]-min)-(max-min))/(max-min);
	return std::make_pair(idit,val); 
}
/*
float Recommender::prediccion(std::string iduser,string iditem){
	
}*/


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

void Recommender::generateMatrixDisco(){
    int ixx=0;
	for(auto p=object.begin();p!=object.end();){
		++p;
		auto q=p;
		
		double *vectorFila = new double[object.size()*3];
		
		int j=0;
		for(;q!=object.end() ;++q){
	        double *valores = computeSimilarity3(p->first,q->first);
	        vectorFila[j] = valores[0];
	        vectorFila[j+1] = valores[1];
	        vectorFila[j+2] = valores[2];
	        j +=3;
	        delete[] valores;
	        
		}
		
		//guardar a disco toda la fila ( el vectorFila )
				
		
		
		
		
		
		
		
		
		delete[] vectorFila;
		cout<<ixx++<<"\n";
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


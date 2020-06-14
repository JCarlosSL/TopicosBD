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

double* Recommender::computeSimilarity3(std::string band1,std::string band2){
	
	double *valores = new double[3];
	
	double num=0;
	double den1=0;
	double den2=0;
	
	auto bandaA=object[band1];
	auto bandaB=object[band2];
	    
    if (bandaUsrPuntaje[Bits(bandaA)].size() > bandaUsrPuntaje[Bits(bandaB)].size()){
        int aux = bandaA;
        bandaA = bandaB;
        bandaB = aux;
    }
    
    for(auto key:bandaUsrPuntaje[Bits(bandaA)]){
    
        auto usr = key.first;
        float puntaje = key.second;
        
        if(bandaUsrPuntaje[Bits(bandaB)].find(usr) !=   bandaUsrPuntaje[Bits(bandaB)].end()){
            double avg = averages[usr.getitem()];
            double num1 = (puntaje - avg);
            double num2 = (bandaUsrPuntaje[Bits(bandaB)][usr] - avg);
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
    
std::map<string, float> readmatrix(string address){
    std::fstream fin;
    fin.open(address, std::ios::binary);
    
}   
    
float prediction(string userA, string item){
    map<string,float> items = readMatrix();
    float num = 0, den = 0;
    for(auto key:items){
        num = key.first + normalizerR(userA,key.second);
        den = key.first + normalizerR(userA,key.second);
    }
        
    return deNormalizerR(num/den);
}   
  


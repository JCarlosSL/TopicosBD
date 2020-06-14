#include <cmath>
float manhattan(std::map<Bits,float> rating1,std::map<Bits,float> rating2){
	float distance=0;
	bool verbose=false;
	for( auto key:rating1){
		auto it=rating2.find(key.first);
		if(it!=rating2.end()){
			distance+=abs(key.second - (*it).second);
			verbose=true;
		}
	}
	if( verbose==false) return -1;
	return distance;
	
}

float euclides(std::map<Bits,float> rating1,std::map<Bits,float> rating2){
	float distance=0;
	bool verbose=false;
	for( auto key:rating1){
		auto it=rating2.find(key.first);
		if(it!=rating2.end()){
			distance+=pow(abs(key.second - (*it).second),2);
			verbose=true;
		}
	}
	if( verbose==false) return -1;
	return sqrt(distance);
	
}

float minkowsky(std::map<Bits,float> rating1,std::map<Bits,float> rating2,int r){
	float distance=0;
	bool verbose=false;
	for( auto key:rating1){
		auto it=rating2.find(key.first);
		if(it!=rating2.end()){
			distance+=pow(abs(key.second - (*it).second),r);
			verbose=true;
		}
	}
	if( verbose==false) return -1;
	return pow(distance,1/r);
	
}


float pearson(std::map<Bits,float> rating1,std::map<Bits,float> rating2){
	bool verbose=false;
	float sumxy=0;
	float sumx=0;
	float sumx2=0;
	float sumy=0;
	float sumy2=0;
	float n=0;
	
	for( auto key:rating1){
		auto it=rating2.find(key.first);
		if(it!=rating2.end()){
			sumxy += key.second * (*it).second;
            sumx += key.second;
            sumx2 += pow(key.second,2);
            sumy += (*it).second;
            sumy2 += pow((*it).second,2);
            n+=1;
			verbose=true;
		}
	}
	if( verbose==false) return 0;
	return (sumxy-(sumx*sumy)/n)/(sqrt(sumx2-pow(sumx,2)/n)*sqrt(sumy2-pow(sumy,2)/n));
	
}


float coseno(std::map<Bits,float> rating1,std::map<Bits,float> rating2){
	bool verbose=false;
	float productpoint=0;
	float normx=0;
	float normy=0;
	
	for( auto key:rating1){
		auto it=rating2.find(key.first);
		if(it!=rating2.end()){
			productpoint += key.second * (*it).second;
			verbose=true;
		}
		normx+=pow(key.second,2);
	}
	
	for(auto key:rating2){
		normy+=pow(key.second,2);
	}
	
	if( verbose==false) return 0;
	return productpoint/(sqrt(normx)*sqrt(normy));
	
}


float jaccard(std::map<Bits,float> rating1,std::map<Bits,float> rating2){
	bool verbose=false;
	float intersect=0;
	float nsiz1=rating1.size();
	float nsiz2=rating2.size();
	
	for( auto key:rating1){
		auto it=rating2.find(key.first);
		if(it!=rating2.end()){
			intersect+=1;
			verbose=true;
		}
	}
	
	if( verbose==false) return 0;
	float n=nsiz1+nsiz2-intersect;
    return 1-intersect/n;
	
}



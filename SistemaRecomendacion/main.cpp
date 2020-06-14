#include <iostream>
#include <bits/stdc++.h>
#include "preprocesar.cpp"
#include "recommend.cpp"

using namespace std;

std::string path;
char limit;

void listmetricas(){
	cout<<"1 manhattan \n";
	cout<<"2 euclides \n";
	cout<<"3 minkowsky \n";
	cout<<"4 coseno \n";
	cout<<"5 jaccard \n";
	cout<<"6 pearson \n";
}

void list(){
	cout<<"1. metricas \n";
	cout<<"2. computeSimilarity \n";
	cout<<"3. generateMatrixDisco \n";
	cout<<"4. computenearestNeighbors \n";
	cout<<"5. recomendacion por usuario 'n";
	cout<<"6. prediccion por items \n";
}

int main(){

	//Preprocesamiento de la data
	 
	/*DataPreprocessing prepro("datasetSmall/ratings.csv");
	prepro.DataRecognition();

	char limit = prepro.getlim();
	char strip = prepro.getdiv();	
	*/
	//sistema de recomendacion
	 
	Recommender data;

	//data.loadData("BX-Book-Ratings.csv");
	//data.loadData("ml-25m/ratings.csv");
	//cout<<data.computeSimilarity("Star Wars","Jaws");
	//data.loadData("Movie_Ratings.csv");
	data.loadData("ml-latest-small/ratings.csv",',');
	//data.loadData("ml-latest/ratings.csv");
	//data.loadData("bandas.csv");
	//std::cout<<data.user.size()<<" "<<data.object.size();

	//cout<<data.computeSimilarity("You Got Mail","The Matrix");
	//cout<<data.computeSimilarity("Deadmau5","Slightly Stoopid");
	data.generateMatrixDisco();
	//cout<<data.computeSimilarity("Alien","Avatar");
	//auto p=data.user.find("Stephen");
	//auto q=data.user.find("Amy");
	//cout<<jaccard(data.dualhash[p->second],
	//		data.dualhash[q->second]);
//	data.dualhash.show();	
	//auto v =data.influences("332",3);

	//cout<<data.recommender(v,"21")<<"\n";
	

	return 0;
}

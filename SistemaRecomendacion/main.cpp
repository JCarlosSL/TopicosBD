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

	data.loadData("movie_ratings/Movie_Ratings.csv",',');
	data.loadDataItems("movie_ratings/Movie_Ratings.csv",',');
	//data.loadData("Data/bandas2.csv",'\t');
	//data.loadData("Data/bandas2.csv",'\t');
	//data.loadData("ml-25m/ratings.csv",',');
	//data.loadDataItems("ml-25m/ratings.csv",',');
	//data.loadData("BX-Dump/BX-Book-Ratings.csv",';');
	//data.loadDataItems("BX-Dump/BX-Book-Ratings.csv",';');
	//data.loadData("Movie_Ratings.csv",'\t');

	//cout<<data.computeSimilarity("213","2131");
	//cout<<data.computeSimilarity("Deadmau5","Slightly Stoopid");
	data.getAverage();
	data.generateMatrixDisco();
	//cout<<data.computeSimilarity("Alien","Avatar");
	//data.generateMatrix();
	cout<<"Recomendacion\nUsr, Item\n";
	string usr="";
	string item="";
	
	while(usr != "fin" || item!="fin"){
	    getline(cin, usr);
	    getline(cin, item);
	    cout<<usr<<", "<<item<<'\n';
	//	data.generatevectorDisco(item);
	    cout<<data.prediction(usr,item)<<"\n\n";
	}
	//cout<<data.computeSimilarity("Star Wars","Jaws");
	//data.loadData("ml-latest-small/ratings.csv",',');
	//data.loadData("ml-latest/ratings.csv");
	//data.loadData("bandas.csv");
	//std::cout<<data.user.size()<<" "<<data.object.size();

	//cout<<data.computeSimilarity("213","2131");
	//cout<<data.computeSimilarity("Deadmau5","Slightly Stoopid");
	//data.getAverage();
	//data.generateMatrixDisco();
	//cout<<data.computeSimilarity("Alien","Avatar");
	//data.generateMatrix();
	//cout<<data.prediction("David","Kacey Musgraves");
	//auto p=data.user.find("Stephen");
	//auto q=data.user.find("Amy");
	//cout<<jaccard(data.dualhash[p->second],
	//		data.dualhash[q->second]);
//	data.dualhash.show();	
	//auto v =data.influences("332",3);

	//cout<<data.recommender(v,"21")<<"\n";
	

	return 0;
}

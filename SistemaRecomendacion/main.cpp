#include <iostream>
#include <bits/stdc++.h>
#include "recommend.cpp"
#include "datasetconstants.h"
using namespace std;

std::string path;
char limit;
void DatasetLorde(){
    
    Recommender data(DataSetConstants::LORDE,true);
    data.getAverage();
    //data.generateMatrixDisco();
    cout<<data.prediction("David","Kacey Musgraves");
    cout<<data.prediction("David","Lorde");
    data.insertRatings("inRat.txt");
}

void DatasetMovieLeans25M(){
    Recommender data(DataSetConstants::MOVIELEANS27M);
    data.getAverage();
}

void DatasetBooks(){
	cout<<DataSetConstants::BOOKS<<endl;
	Recommender data(DataSetConstants::BOOKS,true);
	data.getAverage();
	//data.generateMatrixDisco();	
	
	string usuario="",item="";
	cout<<"coseno ajustado \n"<<endl;
	while(usuario!="fin" and item!="fin"){
		cout<<"usuario: ";
		getline(cin,usuario);
		cout<<"item: ";
		getline(cin,item);
		auto t1 = chrono::high_resolution_clock::now();
		float pr= data.prediction1(usuario,item);
		cout<<"prediccion: "<<pr<<endl;
		auto t2 = chrono::high_resolution_clock::now();
		auto d = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		cout<<"duracion "<<d/1000.0<<"\n";	
	}

}

int main(){
	DatasetLorde();
    //DatasetMovieLeans25M();
    DatasetBooks();
    return 0;
}

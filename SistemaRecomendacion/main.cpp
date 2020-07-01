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
}
void DatasetMovieLeans25M(){
    Recommender data(DataSetConstants::MOVIELEANS27M);
    data.getAverage();
}

void DatasetBooks(){
	cout<<DataSetConstants::BOOKS<<endl;
	Recommender data(DataSetConstants::BOOKS);
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
		cout<<"prediccion: "<<data.prediction(usuario,item);
		auto t2 = chrono::high_resolution_clock::now();
		auto d = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		cout<<"\n duracion "<<d/1000.0<<"\n";	
	}

}

int main(){
	//DatasetLorde();
    //DatasetMovieLeans25M();
    DatasetBooks();
    return 0;
}

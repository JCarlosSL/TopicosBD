#include <iostream>
#include <bits/stdc++.h>
#include "recommend.cpp"

using namespace std;


int main(){

	Recommender data;

	data.loadData("movie_ratings/Movie_Ratings.csv",',');
	data.loadDataItems("movie_ratings/Movie_Ratings.csv",',');
	//data.loadData("Data/bandas2.csv",'\t');
	//data.loadData("ml-25m/ratings.csv",',');
	//data.loadDataItems("ml-25m/ratings.csv",',');
	//data.loadData("BX-Dump/BX-Book-Ratings.csv",';');
	//data.loadDataItems("BX-Dump/BX-Book-Ratings.csv",';');
    	//data.loadData("ml-latest27/ratings.csv",',');
	//data.loadDataItems("ml-latest27/ratings.csv",',');
	//data.loadData("pdf/slopeOne.csv",',');
	data.getAverage();
	//data.generateMatrixDisco();
	//data.generateMatrix();
	//cout<<data.computeSimilarity("Alien","Avatar");
	
	cout<<"Recomendacion\nUsr, Item\n";
	string usr="";
	string item="";
	
	while(usr != "fin" || item!="fin"){
	    getline(cin, usr);
	    getline(cin, item);
	    cout<<usr<<", "<<item<<'\n';
		cout<<data.prediction(usr,item)<<"\n\n";
	}
	
	/*
	int numItems = data.bandaUsrPuntaje.size();
	vector<vector<float>> matriz = data.generateMatrixRAMSlopeOne();
    	
	for(int i=0; i<numItems; i++){
	    for (int j=0; j<numItems*2; j+=2){
	        cout<<"("<<matriz[i][j]<<", "<<matriz[i][j+1]<<") ";	        
	    }
	    cout<<"\n";
	}
	*/
    	//map<int,float> predictions;
    	//predictions = data.predictionWSlopeOne("Ben", matriz);
    	//predictions = data.predictionWSlopeOne("Clara", matriz);
    	//predictions = data.predictionWSlopeOne("Daisy", matriz);
	//for(auto key:predictions)
	//	cout<<key.first<<" -> "<<key.second<<endl;

	//vector<vector<float>> matriz = data.generateMatrixRAMSlopeOne();
	//cout<<data.predictionSlopeOneRAM("Patrick C","Village",matriz)<<"\n";

	return 0;
}

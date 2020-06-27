#include <iostream>
#include <bits/stdc++.h>
#include "recommend.cpp"

using namespace std;

std::string path;
char limit;

int main(){

	Recommender data;

	// data.loadData("movie_ratings/Movie_Ratings.csv",',');
	// data.loadDataItems("movie_ratings/Movie_Ratings.csv",',');
	//data.loadData("Data/bandas2.csv",'\t');
	//data.loadData("Data/bandas2.csv",'\t');
	//data.loadData("ml-25m/ratings.csv",',');
	//data.loadDataItems("ml-25m/ratings.csv",',');
	data.loadData("BX-Dump/BX-Book-Ratings.csv",';');
	data.loadDataItems("BX-Dump/BX-Book-Ratings.csv",';');
	
	// //data.loadData("Movie_Ratings.csv",'\t');
    	//data.loadData("ml-latest27/ratings.csv",',');
	//data.loadDataItems("ml-latest27/ratings.csv",',');
	// data.loadData("pdf/slopeOne.csv",',');
	// data.loadDataItems("pdf/slopeOne.csv",',');

	// data.loadData("pdf/lorde.csv",',');
    // data.loadDataItems("pdf/lorde.csv",',');

	//cout<<data.computeSimilarity("213","2131");
	//cout<<data.computeSimilarity("Deadmau5","Slightly Stoopid");
    //data.getAverage();
	//data.generateMatrixDisco();
	//data.generateMatrix();
	//cout<<data.computeSimilarity("Alien","Avatar");
	/*
	cout<<"Recomendacion\nUsr, Item\n";
	string usr="";
	string item="";
	
	while(usr != "fin" || item!="fin"){
	    getline(cin, usr);
	    getline(cin, item);
	    cout<<usr<<", "<<item<<'\n';
		cout<<data.prediction1(usr,item)<<"\n\n";
	}*/
	
	cout << data.object["0345296060"] << endl;
	// for(auto i:data.object)
	// 	cout << i.first << "[-]" << i.second << endl;	
	int numItems = data.bandaUsrPuntaje.size();
	cout << "numitems" << numItems << endl;
	vector<vector<float>> matriz = data.generateMatrixRAMSlopeOne();
	// for(int i=0; i<numItems; i++){
	//     for (int j=0; j<numItems*2; j+=2){
	//         cout<<"("<<matriz[i][j]<<", "<<matriz[i][j+1]<<") ";	        
	//     }
	// 	break;
	//     cout<<"\n";
	// }
	cout << "generate prediction" << endl;
	map<int,float> predictions;
    cout << data.predictionSlopeOneRAM("276746","194864",matriz);
	//predictions = data.predictionWSlopeOne("194864", matriz);
	// cout << "Prediction" << endl;
	// for(auto key:predictions)
	//  	cout<<key.first<<" -> "<<key.second<<endl;

	// vector<vector<float>> matriz = data.generateMatrixRAMSlopeOne();
	// cout<<data.predictionSlopeOneRAM("Patrick C","Village",matriz)<<"\n";

    // // cout<<data.prediction("David","Kacey Musgraves");

	return 0;
}

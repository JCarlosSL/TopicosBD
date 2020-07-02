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
    data.generateMatrixDiscoAC();
    cout<<data.prediction("David","Kacey Musgraves")<<'\n';
    cout<<data.prediction1("David","Kacey Musgraves")<<'\n';
    cout<<data.predictionSlopeOneRAM("David","Kacey Musgraves",data.generateMatrixRAMSlopeOne())<<'\n';
    cout<<data.predictionSlopeOneRAM("David","Kacey Musgraves");
}

void DatasetMovieLeans25M(){
    Recommender data(DataSetConstants::BOOKS,true);
    //data.getAverage();
	//data.insertRatings("inRat.txt");
}


int main(){
    DatasetLorde();
	//DatasetMovieLeans25M();
}

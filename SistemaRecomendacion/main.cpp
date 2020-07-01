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
//    cout<<data.prediction("juana","Kacey Musgraves");

    data.insertRatings("inRat.txt");
	data.serializeUpdate();
    
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

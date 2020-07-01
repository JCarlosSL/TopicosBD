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
//    data.generateMatrixDisco();
    cout<<data.prediction("David","Kacey Musgraves");
    data.insertRatings("inRat.txt");
    
}

void DatasetMovieLeans25M(){
    Recommender data(DataSetConstants::MOVIELEANS27M);
    data.getAverage();
}


int main(){
    DatasetLorde();
}

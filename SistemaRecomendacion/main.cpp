#include <iostream>
#include <bits/stdc++.h>
#include "recommend.cpp"
using namespace std;

std::string path;
char limit;

int main(){

    //FileManager(DataSetConstants::LORDE);
    //Preprocesamiento de la data

    /*DataPreprocessing prepro("datasetSmall/ratings.csv");
    prepro.DataRecognition();

    char limit = prepro.getlim();
    char strip = prepro.getdiv();
    */
    //sistema de recomendacion

    Recommender data;

    // data.loadData("movie_ratings/Movie_Ratings.csv",',');
    // data.loadDataItems("movie_ratings/Movie_Ratings.csv",',');
    //data.loadData("Data/bandas2.csv",'\t');
    //data.loadData("Data/bandas2.csv",'\t');
    //data.loadData("ml-25m/ratings.csv",',');
    //data.loadDataItems("ml-25m/ratings.csv",',');
    //data.loadData("BX-Dump/BX-Book-Ratings.csv",';');
    //data.loadDataItems("BX-Dump/BX-Book-Ratings.csv",';');
    //data.loadData("Movie_Ratings.csv",'\t');
    //data.loadData("ml-latest27/ratings.csv",',');
    //data.loadDataItems("ml-latest27/ratings.csv",',');
    data.loadData("pdf/lorde.csv",',');
    data.loadDataItems("pdf/lorde.csv",',');

    //cout<<data.computeSimilarity("213","2131");
    //cout<<data.computeSimilarity("Deadmau5","Slightly Stoopid");
    data.getAverage();
    //data.generateMatrixDisco();
    //data.generateMatrix();
    //cout<<data.computeSimilarity("Alien","Avatar");
    //data.generateMatrix();
    /*
    cout<<"Recomendacion\nUsr, Item\n";
    string usr=""loadDataItems;
    string item="";

    while(usr != "fin" || item!="fin"){
        getline(cin, usr);
        getline(cin, item);
        cout<<usr<<", "<<item<<'\n';
    //	data.generatevectorDisco(item);
        cout<<data.prediction(usr,item)<<"\n\n";
    }
    */
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
    cout<<data.prediction("David","Kacey Musgraves");
    //auto p=data.user.find("Stephen");
    //auto q=data.user.find("Amy");
    //cout<<jaccard(data.dualhash[p->second],
    //		data.dualhash[q->second]);
    //	data.dualhash.show();
    //auto v =data.influences("332",3);

    //cout<<data.recommender(v,"21")<<"\n";
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

    // vector<vector<float>> matriz = data.generateMatrixRAMSlopeOne();
    // cout<<data.predictionSlopeOneRAM("Patrick C","Village",matriz)<<"\n";
}

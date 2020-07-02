#include <iostream>
#include <bits/stdc++.h>
#include "recommend.cpp"
#include "datasetconstants.h"
using namespace std;

std::string path;
char limit;
void DatasetLorde(){
    Recommender data(DataSetConstants::LORDE);
    data.getAverage();
    data.generateMatrixDisco();
    //cout<<data.prediction("David","Kacey Musgraves");
    auto t1 = std::chrono::high_resolution_clock::now();
    cout<<data.prediction("Ben","Lorde");
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();  
    cout<<"duracion de predecir sin disco " << duration/1000.0<<"\n";
}
void DatasetMovieLeans27M(){
    Recommender data(DataSetConstants::MOVIELEANS27M);
    cout << "termino cargar datos" << endl;
    string user,item;
    cout << "input user \t"; cin>> user;
    cout << "input item \t" ;cin>> item;
    while (user!="q" && item!="q")
    {
        data.getAverage();
        auto t1 = std::chrono::high_resolution_clock::now();
        cout << "prediccion" <<  data.prediction(user,item) << endl;
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();  
        cout<<"Tiempo " << duration/1000.0<<"\n";
        cout << "input user \t "; cin>> user;
        cout << "input item \t" ;cin>> item;

    }
    //data.getAverage();
}
void AjusteCosenoMovieLeans27M(){
    Recommender data(DataSetConstants::LORDE);
    string user,item;
    cout << "input user \t"; cin>> user;
    cout << "input item \t" ;cin>> item;
    while (user!="q" && item!="q")
    {
        data.getAverage();
        auto t1 = std::chrono::high_resolution_clock::now();
        data.prediction1(user,item);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();  
        cout<<"Tiempo " << duration/1000.0<<"\n";
        cout << "input user \t "; cin>> user;
        cout << "input item \t" ;cin>> item;
    }
    
}
void slopOneMovieLeans27m(){
    Recommender data(DataSetConstants::MOVIELEANS27M);
    string user,item;
    cout << "input user \t"; cin>> user;
    cout << "input item \t" ;cin>> item;
    while (user!="q" && item!="q")
    {
        data.getAverage();
        int itemkey=data.object[item];
        cout << "item pos" << itemkey <<"--" <<item << endl;
        vector<vector<float>> matriz = data.generateMatrixRAMSlopeOne(itemkey);
        auto t1 = std::chrono::high_resolution_clock::now();
        cout << "prediccion " << data.predictionSlopeOneRAM(user,item,matriz) << endl;
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();  
        cout<<"Tiempo " << duration/1000.0<<"\n";
        cout << "input user \t "; cin>> user;
        cout << "input item \t" ;cin>> item;
    }
}
int main(){
    //DatasetLorde();
    //DatasetMovieLeans27M();
    //AjusteCosenoMovieLeans27M();
    slopOneMovieLeans27m();
}
void calculateTime(){
    auto t1 = std::chrono::high_resolution_clock::now();

    //float pred = data.prediccion_cosenoAjustado_cuda_sin_disco("1", "5");

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();  
    cout<<"duracion de predecir sin disco " << duration/1000.0<<"\n";
}
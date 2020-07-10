#include <iostream>
#include <bits/stdc++.h>
#include "recommend.cpp"
#include "datasetconstants.h"
using namespace std;

std::string path;
char limit;

/////Dataset Lorde///////////
void DatasetLorde(){
    
    Recommender data(DataSetConstants::LORDE,true);
    data.getAverage();
    //data.generateMatrixDisco();
    
    data.generateMatrixDiscoAC();
    data.generateMatrixDiscoSO();
    cout<<data.predictionDisk("David","Kacey Musgraves");
    cout<<data.predictionRAM("David","Kacey Musgraves")<<'\n';
    //cout<<data.predictionDisk("David","Lorde");
    data.insertRatings("inRat2.txt");
	data.serializeUpdate();
    cout<<data.predictionDisk("David","Kacey Musgraves")<<'\n';
    cout<<data.predictionRAM("David","Kacey Musgraves")<<'\n';
    cout<<data.predictionSlopeOneRAM("David","Kacey Musgraves",data.generateMatrixRAMSlopeOne())<<'\n';
    cout<<data.predictionSlopeOneDisk("David","Kacey Musgraves");
}


void datasetLode1(){
    Recommender data(DataSetConstants::LORDE);
    data.getAverage();
    data.generateMatrixDiscoAC();
    //cout<<data.predictionDisk("David","Kacey Musgraves");
    auto t1 = std::chrono::high_resolution_clock::now();
    cout<<data.predictionDisk("Ben","Lorde");
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();  
    cout<<"duracion de predecir sin disco " << duration/1000.0<<"\n";
}

//////////FC items(Coseno Ajustado) para books////////////////////////////
void DatasetBooks(){
	Recommender data(DataSetConstants::BOOKS,false,0,10);
	data.getAverage();
	//data.generateMatrixDiscoAC();	
	
	string usuario="",item="";
	while(usuario!="fin" and item!="fin"){
		cout<<"usuario: ";getline(cin,usuario);
		cout<<"item: ";getline(cin,item);
		
		auto t1 = chrono::high_resolution_clock::now();
		
		float pr= data.predictionDisk(usuario,item);
		
		cout<<"prediccion: "<<pr<<endl;
		
		auto t2 = chrono::high_resolution_clock::now();
		auto d = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		
		cout<<"duracion "<<d/1000.0<<"\n";	
	}

}

///////////FC usuarios Books///////////////////////////////////
void DatasetBooksUsuarios(){
	Recommender data(DataSetConstants::BOOKS);	
	string usuario="",item="";
	int k=0;
	while(usuario!="fin" and item!="fin"){
		cout<<"usuario: ";getline(cin,usuario);
		cout<<"item: ";getline(cin,item);
		cout<<"k: ";cin>>k;
		cin.ignore();
		auto t1 = chrono::high_resolution_clock::now();	

		auto inf = data.influences(usuario,k);
		float pr = data.recommender(inf,item);
		
		cout<<"prediccion: "<<pr<<endl;
		auto t2 = chrono::high_resolution_clock::now();
		auto d = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		
		cout<<"duracion "<<d/1000.0<<"\n";	
	}

}

///////FC items SlopeOne Book///////////////////////////////
void slopOneBook(){
    Recommender data(DataSetConstants::BOOKS,0,10);
    string user="",item="";
    data.getAverage();
    while (user!="fin" && item!="fin"){
     	cout << "input user: "; cin>> user;
        cout << "input item: " ;cin>> item;
        int itemkey=data.object[item];
        vector<vector<float>> matriz = data.generateMatrixRAMSlopeOne(itemkey);
        auto t1 = std::chrono::high_resolution_clock::now();
        cout << "prediccion: " << data.predictionSlopeOneRAM(user,item,matriz) << endl;
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();  
        cout<<"Tiempo " << duration/1000.0<<"\n";
       
    }
}

////////////////Calculo del Error Cuadratico medio MOVIE and TV////////////////////////
void DatasetBooksError(){
	auto t1 = chrono::high_resolution_clock::now();
	Recommender data(DataSetConstants::MOVIETV,true);
	auto t2 = chrono::high_resolution_clock::now();
	auto d = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	cout<<"duracion "<<d/1000.0<<"\n";
	data.getAverage();
	cout<<"error"<<endl;	
	string usuario="";
	while(usuario!="fin"){
		getline(cin,usuario);
		float pr= data.errorcuadratico(usuario);
		cout<<"error: "<<pr<<"\n";
			
	}
}

////////////////FC items(Coseno Ajustado) MOVIE and TV//////////////////////////////
void DatasetMovieAndTV(){
	cout<<DataSetConstants::MOVIETV<<endl;
	Recommender data(DataSetConstants::MOVIETV,true,1,5);
	data.getAverage();
	//data.generateMatrixDiscoAC();		
	string usuario="",item="";
	while(usuario!="fin" and item!="fin"){
		cout<<"usuario: ";
		getline(cin,usuario);
		cout<<"item: ";
		getline(cin,item);
		auto t1 = chrono::high_resolution_clock::now();
		
		float pr= data.predictionDisk(usuario,item);
		
		cout<<"prediccion: "<<pr<<endl;
		auto t2 = chrono::high_resolution_clock::now();
		auto d = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		cout<<"duracion "<<d/1000.0<<"\n";	
	}

}

///////////////FC usuarios Movie and Tv ////////////////////////
void DatasetMovieAndTVUsuarios(){
	cout<<DataSetConstants::MOVIETV<<endl;
	Recommender data(DataSetConstants::MOVIETV);	
	string usuario="",item="";
	int k=0;
	while(usuario!="fin" and item!="fin"){
		cout<<"usuario: ";getline(cin,usuario);
		cout<<"item: ";getline(cin,item);
		auto t1 = chrono::high_resolution_clock::now();
		
		cout<<"k: ";cin>>k;
		cin.ignore();

		auto inf = data.influences(usuario,k);
		float pr = data.recommender(inf,item);
		
		cout<<"prediccion: "<<pr<<endl;
		
		auto t2 = chrono::high_resolution_clock::now();
		auto d = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		
		cout<<"duracion "<<d/1000.0<<"\n";	
	}

}

void DatasetMovieLeans27M(){
    Recommender data(DataSetConstants::MOVIERATINGS);

    data.getAverage();
    data.generateMatrixDiscoAC();
    data.generateMatrixDiscoSO();

    cout<<data.predictionDisk("Patrick C","Alien")<<'\n';
    cout<<data.predictionRAM("Patrick C","Alien")<<'\n';
    cout<<data.predictionSlopeOneRAM("Patrick C","Alien",data.generateMatrixRAMSlopeOne())<<'\n';
    cout<<data.predictionSlopeOneDisk("Patrick C","Alien")<<'\n';

    // cout << "termino cargar datos" << endl;
    // string user,item;
    // cout << "input user \t"; cin>> user;
    // cout << "input item \t" ;cin>> item;
    // data.getAverage();
    // while (user!="q" && item!="q")
    // {
    //     auto t1 = std::chrono::high_resolution_clock::now();
    //     cout << "prediccion" <<  data.predictionDisk(user,item) << endl;
    //     auto t2 = std::chrono::high_resolution_clock::now();
    //     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();  
    //     cout<<"Tiempo " << duration/1000.0<<"\n";
    //     cout << "input user \t "; cin>> user;
    //     cout << "input item \t" ;cin>> item;

    // }
    //data.getAverage();
}
void AjusteCosenoMovieLeans27M(){
    Recommender data(DataSetConstants::LORDE);
    string user,item;
    cout << "input user \t"; cin>> user;
    cout << "input item \t" ;cin>> item;
    data.getAverage();
    while (user!="q" && item!="q")
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        data.predictionRAM(user,item);
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
    data.getAverage();
    while (user!="q" && item!="q")
    {
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


void calculateTime(){
    Recommender data(DataSetConstants::MOVIERATINGS,true);
    data.getAverage();
    data.getMaxItems();
    data.generateMatrixDiscoAC();
    data.generateMatrixDiscoSO();
    auto t1 = std::chrono::high_resolution_clock::now();

    auto p = data.predictionAdjustCosine("Josh","Blade Runner");
    //float pred = data.prediccion_cosenoAjustado_cuda_sin_disco("1", "5");

    auto t2 = std::chrono::high_resolution_clock::now();
    cout<< p << endl;
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();  
    cout<<"duracion de predecir sin disco " << duration/1000.0<<"\n";
}

int main(){
    //DatasetMovieAndTV();
    //slopOneBook();
    DatasetBooks();
    //DatasetBooksUsuarios();
    //DatasetBooksError();
    //DatasetMovieAndTVUsuarios();
    //DatasetLorde();
    //calculateTime();
    //DatasetMovieLeans27M();
    //AjusteCosenoMovieLeans27M();
    //slopOneMovieLeans27m();
    return 0;
}

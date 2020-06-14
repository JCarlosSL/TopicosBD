#include "tools.h"
#include "preprocesar.h"

DataPreprocessing::DataPreprocessing(string path){
	filename=path;	
}


char DataPreprocessing::getlim(){
	return lim;
}

char DataPreprocessing::getdiv(){
	return div;
}

void DataPreprocessing::DataRecognition(){
	fstream f;
	f.open(filename,ios::in);
	string temp;
	if(getline(f,temp)){
		lim=findS(Strip,temp);
		div=findS(Split,temp);
	}
	vector<string> head=split(temp,div);
	if(head[0]!="") type=1;
	else type=0;
	f.close();
}


void DataPreprocessing::DataCleaning(){
	fstream f,g;
	f.open("temp.csv",ios::out);
	g.open(filename,ios::in);
	if(type==0){
		string temp;
		vector<string> data;
		if(getline(g,temp)){
			data=split(temp,div);
			vector<string> sub(data.begin()+1,data.end());
			data=forstrip(sub,lim);	
		}
		while(getline(g,temp)){
			vector<string> fields=split(temp,div);
			string objeto=strip(fields[0],lim);
			for(int i=1;i<fields.size();++i){
				if(fields[i]!=""){
					f<<data[i-1]<<"\t"<<objeto<<"\t"<<fields[i]<<"\n";
				}
			}
		}
	}
	else{
		string temp;
		while(getline(g,temp)){
			vector<string> fields=split(temp,div);
			f<<strip(fields[0],lim);
			for(int i=1;i<fields.size();++i){
				f<<"\t"<<strip(fields[i],lim);
			}
			f<<"\n";
		}
	}
	f.close();
	g.close();
	string syst="cp temp.csv "+filename;
	system(syst.c_str());
}

#ifndef Tools_H
#define Tools_H
#include <bits/stdc++.h>
#include "bits.h"

using namespace std;

vector<string> split(const string &s,char delimiter){
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while(getline(tokenStream,token,delimiter)){
		tokens.push_back(token);
	}
	return tokens;
}

string trim(const string &str){
	if(str.front() == '"'){
		return str.substr(1,str.size()-2);
	}
	return str;
}

string strip(const string &str,char delimiter){
	size_t first = str.find_first_not_of(delimiter);
	size_t last = str.find_last_not_of(delimiter);
	return str.substr(first,last-first+1);
}

vector<string> forstrip(const vector<string> &str,char delimiter){
	vector<string> fields;
	for (auto v:str){
		fields.push_back(strip(v,delimiter));
	}
	return fields;
}

char findS(const vector<char> &S,const string &str){
	for(auto s:S){
		size_t found=str.find(s);
		if(found!=string::npos){
			return s;
		}
	}
	return '0';
}

bool sortbysec(const std::pair<Bits,float> &a,
		const std::pair<Bits,float> &b){
	return (a.second>b.second);
}




#endif
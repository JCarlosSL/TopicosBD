#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/bitset.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <sstream>
#include "bits.h"
#include <cassert>
typedef  unsigned short int	bits;
//typedef std::bitset<19> bits;
typedef std::unordered_map<std::string,bits> typeUMap;
typedef std::map<bits,float> typeMap0;
typedef std::map<bits,typeMap0> typeMapBU;
class FileManager
{
public:
    FileManager(){

    };
    typeUMap recoverUser(std::string filename);
    typeUMap recoverObject(std::string filename);
    typeMapBU recoverBandaUsers(std::string file);
    typeMapBU recoverBandaUsersPuntaje(std::string file);
    void saveUser(typeUMap &userMap,std::string filename);
    void saveObject(typeUMap &userMap,std::string filename);
    void saveBandaUsers(typeMapBU &userMap,std::string filename);
    void saveBandaUsersPuntaje(typeMapBU &userMap,std::string filename);
private:

};

#endif // FILEMANAGER_H
    
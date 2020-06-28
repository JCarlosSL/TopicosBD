#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/bitset.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
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
    typeUMap recoverUser(std::string filename){
        typeUMap map;
        {
            std::ifstream ifs(filename, std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia>>map;
        }
        return map;
    }

    typeUMap  recoverObject(std::string filename){
        typeUMap map;
        {
            std::ifstream ifs(filename, std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia>>map;
        }
        return map;
    }

    typeMapBU recoverBandaUsers(std::string file){
        typeMapBU map;
        {
            std::ifstream ifs(file, std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia>>map;
        }
        return map;
    }

    typeMapBU recoverBandaUsersPuntaje(std::string file){
        typeMapBU map;
        {
            std::ifstream ifs(file, std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia>> map;
        }
        return map;
    }

    void saveUser(typeUMap &userMap, std::string filename){
        std::ofstream ofs(filename,std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        oa<<userMap;
    }

    void saveObject(typeUMap &userMap, std::string filename){
        std::ofstream ofs(filename,std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        oa<<userMap;

    }

    void saveBandaUsers(typeMapBU &userMap, std::string filename){
        std::ofstream ofs(filename,std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        oa<<userMap;
    }

    void saveBandaUsersPuntaje(typeMapBU &userMap, std::string filename){
        std::ofstream ofs(filename,std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        oa<<userMap;
    }

private:

};

#endif // FILEMANAGER_H

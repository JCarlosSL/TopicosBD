#ifndef SERIALIZER_H
#define SERIALIZER_H
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
typedef  unsigned int userOrItemKeyType;
typedef std::unordered_map<std::string,userOrItemKeyType> UserOrItemMap;
typedef std::map<userOrItemKeyType,std::map<userOrItemKeyType,float>> MatrixDataMap;
class Serializer
{
public:
    Serializer(){
    };
    UserOrItemMap recoverUser(std::string filename){
        UserOrItemMap map;
        {
            std::ifstream ifs(filename, std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia>>map;
        }
        return map;
    }
    UserOrItemMap  recoverObject(std::string filename){
        UserOrItemMap map;
        {
            std::ifstream ifs(filename, std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia>>map;
        }
        return map;
    }
    MatrixDataMap recoverBandaUsers(std::string file){
        MatrixDataMap map;
        {
            std::ifstream ifs(file, std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia>>map;
        }
        return map;
    }
    MatrixDataMap recoverBandaUsersPuntaje(std::string file){
        MatrixDataMap map;
        {
            std::ifstream ifs(file, std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia>> map;
        }
        return map;
    }
    void saveUser(UserOrItemMap &userMap, std::string filename){
        std::ofstream ofs(filename,std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        oa<<userMap;
    }

    void saveObject(UserOrItemMap &userMap, std::string filename){
        std::ofstream ofs(filename,std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        oa<<userMap;

    }
    void saveBandaUsers(MatrixDataMap &userMap, std::string filename){
        std::ofstream ofs(filename,std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        oa<<userMap;
    }
    void saveBandaUsersPuntaje(MatrixDataMap &userMap, std::string filename){
        std::ofstream ofs(filename,std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        oa<<userMap;
    }
private:

};

#endif // SERIALIZER_H

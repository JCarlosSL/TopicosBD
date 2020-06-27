#include "filemanager.h"
typeUMap FileManager::recoverUser(string filename){
    typeUMap myMap;
    {
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia>>myMap;
    }
    return myMap;
}

typeUMap FileManager::recoverObject(string filename){
    typeUMap map;
    {
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia>>map;
    }
    return map;
}

typeMapBU FileManager::recoverBandaUsers(string file){
    typeMapBU map;
    {
        std::ifstream ifs(file);
        boost::archive::text_iarchive ia(ifs);
        ia>>map;
    }
    return map;
}

typeMapBU FileManager::recoverBandaUsersPuntaje(string file){
    typeMapBU map;
    {
        std::ifstream ifs(file);
        boost::archive::text_iarchive ia(ifs);
        ia>> map;
    }
    return map;
}

void FileManager::saveUser(typeUMap &userMap, string filename){
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa<<userMap;

}

void FileManager::saveObject(typeUMap &userMap, string filename){
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa<<userMap;

}

void FileManager::saveBandaUsers(typeMapBU &userMap, string filename){
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa<<userMap;
}

void FileManager::saveBandaUsersPuntaje(typeMapBU &userMap, string filename){
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa<<userMap;
}

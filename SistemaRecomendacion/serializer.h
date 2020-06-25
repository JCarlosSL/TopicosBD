#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/bitset.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <sstream>
#include "bits.h"
#include <cassert>

typedef std::unordered_map<std::string,Bits> typeMap1;
typedef std::map<Bits,float> typeMap2;
typedef std::map<Bits,typeMap2> typeMap3;

class Serializer
{
public:
    static void createInstance(typeMap1 &u,typeMap1 &o, typeMap3 &du,typeMap3 &bup){
        assert(!instance);
        instance=new  Serializer(u,o,du,bup);
    }
    static void destroyInstance(){
        assert(instance);
        delete instance;
    }
    static Serializer * getInstance(){
        assert(instance);
        return instance;
    }
    typeMap1 getUser() const;
    void setUser(const typeMap1 &value);

    typeMap1 getObject() const;
    void setObject(const typeMap1 &value);

    typeMap3 getDataUsers() const;
    void setDataUsers(const typeMap3 &value);

    typeMap3 getBandaUrsPuntaje() const;
    void setBandaUrsPuntaje(const typeMap3 &value);
private:
    Serializer(typeMap1 &u,typeMap1 &o, typeMap3 &du,typeMap3 &bup)
        :user(u),object(o),dataUsers(du),bandaUrsPuntaje(bup)
    {}
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar,const unsigned int version){
        ar & user;
        ar & object;
        ar & dataUsers;
        ar & bandaUrsPuntaje;
    }
    typeMap1 user;
    typeMap1 object;
    typeMap3 dataUsers;
    typeMap3 bandaUrsPuntaje;
    static Serializer *instance;
};

#endif // SERIALIZER_H

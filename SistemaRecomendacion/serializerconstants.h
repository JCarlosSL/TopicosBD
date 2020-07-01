#ifndef SERIALIZERCONSTANTS_H
#define SERIALIZERCONSTANTS_H
#include <iostream>
class SerializerConstants
{
public:
    static const std::string ANGELICA;
    static const std::string LORDE;
    static const std::string SLOPONE;
    static const std::string BOOKS;
    static const std::string MOVIELEANS_25M;
    static const std::string MOVIELEANS_ML_LASTET;
    static const std::string MOVIELEANS_ML_LASTETSMALL;
    static const std::string MOVIELEANS_27M;
    static const std::string MOVIERATINGS;
    static const std::string USER;
    static const std::string OBJECT;
    static const std::string BANDA_USERS;
    static const std::string BANDA_USERS_PUNTAJE;
private:
    SerializerConstants();
};
const std::string SerializerConstants::ANGELICA = std::string("serializer/angelica/");
const std::string SerializerConstants::LORDE = std::string("serializer/lorde/");
const std::string SerializerConstants::SLOPONE = std::string("serilaizer/slopone/");
const std::string SerializerConstants::BOOKS = std::string("serializer/books/");
const std::string SerializerConstants::MOVIELEANS_25M=std::string("serializer/movieleans_25m/");
const std::string SerializerConstants::MOVIELEANS_27M=std::string("serializer/movieleans_27m/");
const std::string SerializerConstants::OBJECT = std::string("user");
const std::string SerializerConstants::USER = std::string("object");
const std::string SerializerConstants::BANDA_USERS = std::string("banda_users");
const std::string SerializerConstants::BANDA_USERS_PUNTAJE = std::string("banda_users_puntaje");

#endif // SERIALIZERCONSTANTS_H
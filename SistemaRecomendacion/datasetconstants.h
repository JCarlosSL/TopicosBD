#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>

class DataSetConstants
{
public:
    static const std::string ANGELICA;
    static const std::string LORDE;
    static const std::string SLOPONE;
    static const std::string BOOKS;
    static const std::string MOVIELEANS25M;
    static const std::string MOVIELEANSMLLASTET;
    static const std::string MOVIELEANSMLLASTETSMALL;
    static const std::string MOVIELEANS27M;
    static const std::string MOVIERATINGS;
private:
    DataSetConstants();
};

const std::string DataSetConstants::ANGELICA = std::string("pdf/angelica.csv");
const std::string DataSetConstants::LORDE = std::string("pdf/lorde.csv");
const std::string DataSetConstants::SLOPONE = std::string("pdf/slopeOne.csv");

#endif // CONSTANTS_H

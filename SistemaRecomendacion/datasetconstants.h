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
    static const std::string MOVIETV;
    static const std::string MOVIELEANS27M_MATRIX;
private:
    DataSetConstants();
};
const std::string DataSetConstants::ANGELICA = std::string("pdf/angelica.csv");
const std::string DataSetConstants::LORDE = std::string("pdf/lorde.csv");
const std::string DataSetConstants::SLOPONE = std::string("pdf/slopeOne.csv");
const std::string DataSetConstants::BOOKS =std::string("BX-Dump/BX-Book-Ratings.csv");
const std::string DataSetConstants::MOVIELEANS25M=std::string("ml-25m/ratings.csv");
const std::string DataSetConstants::MOVIELEANS27M=std::string("ml-27m/ratings.csv");
const std::string DataSetConstants::MOVIERATINGS=std::string("movie_ratings/Movie_Ratings.csv");
const std::string DataSetConstants::MOVIELEANSMLLASTETSMALL=std::string("ml-latest-small/ratings.csv");
const std::string DataSetConstants::MOVIETV = std::string("MovieTV/ratings_Movies_and_TV.csv");
const std::string DataSetConstants::MOVIELEANS27M_MATRIX=std::string("matrix/movie_leans27m/");

#endif // CONSTANTS_H

#ifndef MOVIE_H
#define MOVIE_H

//#include "hashtable.h"
#include<iostream>
#include <string>
using namespace std;

class Movie
{
    public:
        // constructor
        Movie();
        Movie(char movieCode, int stock, string director, string title, int releaseYear);

        // destructor
        ~Movie();

        string toString() const;

        // accessors
        char getMovieCode() const;
        int getStock() const;
        string getDirector() const;
        string getTitle() const;        
        int getReleaseYear() const;
        
        // accessors that classic.h will inherit
        int getMonth() const;
        string getActor() const;

        // mutators
        bool addStock(int);
        bool removeStock(int);

        // operator overloads
        bool operator==(const Movie &compare);
        bool operator>(const Movie &compare);
        bool operator<(const Movie &compare);

    protected:
        int stock;
        int releaseYear;
        char movieCode;
        string title;
        string director;
};

#endif //MOVIE_H

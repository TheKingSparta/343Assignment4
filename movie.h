#ifndef MOVIE_H
#define MOVIE_H

#include<iostream>
#include<string>

class Movie
{
    public:
        // constructor
        Movie();
        Movie(char movieCode, int stock, std::string director, std::string title, int releaseYear);

        // destructor
        ~Movie();

        // accessors
        char getMovieCode() const;
        std::string getTitle() const;
        std::string getDirector() const;
        int getReleaseDate() const;
        int getStock() const;
    
       //overloaded operators
       bool operator== (const Movie &compare);
       bool operator> (const Movie &compare);
       bool operator< (const Movie &compare);

        // display output function
        void display() const;

        // mutators
        bool addStock(int);
        bool subtractStock(int);

        std::string toString() const;

    protected:
        int stock;
        int releaseYear;
        char movieCode;
        std::string title;
        std::string director;
};

#endif //MOVIE_H

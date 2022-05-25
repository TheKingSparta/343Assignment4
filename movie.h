#ifndef MOVIE_H
#define MOVIE_H

#include<iostream>
using namespace std;

class Movie
{
    public:
        // constructor
        Movie();
        Movie(char movieCode, int stock, string director, string title, int releaseYear);

        // destructor
        ~Movie();

        // accessors
        char getMovieCode() const;
        string getTitle() const;
        string getDirector() const;
        int getReleaseDate() const;
        int getStock() const;
    
       bool operator== (const Movie &compare);
       bool operator> (const Movie &compare);
       bool operator< (const Movie &compare);

        // display output function
        void display();

        // mutators
        bool addStock(int);
        bool subtractStock(int);

    private:
        int stock;
        int releaseYear;
        char movieCode;
        string title;
        string director;
};

#endif //MOVIE_H

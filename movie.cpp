#include "movie.h" 
#include <iomanip>


// default constructor
Movie::Movie()
{
   movieCode = '';
   stock = 0;
   director = "";
   title = "";
   releaseYear = 0;
}

// input constructor
Movie::Movie(char movieCode, int stock, string director, string title, int releaseYear)
{
    this->movieCode = movieCode;
    this->stock = stock;
    this->director = director;
    this->title = title;
    this->releaseYear = releaseYear;
}

// destructor
Movie::~Movie()
{

}

// getter function for movie code
char Movie::getMovieCode() const
{
    return movieCode;
}

// getter function for stock
int Movie::getStock() const
{
    return stock;
}

// getter function for director
string Movie::getDirector() const
{
    return director;
}

// getter function for title
string Movie::getTitle() const
{
    return title;
}

// getter function for release year
int Movie::getReleaseYear() const
{
    return releaseYear;
}

// getter function for month
// only classic.cpp will use this
int Movie::getMonth() const
{
    return -1;
}

// getter function for actor
// only classic.cpp will use this
string Movie::getActor() const
{
    return "";
}

// mutator function to add stock
bool Movie::addStock(int stockToAdd)
{
    if (stockToAdd >= 0)
    {
        stock += stockToAdd;
        return true;
    }   
}

// mutator function to remove stock 
bool Movie::removeStock(int stockToRemove)
{
    if (stock >= stockToRemove && stockToRemove > 0)
    {
        stock -= stockToRemove;
        return true;
    }
    else
    {
        return false;
    }
}

// operator == overload
// checks if two movies are the same
bool Movie::operator==(const Movie &compare)
{
    if (this->title == compare.title && this->releaseYear == compare.getReleaseYear())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// operator > overload
// checks if the first movie's release year is greater than the second movie's release year
bool Movie::operator>(const Movie &compare)
{
    return this->releaseYear > compare.getReleaseYear();
}

// operator < overload
// checks if the first movie's release year is less than the second movie's release year
bool Movie::operator<(const Movie &compare)
{
    return this->releaseYear < compare.getReleaseYear();
}

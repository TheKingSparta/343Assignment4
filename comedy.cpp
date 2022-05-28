/**         comedy.cpp
 *
 * Created by Zachary Clow
 *
 * Defines a Comedy class that inherits from Movie.
 * Movie code is 'F'
 */

#include comedy.h
#include "comedy.h"


Comedy::Comedy()
{
   stock = 0;
   releaseYear = 0;
   movieCode = 'F';
   title = "";
   director = "";
}

Comedy::~Comedy() {

}

Comedy::Comedy(int stock, std::string title, std::string director,
               int releaseYear)
{
   this->stock = stock;
   this->title = title;
   this->director = director;
   this->releaseYear = releaseYear;
   movieCode = 'F';
}


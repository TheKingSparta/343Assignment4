/**         comedy.cpp
 *
 * Created by Zachary Clow
 *
 * Defines a Comedy class that inherits from Movie.
 * movieCode is F, sorting criteria are title and release year
 *
 */

#include "comedy.h"

Comedy::Comedy(int stock, std::string title, std::string director,
               int releaseYear)
{
   this->movieCode = 'F';
   this->stock = stock;
   this->title = title;
   this->director = director;
   this->releaseYear = releaseYear;
}

Comedy::Comedy()
{
   stock = 0;
   releaseYear = 0;
   movieCode = 'F';
   title = "";
   director = "";
}

Comedy::~Comedy() = default;

//Returns a string representation of the Comedy. Format is:
//"title year stock director F"
string Comedy::toString() const{
   string str;
   str.push_back(movieCode);
   return title + " " + to_string(releaseYear) + " " + to_string(stock) + " " + director + " " + str;
}

//Returns true if the input's title comes first alphabetically,
//false if it comes after. If they're the same, returns true
//if the input's release year comes first, and false otherwise.
bool Comedy::operator<(const Comedy &compare) const
{
   if(title.compare(compare.getTitle()) < 0) {
      return true;
   } else if(title.compare(compare.getTitle()) == 0) {
      if(releaseYear < compare.getYear()) {
         return true;
      }
   }
   return false;
}

//Outputs movie.toString()
std::ostream& operator<<(ostream& output, const Comedy& movie)
{
   output << movie.toString();
   output << "\n";
   return output;
}
/**         comedy.h
 *
 * Created by Zachary Clow
 *
 * Defines a Comedy class that inherits from Movie.
 * movieCode is F, sorting criteria are title and release year
 *
 */

#ifndef ASSIGNMENT4_COMEDY_H
#define ASSIGNMENT4_COMEDY_H

#include "movie.h"
#include <string>

class Comedy: public Movie {
public:
   //Default constructor. Defined in Movie.h
   Comedy();
    
   // Destructor
   ~Comedy();

   //Constructor to set default values
   Comedy(int stock, std::string title, std::string director, int releaseYear);

   //Returns a string representation of the Comedy. Format is:
   //"title year stock director F"
   string toString() const;

   //Returns true if the input's title comes first alphabetically,
   //false if it comes after. If they're the same, returns true
   //if the input's release year comes first, and false otherwise.
   bool operator<(const Comedy &compare) const;

   //Outputs movie.toString()
   friend std::ostream& operator<<(std::ostream&, const Comedy&);
};

#endif //ASSIGNMENT4_COMEDY_H


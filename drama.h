/** drama.h
 * Defines a Drama class that describes a drama movie. Includes functions for
 *movie class *
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_DRAMA_H
#define ASSIGNMENT4_DRAMA_H

#include <fstream>
#include "movie.h"
#include <iomanip>

using namespace std;

class Drama:public Movie {

   public:

   //Constructor set to default values
   Drama(char movieCode,int stock, string title, string director, int releaseYear);
   
   //default constructor from Movie
   Drama();
   
   //destructor
   ~Drama();

   string toString() const;
   
};
#endif //ASSIGNMENT4_DRAMA_H

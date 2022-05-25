/** drama.h
 * Defines a Drama class that describes a drama movie. Includes functions for
 *movie class *
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_DRAMA_H
#define ASSIGNMENT4_DRAMA_H

#include <fstream>
#include "Movie.h"
#include <iomanip>

using namespace std;

class Drama:public Movie {
public:
   Drama(char genre);
   ~Drama();
   void setData(ifstream& f);
   
};
#endif //ASSIGNMENT4_DRAMA_H

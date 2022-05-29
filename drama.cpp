/** drama.h
 * Defines a Drama class that describes a drama movie. Includes functions for
 *movie class *
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_DRAMA_CPP
#define ASSIGNMENT4_DRAMA_CPP

#include <fstream>
#include "movie.h"
#include "drama.h"
#include <iomanip>

using namespace std;

 

   //Constructor set to default values
   Drama::Drama(char moviecode,int stock, string title, string director, int releaseYear){
      this->movieCode = 'D';
      this->stock = stock;
      this->title = title;
      this->director = director;
      this->releaseYear = releaseYear;


   }
   
   //default constructor from Movie
   Drama::Drama(){
    movieCode = 'D';
   stock = 0;
   releaseYear = 0;
   title = "";
   director = "";

   }
   
   //destructor
   Drama::~Drama(){

   }
   

#endif //ASSIGNMENT4_DRAMA_H

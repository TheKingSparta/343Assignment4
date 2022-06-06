#include <iostream>
#include <fstream>
#include "customer.h"
#include "hashtable.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"
#include "movie.h"
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void fillCustomerData(ifstream &customerFile, HashTable<Customer> &customers) {
   char nextLine[100];  //Size doesn't matter much, just needs to be big enough

   stringstream stream;

   string ID;
   string firstName;
   string lastName;

   while(!customerFile.eof()) {
      //Get the next line, up to 100 chars, put in nextLine
      customerFile.getline(nextLine, 100);
      stream << nextLine;
      stream >> ID;
      stream >> lastName;
      stream >> firstName;
      customers.insertItem(ID, new Customer(ID, firstName, lastName));
   }
}

void fillMovieData(ifstream &movieFile, vector<Comedy*> &comedies, vector<Drama*> &dramas, vector<Classic*> &classics) {

   string token;

   stringstream stream;

   char code;
   string stock;
   string director;
   //string directorLastName;
   string title;

   //Everything but Classic year is next
   string year;

   //Only for classic
   string majorActorFirstName;
   string majorActorLastName;
   string month;

   while(!movieFile.eof()) {
      char nextLine[999];  //Size doesn't matter much, just needs to be big enough

      //Get the next line, up to 100 chars, put in nextLine
      movieFile.getline(nextLine, 999);
      if(movieFile.eof()) {
         break;
      }
      stream << nextLine;

      //string next(nextLine);
      //next.erase(remove(next.begin(), next.end(), ','), next.end());
      getline(stream, token, ',');
      code = token[0];

      getline(stream, token, ',');
      stock = token;

      getline(stream, token, ',');
      director = token;
      //stream >> directorLastName;
      getline(stream, token, ',');
      title = token;

      if(code == 'C') {
         stream >> majorActorFirstName;
         stream >> majorActorLastName;
         stream >> month;
         stream >> year;
         classics.push_back(new Classic(stoi(stock), title, director, majorActorFirstName + " " + majorActorLastName, stoi(year), stoi(month)));
      } else if(code == 'F') {
         //getline(stream, token, ',');
         //year = token;
         stream >> year;
         comedies.push_back(new Comedy(stoi(stock), title, director, stoi(year)));
      } else if(code == 'D') {
         //getline(stream, token, ',');
         //year = token;
         stream >> year;
         dramas.push_back(new Drama(stoi(stock), title, director, stoi(year)));
      } else {
         cout << "Invalid movie code \n";
      }
      stream.str("");
   }
   //Sort
   sort(classics.begin(), classics.end());
   sort(dramas.begin(), dramas.end());
   sort(comedies.begin(), comedies.end());

   //Output
   for(Comedy* c : comedies) {
      cout << *c;
   }
   for(Drama* d : dramas) {
      cout << *d;
   }
   for(Classic* c : classics) {
      cout << *c;
   }
}

void executeCommands() {

}

void outputInventory() {
   //For each in comedy, output each comedy
   //For each in Drama, output each drama
   //For each in classics, output each classics
}

int main()
{
   ifstream customerFile("data4customers.txt");
   ifstream moviesFile("data4movies.txt");
   ifstream transactionsFile("data4commands.txt");

   if(!customerFile)
      cout << "Customer file cannot be opened" << endl;
   if(!moviesFile)
      cout << "Movie file cannot be opened" << endl;
   if(!transactionsFile)
      cout << "Transaction file cannot be opened" << endl;

   HashTable<Customer> customers;

   vector<Comedy*> comedies;
   vector<Drama*> dramas;
   vector<Classic*> classics;

   fillCustomerData(customerFile, customers);
   fillMovieData(moviesFile, comedies, dramas, classics);
   //customers.printHash();
}




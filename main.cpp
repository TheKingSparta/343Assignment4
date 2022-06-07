#include <string>
#include <iostream>
#include <fstream>
#include "customer.h"
#include "hashtable.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"
#include "movie.h"

#include <vector>

#include <algorithm>
#include <sstream>

using namespace std;

void fillCustomerData(ifstream &customerFile, HashTable<Customer> &customers) {
   char nextLine[100];  //Size doesn't matter much, just needs to be big enough

   std::stringstream stream;

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
      stream.clear();
   }
}


string removeSpaces(string input) {
   string output;
   bool isStart = true;
   for(int i = 0; i < input.length(); i++) {
      if(!(isStart && input[i] == ' ')) {
         isStart = false;
         output += input[i];
      }
   }
   return output;
}

void fillMovieData(ifstream &movieFile, vector<Comedy*> &comedies, vector<Drama*> &dramas, vector<Classic*> &classics) {

   string token;

   std::stringstream stream;

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
      char nextLine[200];  //Size doesn't matter much, just needs to be big enough

      //Get the next line, up to 999 chars, put in nextLine
      movieFile.getline(nextLine, 200);
      if(movieFile.eof()) {
         break;
      }
      stream.str(nextLine);

      //string next(nextLine);
      //next.erase(remove(next.begin(), next.end(), ','), next.end());
      std::getline(stream, token, ',');
      token = removeSpaces(token);
      code = token[0];

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      stock = token;

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      director = token;

      std::getline(stream, token, ',');
      token = removeSpaces(token);
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
      stream.clear();

   }
   //Sort
   sort(classics.begin(), classics.end(), [](Classic* ptr_l , Classic* ptr_r) { return *ptr_l < *ptr_r;});
   sort(dramas.begin(), dramas.end(), [](Drama* ptr_l , Drama* ptr_r) { return *ptr_l < *ptr_r;});
   sort(comedies.begin(), comedies.end(), [](Comedy* ptr_l , Comedy* ptr_r) { return *ptr_l < *ptr_r;});
}


void outputInventory(vector<Comedy*> &comedies, vector<Drama*> &dramas, vector<Classic*> &classics) {
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

//R [ID] D [movie info]: Return
//B [ID] D [movie info]: Borrow
//I: Output inventory
//H [ID]: Output Customer history
void executeCommands(ifstream &commandFile, HashTable<Customer> &customers, vector<Comedy*> &comedies, vector<Drama*> &dramas, vector<Classic*> &classics) {
   string token;

   std::stringstream stream;

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

   char commandCode;

   string ID;

   while(!commandFile.eof())
   {
      char nextLine[200];  //Size doesn't matter much, just needs to be big enough

      //Get the next line, up to 999 chars, put in nextLine
      commandFile.getline(nextLine, 200);
      if(commandFile.eof())
      {
         break;
      }
      stream.str(nextLine);

      stream >> commandCode;

      if(commandCode == 'I') {
         outputInventory(comedies, dramas, classics);
      } else if(commandCode == 'H') {
         stream >> ID;
         customers.retrieve(ID)->outputHistory();
      } else if(commandCode == 'B') {
         //Borrow
      } else if(commandCode == 'R') {
         //Return
      } else {
         cout << "Bad error code";
         cout << "\n";
      }

      /*
      //string next(nextLine);
      //next.erase(remove(next.begin(), next.end(), ','), next.end());
      std::getline(stream, token, ',');
      token = removeSpaces(token);
      code = token[0];

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      stock = token;

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      director = token;

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      title = token;
`     */
      stream.clear();
   }
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
   executeCommands(transactionsFile, customers, comedies, dramas, classics);
}




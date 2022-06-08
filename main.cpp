#include <string>
#include <iostream>
#include "customer.h"
#include "hashtable.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

//Fill in the customers HashTable using the data from customerFile.
//Assumes data is formatted correctly.
void fillCustomerData(ifstream& customerFile, HashTable<Customer>& customers)
{
   //Stores the next line from the file
   char nextLine[200];  //Size doesn't matter much, just needs to be big enough for a whole line

   //Used for getting the next " " or ","-seperated string from the file
   std::stringstream stream;

   string ID;
   string firstName;
   string lastName;

   while(!customerFile.eof())
   {
      //Get the next line, up to 100 chars, put in nextLine
      customerFile.getline(nextLine, 200);
      //Put the next line into the stream
      stream << nextLine;
      //Grab the next string from the stream and store it
      stream >> ID;
      stream >> lastName;
      stream >> firstName;
      customers.insertItem(ID, new Customer(ID, firstName, lastName));
      //Reset the stream
      stream.clear();
   }
}

//Returns a string that is identical to the input string, but with all
//spaces removed from the start
string removeSpaces(string input)
{
   string output;
   bool isStart = true;
   for(int i = 0; i < input.length(); i++)
   {
      if(!(isStart && input[i] == ' '))
      {
         isStart = false;
         output += input[i];
      }
   }
   return output;
}

//Fills in the movie vectors with the data from movieFile. Assumes movieFile
//Is formatted correctly
void fillMovieData(ifstream& movieFile, vector<shared_ptr<Comedy>>& comedies,
                   vector<shared_ptr<Drama>>& dramas,
                   vector<shared_ptr<Classic>>& classics)
{
   //The next string in the data file. Is used for getting ,-seperated
   //strings
   string token;

   //Used for getting , or space seperated strings from the movieFile
   std::stringstream stream;

   //Things that all Movies have
   char code;
   string stock;
   string director;
   string title;

   //Year is in a different place depending on the genre
   string year;

   //Only for classic
   string majorActorFirstName;
   string majorActorLastName;
   string month;

   while(!movieFile.eof())
   {
      //Stores the next line from the movieFile
      char nextLine[200];  //Size doesn't matter much, just needs to be big enough

      //Get the next line, up to 200 chars, put in nextLine
      movieFile.getline(nextLine, 200);
      //Sometimes the files have an extra linebreak at the end, which we need
      //to check for
      if(movieFile.eof())
      {
         break;
      }

      //Add nextLine to the stream
      stream.str(nextLine);

      //Get everything in the stream up until a comma, put it in token.
      std::getline(stream, token, ',');

      //Sometimes getline leaves white space at the start of the string
      //that needs to be removed
      token = removeSpaces(token);

      //code is a char, so only need the first char in token
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

      if(code == 'C')
      {
         stream >> majorActorFirstName;
         stream >> majorActorLastName;
         stream >> month;
         stream >> year;

         //Create the new movie as a shared_ptr, add it to the appropriate vector
         auto thing = shared_ptr<Classic>(
            new Classic(stoi(stock), title, director,
                        majorActorFirstName + " " +
                        majorActorLastName, stoi(year),
                        stoi(month)));
         classics.push_back(thing);

      } else if(code == 'F')
      {
         stream >> year;
         //Create the new movie as a shared_ptr, add it to the appropriate vector
         auto thing2 = shared_ptr<Comedy>(
            new Comedy(stoi(stock), title, director, stoi(year)));
         comedies.push_back(thing2);
      } else if(code == 'D')
      {
         stream >> year;
         //Create the new movie as a shared_ptr, add it to the appropriate vector
         auto thing3 = shared_ptr<Drama>(
            new Drama(stoi(stock), title, director, stoi(year)));
         dramas.push_back(thing3);
      } else
      {
         std::cout << "Invalid movie code in movie file: ";
         std::cout << code;
         std::cout << "\n\n";
      }
      stream.clear();
   }
   //Sort the vectors using std::sort and a basic lambda function
   std::sort(classics.begin(), classics.end(),
             [](shared_ptr<Classic> ptr_l, shared_ptr<Classic> ptr_r)
             { return *ptr_l < *ptr_r; });
   sort(dramas.begin(), dramas.end(),
        [](shared_ptr<Drama> ptr_l, shared_ptr<Drama> ptr_r)
        { return *ptr_l < *ptr_r; });
   sort(comedies.begin(), comedies.end(),
        [](shared_ptr<Comedy> ptr_l, shared_ptr<Comedy> ptr_r)
        { return *ptr_l < *ptr_r; });
}

//Outputs the contents of the movie vectors to cout with nice formatting
void outputInventory(vector<shared_ptr<Comedy>>& comedies,
                     vector<shared_ptr<Drama>>& dramas,
                     vector<shared_ptr<Classic>>& classics)
{
   for(shared_ptr<Comedy> c: comedies)
   {
      std::cout << c->getStock() << ": ";
      std::cout << c->getTitle() << ", ";
      std::cout << c->getYear() << " " << c->getMovieCode() << "\n";
   }
   for(shared_ptr<Drama> d: dramas)
   {
      std::cout << d->getStock() << ": ";
      std::cout << d->getDirector() << ", ";
      std::cout << d->getTitle() << " " << d->getMovieCode() << "\n";
   }
   for(shared_ptr<Classic> c: classics)
   {
      std::cout << c->getStock() << ": ";
      std::cout << c->getMonth() << " ";
      std::cout << c->getYear() << ", ";
      std::cout << c->getActor() << " " << c->getMovieCode() << "\n";
   }
   std::cout << "\n";
}

//R [ID] D [movie info]: Return
//B [ID] D [movie info]: Borrow
//I: Output inventory
//H [ID]: Output Customer history
//Executes the commands from commandFile, outputting errors for bad commands/data,
//And updating movie stocks and customer transaction history as necessary.
void executeCommands(ifstream& commandFile, HashTable<Customer>& customers,
                     vector<shared_ptr<Comedy>>& comedies,
                     vector<shared_ptr<Drama>>& dramas,
                     vector<shared_ptr<Classic>>& classics)
{
   //The next string from commandFile
   string token;

   //Used for getting strings from commandFile
   std::stringstream stream;

   //Variables for storing data from movie-related commands
   char code;
   string stock;
   string director;
   string title;
   string year;

   //Only for classic
   string majorActorFirstName;
   string majorActorLastName;
   string month;

   //The char that represents the command to be executed
   char commandCode;

   //The type of media (should only be D for DVD)
   char media;

   //The customer ID for customer-related commands
   string ID;

   while(!commandFile.eof())
   {
      stream.clear();
      //Stores the next line of commandFile
      char nextLine[200];  //Size doesn't matter much, just needs to be big enough

      //Get the next line, up to 999 chars, put in nextLine
      commandFile.getline(nextLine, 200);
      if(commandFile.eof())
      {
         break;
      }
      //Put nextLine into the stream
      stream.str(nextLine);

      stream >> commandCode;

      if(commandCode == 'I')
      {
         outputInventory(comedies, dramas, classics);
      } else if(commandCode == 'H')
      {
         stream >> ID;
         customers.retrieve(ID)->outputHistory();
      } else if(commandCode == 'B')
      {
         //Borrow
         stream >> ID;
         stream >> media;
         if(media != 'D')
         {
            std::cout << "Invalid media type: " << media << "\n\n";
            continue;
         }
         stream >> code;
         if(code == 'D')
         {
            //Get everything up to the next comma, store it in token, Removing any
            //leading whitespace from token, then set the next value using token.
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            director = token;

            std::getline(stream, token, ',');
            token = removeSpaces(token);
            title = token;

            //Using the provided information, look for the movie in the appropriate
            //vector
            shared_ptr<Drama> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Drama> d: dramas)
            {
               if(d->getDirector() == director && d->getTitle() == title)
               {
                  movie = d;
               }
            }
            //If the movie doesn't exist:
            if(movie == nullptr)
            {
               std::cout << "No movie with title: ";
               std::cout << title;
               std::cout << "\n\n";
               continue;
            }
            //If the movie isn't in stock:
            if(!movie->removeStock(1))
            {
               std::cout << "Movie not in stock: " << title << "\n\n";
               continue;
            }
            customer = customers.retrieve(ID);
            //If the ID doesn't match any customer:
            if(customer == nullptr)
            {
               std::cout << "No customer with ID ";
               std::cout << ID;
               std::cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "borrow");
         } else if(code == 'C')
         {
            stream >> month;
            stream >> year;
            stream >> majorActorFirstName;
            stream >> majorActorLastName;
            shared_ptr<Classic> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Classic> c: classics)
            {
               if(c->getMonth() == stoi(month) && c->getYear() == stoi(year) &&
                  c->getActor() ==
                  majorActorFirstName + " " + majorActorLastName)
               {
                  movie = c;
               }
            }
            if(movie == nullptr)
            {
               cout << "No movie with release date and actor: ";
               cout << month << " " << year << " " << majorActorFirstName << " "
                    << majorActorLastName;
               cout << "\n\n";
               continue;
            }
            customer = customers.retrieve(ID);
            if(customer == nullptr)
            {
               cout << "No customer with ID: ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            if(!movie->removeStock(1))
            {
               std::cout << "Movie not in stock: " << month << " " << year
                         << " " << majorActorFirstName << " "
                         << majorActorLastName << "\n\n";
               continue;
            }
            customer->addHistory(movie, "borrow");
         } else if(code == 'F')
         {
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            title = token;
            stream >> year;
            shared_ptr<Comedy> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Comedy> c: comedies)
            {
               if(c->getTitle() == title && c->getYear() == stoi(year))
               {
                  movie = c;
               }
            }
            if(movie == nullptr)
            {
               cout << "No movie with title: ";
               cout << title;
               cout << "\n\n";
               continue;
            }
            customer = customers.retrieve(ID);
            if(customer == nullptr)
            {
               cout << "No customer with ID: ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            if(!movie->removeStock(1))
            {
               std::cout << "Movie not in stock: " << title << "\n\n";
               continue;
            }
            customer->addHistory(movie, "borrow");
         } else
         {
            std::cout << "Invalid movie code in command file: ";
            std::cout << code;
            std::cout << "\n\n";
            continue;
         }

      } else if(commandCode == 'R')
      {
         //Return
         stream >> ID;
         stream >> media;
         if(media != 'D')
         {
            std::cout << "Invalid media type: " << media << "\n\n";
            continue;
         }
         stream >> code;
         if(code == 'D')
         {
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            director = token;
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            title = token;
            shared_ptr<Drama> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Drama> d: dramas)
            {
               if(d->getDirector() == director && d->getTitle() == title)
               {
                  movie = d;
               }
            }
            if(movie == nullptr)
            {
               cout << "No movie with title: ";
               cout << title;
               cout << "\n\n";
               continue;
            }
            movie->addStock(1);
            customer = customers.retrieve(ID);
            if(customer == nullptr)
            {
               cout << "No customer with ID: ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "return");
         } else if(code == 'C')
         {
            stream >> month;
            stream >> year;
            stream >> majorActorFirstName;
            stream >> majorActorLastName;
            shared_ptr<Classic> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Classic> c: classics)
            {
               if(c->getMonth() == stoi(month) && c->getYear() == stoi(year) &&
                  c->getActor() ==
                  majorActorFirstName + " " + majorActorLastName)
               {
                  movie = c;
               }
            }
            if(movie == nullptr)
            {
               cout << "No movie with release date and major actor: ";
               cout << month << " " << year << " " << majorActorFirstName << " "
                    << majorActorLastName;
               cout << "\n\n";
               continue;
            }
            movie->addStock(1);
            customer = customers.retrieve(ID);
            if(customer == nullptr)
            {
               cout << "No customer with ID: ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "return");
         } else if(code == 'F')
         {
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            title = token;
            stream >> year;
            shared_ptr<Comedy> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Comedy> c: comedies)
            {
               if(c->getTitle() == title && c->getYear() == stoi(year))
               {
                  movie = c;
               }
            }
            if(movie == nullptr)
            {
               cout << "No movie with title: ";
               cout << title;
               cout << "\n\n";
               continue;
            }
            movie->addStock(1);
            customer = customers.retrieve(ID);
            if(customer == nullptr)
            {
               cout << "No customer with ID: ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "return");
         } else
         {
            std::cout << "Invalid movie code in command file: ";
            std::cout << code;
            std::cout << "\n\n";
            continue;
         }
      } else
      {
         cout << "Invalid command code: " << commandCode << "\n\n";
      }
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

   vector<shared_ptr<Comedy>> comedies;
   vector<shared_ptr<Drama>> dramas;
   vector<shared_ptr<Classic>> classics;

   fillCustomerData(customerFile, customers);
   cout << "\n";
   fillMovieData(moviesFile, comedies, dramas, classics);
   executeCommands(transactionsFile, customers, comedies, dramas, classics);

   return 0;
}
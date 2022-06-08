/** customer.cpp
 * Defines a Customer class that describes a customer. Includes functions for
 * tracking the Customer's transaction history, name, and ID.
 *
 * Written by Zachary Clow
 *
 */

#include "customer.h"
#include <string>

using namespace std;

//Default constructor. Sets ID to 0000, firstName "Default", lastName "Default"
Customer::Customer()
{
   ID = "0000";
   firstName = "Default";
   lastName = "Default";
   numTransactions = 0;
   for(int i = 0; i < MAXHISTORY; i++) {
      historyTypes[i] = "";
      historyMovies[i] = nullptr;
   }
}

Customer::~Customer()
{
   //for(int i = 0; i < MAXHISTORY; i++) {
   //   delete historyMovies[i];
   //}
}

Customer::Customer(string ID, std::string firstName, std::string lastName)
{
   this->ID = ID;
   this->firstName = firstName;
   this->lastName = lastName;
   numTransactions = 0;
   for(int i = 0; i < MAXHISTORY; i++) {
      historyTypes[i] = "";
      historyMovies[i] = nullptr;
   }
}

//Output the Customer's history to cout in chronological order.
//Format:
//typeOfHistory: movie.toString()
void Customer::outputHistory() const
{
   cout << "ID: " << ID << "\n";
   cout << lastName << ", ";
   cout << firstName;
   cout << "\n";
   //Loop through the history from most recent to oldest.
   for(int i = numTransactions - 1; i >= 0; i--) {
      cout << historyTypes[i];
      cout << ": ";
      cout << historyMovies[i]->toString();
      cout << "\n";
   }
   cout << "\n";
}

//Add a new borrow or return to the customer's history. movie should be
//a shared_ptr that points to the movie, and type should be
//the type of transaction, ie "borrow" or "return"
//Customers cannot return movies they have not borrowed.
void Customer::addHistory(shared_ptr<Movie> movie, std::string type)
{
   if(numTransactions >= MAXHISTORY) { //If the history arrays are full...
      cout << "numTransactions cannot exceed MAXHISTORY";
      return;
   }
   int numTimesBorrowed = 0;
   int numTimesReturned = 0;

   //If a customer attempts to return a movie they don't have, the
   //method ends and outputs a message.
   if(type == "return")
   {
      for(int i = 0; i < numTransactions; i++)
      {
         if(historyMovies[i] == movie)
         {
            if(historyTypes[i] == "borrow")
            {
               numTimesBorrowed++;
            } else if(historyTypes[i] == "return")
            {
               numTimesReturned++;
            }
         }
      }
      if(numTimesReturned == numTimesBorrowed) {
         cout << "Cannot return movie that has not been borrowed\n\n";
         return;
      }
   }
   historyMovies[numTransactions] = movie;
   historyTypes[numTransactions] = type;
   numTransactions++;
}

string Customer::getID() const
{
   return ID;
}

string Customer::getFirstName() const
{
   return firstName;
}

string Customer::getLastName() const
{
   return lastName;
}

//Output the customer's ID, lastname, and firstname
std::ostream& operator<<(ostream& output, const Customer& customer)
{
   output << "ID: " << customer.ID << "\n";
   output << customer.lastName << " ";
   output << customer.firstName;

   return output;
}



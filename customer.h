/** customer.h
 * Defines a Customer class that describes a customer. Includes functions for
 * tracking the Customer's transaction history, name, and ID.
 *
 * Written by Zachary Clow
 *
 */

#ifndef ASSIGNMENT4_CUSTOMER_H
#define ASSIGNMENT4_CUSTOMER_H

#include <string>
#include <memory>
#include "movie.h"

class Customer : public Movie
{
public:
   //The max number of history items the customer can have.
   static int const MAXHISTORY = 9999;

   //Add a new borrow or return to the customer's history. movie should be
   //a shared_ptr that points to the movie, and type should be
   //the type of transaction, ie "borrow" or "return"
   //Customers cannot return movies they have not borrowed.
   void addHistory(shared_ptr<Movie> movie, std::string type);

   //Output the Customer's history to cout in chronological order
   //Format:
   //typeOfHistory: movie.toString()
   void outputHistory() const;

   //Default constructor. Sets ID to 0000, firstName "Default", lastName "Default"
   Customer();

   ~Customer();

   //Creates a Customer with an input ID, firstname, and lastname
   Customer(string ID, std::string firstName, std::string lastName);

   string getID() const;

   string getFirstName() const;

   string getLastName() const;

   //Output the customer's ID, lastname, and firstname
   friend std::ostream& operator<<(std::ostream&, const Customer&);

private:
   //The customer's unique ID
   string ID;

   //The customer's last name
   std::string lastName;

   //The customer's first name
   std::string firstName;

   //The customer's transaction history. historyMovies stores the movies
   //checked out or returned by the customer, and historyTypes stores
   //whether the movie was checked out or returned.
   shared_ptr<Movie> historyMovies[MAXHISTORY];
   //The customer's transaction history. historyMovies stores the movies
   //checked out or returned by the customer, and historyTypes stores
   //whether the movie was checked out or returned.
   std::string historyTypes[MAXHISTORY];

   //The number of transactions (returns or check-outs) made by
   //the Customer.
   int numTransactions;
};

#endif //ASSIGNMENT4_CUSTOMER_H

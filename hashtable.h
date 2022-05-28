/** hashtable.h
 * Defines a hashtable of what customers' bought that store has on record. Implemented using array of linked lists 
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_HASHTABLE_H
#define ASSIGNMENT4_HASHTABLE_H

#include "customer.h"
#include <string>

class HashTable
{
   // structure of linked list
   struct node
   {
      void* data;
      node* next;

      node(void* customer, node* n) : data(customer), next(n)
      {};
   };

public:

   // constructor
   HashTable();

   // destructor
   ~HashTable();

   // finding item in hashtable
   bool retrieve(std::string key);

   void insertItem(std::string key, void* data);

   void deleteItem(std::string key);

   // show all contents in hashtable
   void printHash();

private:
   int hash(int ID); // calculation to find remainder
   int hashSize; // max size of hashtable
   node* customerHash[]; // array of linked lists. Need to initialize in constructor
};

#endif //ASSIGNMENT4_HASHTABLE_H

/** hashtable.h
 * Defines a hashtable of what customers' bought that store has on record. Implemented using array of linked lists 
* Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_HASHTABLE_H
#define ASSIGNMENT4_HASHTABLE_H

#include "customer.h"
#include "movie.h"
using namespace std;

class HashTable {
  // structure of linked list
  struct node{
    void* data;
    string key;
    node* next;
    
    node(void* customer, node* n, string key): data(customer), next(n), key(key) {};
  };
  public:

// constructor
HashTable();
// destructor
~HashTable();
// finding item in hashtable
bool retrieve(string key);
  
void insertItem(string key, void* data);

void deleteItem(string key);
    
// show all contents in hashtable
void printHash();


private:
int hash(int ID);

  // calculation to find remainder
static int const MAXHASHSIZE = 100; // max size of hashtable
 node* array[MAXHASHSIZE]; // array of linked lists
};

#endif //ASSIGNMENT4_HASHTABLE_CPP


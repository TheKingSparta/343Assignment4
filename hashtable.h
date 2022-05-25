/** hashtable.h
 * Defines a hashtable of what customers' bought that store has on record. Implemented using array of linked lists 
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_HASHTABLE_H
#define ASSIGNMENT4_HASHTABLE_H

#include "customer.h"
using namespace std;

class HashTable {
  // structure of linked list
  struct node{
     void* data;
    node* next;
    
    node(void* customer, node* n): data(customer), next(n) {};
  };
public:

// constructor
HashTable();
// destructor
~HashTable();
// finding item in hashtable
bool retrieve(String key); 
  
void insertItem(String key, void* data);
void deleteItem(String key);
  
// making hashtable from files containing data of customer and movies
void buildHashTable(ifstream &infile);
  
// show all contents in hashtable
void printHash();
private:
int hash(int ID); // calculation to find remainder
int hashSize; // max size of hashtable
 node* customerHash[hashSize]; // array of linked lists
};

#endif //ASSIGNMENT4_HASHTABLE_H

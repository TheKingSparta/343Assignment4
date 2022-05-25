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
    Customer* data;
    node* next;
    
    node(Customer* customer, node* n): data(customer), next(n) {};
  };
public:

// constructor
HashTable();
// destructor
~HashTable();

bool retrieve(String key); 
void insertItem(String key);
void deleteItem(String key);
void buildHashTable(ifstream &infile);
void printHash();
private:
int hash(int ID);
int hashSize;
 node* customerHash[hashSize]; // array of linked lists
};

#endif //ASSIGNMENT4_HASHTABLE_H

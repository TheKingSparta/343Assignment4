/** hashtable.h
 * Defines a hashtable of customers that store has on record. Implemented using linked lists 
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_HASHTABLE_H
#define ASSIGNMENT4_HASHTABLE_H

#include "customer.h"
using namespace std;

class HashTable {
  struct node{
    Customer* data;
    node* next;
    
    node(Customer* customer, node* n): data(customer), next(n) {};
  };
public:

HashTable();
~HashTable();

bool retrieveCustomer(int ID, Customer*& customer);
void insertItem(String key);
void deleteItem(String key);
void buildHashTable(ifstream &infile);
void printHash();
private:
int hash(int ID);
int hashSize;
 node* customerHash[hashSize];
};

#endif //ASSIGNMENT4_HASHTABLE_H

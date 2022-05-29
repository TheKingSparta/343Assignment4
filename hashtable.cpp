/** hashtable.h
 * Defines a hashtable of what customers' bought that store has on record. Implemented using array of linked lists 
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_HASHTABLE_CPP
#define ASSIGNMENT4_HASHTABLE_CPP

#include "customer.h"
#include "hashtable.h"
#include "movie.h"
using namespace std;


  // structure of linked list
  

// constructor
HashTable::HashTable(){

for(int i = 0; i < MAXHASHSIZE; i++)
array[i] = nullptr;

}
// destructor
HashTable::~HashTable(){
  node* curr;

  for(int i = 0; i < MAXHASHSIZE; i++){
    while(array[i] != nullptr){
      curr = array[i];
      array[i] = array[i]->next;

      delete curr->data;
      curr->data = nullptr;

      delete curr;

    }

    array[i] = nullptr;
  }

}
// finding item in hashtable
bool HashTable::retrieve(string key){

}
  
void HashTable::insertItem(string key, void* data){

}
void HashTable::deleteItem(string key){

}
    
// show all contents in hashtable
void HashTable::printHash(){

}

int HashTable::hash(int ID){

  return ID % MAXHASHSIZE;

} // calculation to find remainder



#endif //ASSIGNMENT4_HASHTABLE_CPP

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
// finding item in hashtable
void* HashTable::retrieve(string key){
  int num = 0;
  for(int i = 0; i < key.length();i++){
      num += key[i];
  }
  int index = hash(num);
  node* curr;
  curr = array[index];
  if(curr->key == key)
   return curr->data;
while(curr->next != nullptr){
    if(curr->next->key == key)
   return curr->next->data;
   curr = curr->next; 
     }
   return nullptr;
  
}
  
void HashTable::insertItem(string key, void* data){
   int num = 0;
  for(int i = 0; i < key.length();i++){
      num += key[i];
  }
  int index = hash(num);
 if(array[index] != nullptr){
  node* curr;
  curr = array[index];
  if(curr->data == nullptr && curr->key == key)
    curr->data = data;
    curr->key = key;
while(curr->next != nullptr){
    if(curr->next->data == nullptr && curr->next->key == key){
   curr->next->data = data;
   curr->next->key = key;
    }
   curr = curr->next; 
     }
 }
  

}
void HashTable::deleteItem(string key){
  if(retrieve(key) != nullptr)
  delete retrieve(key);
 

}
    
// show all contents in hashtable
void HashTable::printHash(){
  
  for(int i = 0; i < MAXHASHSIZE; i++)
    cout << array[i] << endl;

}

int HashTable::hash(int ID){

  return ID % MAXHASHSIZE;

} // calculation to find remainder



#endif //ASSIGNMENT4_HASHTABLE_CPP

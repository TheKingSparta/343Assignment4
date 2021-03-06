/** hashtable.h
 * Defines a hashtable of what customers' bought that store has on record. Implemented using array of linked lists 
 * a template class
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_HASHTABLE_H
#define ASSIGNMENT4_HASHTABLE_H

#include "customer.h"
#include "movie.h"
using namespace std;
template <class T>
class HashTable {
  // structure of linked list, used for open hashing
  struct node{
    T* data;
    node* next;
    string key;
    
    // Takes in customer object and key for hashing
    node(T* customer, node* n, string key): data(customer), next(n), key(key) {};
  };
  public:

// constructor
HashTable();
// destructor
~HashTable();
// finding item in hashtable
T* retrieve(string key);
  
void insertItem(string key, T* data);

void deleteItem(string key);
    
// show all contents in hashtable
void printHash();


private:
int hash(int ID);

  // calculation to find remainder
static int const MAXHASHSIZE = 100; // max size of hashtable
 node* array[MAXHASHSIZE]; // array of linked lists
};


// constructor
template<class T>
HashTable<T>::HashTable()
{

   for(int i = 0; i < MAXHASHSIZE; i++) // setting all values to nullptr in array
      array[i] = nullptr;

}

// destructor
// delete all data in array and setting to nullptr
template<class T>
HashTable<T>::~HashTable()
{
   node* curr;
   node* next;
   for(int i = 0; i < MAXHASHSIZE; i++)
   {
      curr = array[i];
      while(curr != nullptr) // if current node isn't empty, delete linked list in array[i]
      {
         delete curr->data;
         curr->data = nullptr;
         next = curr->next;
         if(curr != nullptr)
         {
            delete curr;
         }
         curr = next;
      }
      array[i] = nullptr;
   }


}

// finding item in hashtable
template<class T>
T* HashTable<T>::retrieve(string key)
{
   int num = 0;
   for(int i = 0; i < key.length(); i++)
   {
      num += key[i]; // ID of customer
   }
   int index = hash(num); // hash using ID to get position in hashtable
   node* curr;
   curr = array[index];
   if(curr == nullptr) { 
      return nullptr;
   }
   if(curr->key == key)
      return curr->data;
   while(curr->next != nullptr) // not at end of array
   {
      if(curr->next->key == key)
         return curr->next->data;
      curr = curr->next;
   }
   return nullptr;

}

// insert customer object with data and key
template<class T>
void HashTable<T>::insertItem(string key, T* data)
{
   int num = 0;
   for(int i = 0; i < key.length(); i++)
   {
      num += key[i]; // ID  of customer
   }
   int index = hash(num); //hash using ID to get position in hashtable
   if(array[index] != nullptr)
   {
      node* curr;
      curr = array[index];
      if(curr->data == nullptr) // curr's data is empty, so fill in data and key
      {
         curr->data = data;
         curr->key = key;
      }
      while(curr->next != nullptr) // not at end of array[index]
      {
         if(curr->next->data == nullptr)
         {
            curr->next->data = data;
            curr->next->key = key;
            return;
         }
         curr = curr->next;
      }
     // curr->next and curr are nullptr, make it a new node since it's at the end of the linked list
      curr->next = new node(data, nullptr, key);
   } else
   {
      array[index] = new node(data, nullptr, key);
   }


}

// delete customer object
template<class T>
void HashTable<T>::deleteItem(string key)
{
   if(retrieve(key) != nullptr) // if customer is in array
      delete retrieve(key); // call retrieve to find customer


}

// show all contents in hashtable
template<class T>
void HashTable<T>::printHash()
{
   for(int i = 0; i < MAXHASHSIZE; i++)
      if(array[i] != nullptr)
         cout << *array[i]->data << endl;
}

// calculation to find remainder
template<class T>
int HashTable<T>::hash(int ID)
{

   return ID % MAXHASHSIZE;

} 

#endif //ASSIGNMENT4_HASHTABLE_H



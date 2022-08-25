#include<iostream>
#include<string.h>
#include<bits/stdc++.h>

#ifndef DICTIONARY_H
#define DICTIONARY_H

using namespace std;

// Can change this value for debugging
int DICT_SIZE = 256;

int LIST_SIZE = 64;

// Defines the struct Journey which stores the details of a journey 
struct Journey {
  string start;
  float start_time;
  string end;
  float finish_time;
};

// Defining the entries to the hashTable
struct Entry {
  string key;
  Journey *list;
  int num_journies;
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries
  int num_elements; //To store the current number of entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(string key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // To insert a new Journey in the array of journies
  bool insert(struct Journey j);
  
  // Returns a pointer to the array of Journies which has the given key
  struct Journey *give_list(string key);
};


#endif

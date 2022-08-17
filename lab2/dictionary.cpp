#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"dictionary.h"

using namespace std;

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[])
    {
        //Implementing Hash_Map using polynomial accumulation
        int t = 39; //Multiplier
        int i = 0; //Iterating variable
        long int hash_val = 0; //Hash Value to be calculated
        while(key[i]!='\0')
        {
            hash_val = (hash_val + int(key[i]))*t; //Polynomial accumulation
            i++;
        }
        hash_val = hash_val%21269; //Taking modulus by a huge prime num to prevent any overflow issues

        //Implementing the compression map using Fibonacci hashing scheme
        int hash = 0; //Final hash value will be stored in this
        double A = (sqrt(5)-1)/2; //The multiplier used for fibonacci hashing
        double frac,intpart;
        frac = modf(hash_val*A , &intpart);
        hash = floor(N*(frac)); //Implementing the compression
        return hash;
    }

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[])
    {
        if(num_elements==N) //Array is full if num_elements equal to size of array
        {
            return -1;
        }
        int index = hashValue(key); //Finding out the hash value to find the index to be inserted at
        while (A[index].isempty == false) //Incrementing the index until an empty spot is found
        {
            index = (index+1)%N;
        }
        return index;
            
    }
        
// Default constructor
Dictionary::Dictionary()
    {
        N = DICT_SIZE; //Setting the length of the array
        A = new Entry[N]; //Allocating space to the array
        for(int i=0;i<N;i++)
        {
            A[i].isempty = true; //Setting all entries to isempty(true)
        }
        num_elements = 0; //Initializing num_elements to 0 
    }

//Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry * Dictionary::get(char key[])
    {
        int index = hashValue(key); //Finding out the hash value to find the index
        bool present;
        for(int i=0;i<N;i++)
        {
            if(strcmp(key,A[index].key)==0 && A[index].isempty==false) //Checking if the strings are equal and the index has a element 
            {
                present = true; //Setting boolean to true if match found
                break;
            }
            else
            {
                index = (index+1)%N;
            }
                
        } 
        if(present && A[index].isempty==false)
        {
            return &A[index];
        }
        else
        {
            return NULL;
        }
            
    }

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e)
    {
        int index = findFreeIndex(e.key); //Finding index to insert the element
        if(index == -1)
        {
            return false;
        }
        A[index] = e;
        e.isempty = false;
        num_elements++; 
        return true;
    }

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[])
    {
        Entry* element = get(key); //Getting pointer to the element to remove
        if(element==NULL)
        {
            return false;
        }
        else
        {
            element->isempty = true;
            num_elements--;
            return true;
        }
    }


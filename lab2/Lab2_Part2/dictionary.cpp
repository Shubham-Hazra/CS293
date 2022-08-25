#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"dictionary.h"

using namespace std;

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(string key)
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
int Dictionary::findFreeIndex(string key)
    {
        int index = hashValue(key); //Finding out the hash value to find the index
        if(A[index].num_journies==0)
        {
            return index;
        }
        else if(strcmp(A[index].key.c_str(),key.c_str())==0)
        {
            return index;
        }
        else
        {
            for(int i=0;i<N;i++)
            {
                if(strcmp(A[index].key.c_str(),key.c_str())==0)
                {
                    return index;
                }
                index = (index+1)%N;
            }
            index = hashValue(key);
            for(int i=0;i<N;i++)
            {
                if(A[index].num_journies==0)
                {
                    return index;
                }
                index = (index+1)%N;
            }
        }
        return -1;

    }
        
// Default constructor
Dictionary::Dictionary()
    {
        N = DICT_SIZE; //Setting the length of the array
        A = new Entry[N]; //Allocating space to the array
        for(int i=0;i<N;i++)
        {
            A[i].list = new Journey[LIST_SIZE];
            A[i].num_journies = 0; //Setting all entries to isempty(true)
        }
        num_elements = 0; //Initializing num_elements to 0 
    }

//Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry * Dictionary::get(string key)
    {
        int index = hashValue(key); //Finding out the hash value to find the index
        bool present;
        for(int i=0;i<N;i++)
        {
            if(strcmp(key.c_str(),A[index].key.c_str())==0 && A[index].num_journies!=0) //Checking if the strings are equal and the index has a element 
            {
                present = true; //Setting boolean to true if match found
                break;
            }
            else
            {
                index = (index+1)%N;
            }
                
        } 
        if(present)
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
        num_elements++; 
        return true;
    }

// Inserts a new Journey into the array of journies
// bool Dictionary::insert(struct Journey j)
// {
//     int index = findFreeIndex(j.start); //Finding index to insert the element
//     if(index == -1)
//     {
//         return false;
//     }
//     if(A[index].num_journies==0)
//     {
//         A[index].key = j.start;
//         A[index].list[0]=j;
//         A[index].num_journies++;
//         num_elements++; 
//     }
//     else
//     {
//         int num = A[index].num_journies;
//         A[index].list[num]=j;
//         A[index].num_journies++;
//     }
//     return true;
// }

bool Dictionary::insert(struct Journey j)
{
    int index = findFreeIndex(j.start); //Finding index to insert the element
    if(index == -1)
    {
        return false;
    }
    if(A[index].num_journies==0)
    {
        A[index].key = j.start;
        A[index].list[0]=j;
        A[index].num_journies++;
        num_elements++; 
        return true;
    }
    else if(A[index].num_journies==64)
    {
        return false;
    }
    else
    {
        int num=0;
        while(A[index].list[num].start_time<=j.start_time && num<A[index].num_journies)
        {
            num++;
        }
        if(num==A[index].num_journies)
        {
            A[index].list[num]=j;
            A[index].num_journies++;
            return true;
        }
        else
        {
            Journey term = A[index].list[num];
            A[index].list[num]=j;
            for(int i= num+1;i<A[index].num_journies;i++ )
            {
                Journey temp = A[index].list[i];
                A[index].list[i]=term;
                term = temp;
            }
            A[index].list[A[index].num_journies]=term;
            A[index].num_journies++;
            return true;
        }
    }
}

// Returns the pointer to the list of journies
struct Journey *Dictionary::give_list(string key)
{
    int index = findFreeIndex(key);
    return A[index].list;
}
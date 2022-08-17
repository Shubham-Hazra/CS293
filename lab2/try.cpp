#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;

const int N = 64;

int hashValue(char key[])
{
    //Implementing Hash_Map using polynomial accumulation
    int t =  33; //Multiplier
    int i = 0; //Iterating variable
    long int hash_val = 0; //Hash Value to be calculated
    while(key[i]!='\0')
    {
        hash_val = (hash_val + int(key[i]))*t; //Polynomial accumulation
        i++;
    }

    //Implementing the compression map using Fibonacci hashing scheme
    int hash = 0; //Final hash value will be stored in this
    double A = (sqrt(5)-1)/2; //The multiplier used for fibonacci hashing
    double frac,intpart;
    frac = modf(hash_val*A , &intpart);
    hash = floor(N*(frac)); //Implementing the compression
    return hash;
}

int main()
{
    char name[32];
    cin.getline(name,32);
    cout<<hashValue(name);
}
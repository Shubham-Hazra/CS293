#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>

using namespace std;

int* computeHMatrixForKMP(string pattern) {

  int length = pattern.length();
  int* h = new int[length];
  h[0]=0;
  int len=0,i=1;
  while(i<length)
  {
    if(pattern[len]==pattern[i])
    {
      len++;
      h[i]=len;
      i++;
    }
    else
    {
      if(len>0)
      {
        len = h[len-1];
      }
      else
      {
        h[i] = len;
        i++;
      }
    }
  }
  return h;
}

int KMPMatch(string text, int *hMatrix, string pattern) {

  int pattern_len = pattern.length();
  int text_len = text.length();
  int i = 0;
  int j = 0;
  while(i<text_len)
  {
    if(text[i] == pattern[j])
    {
        i++;
        j++;
        if(j==pattern_len)
        {
            return 1;
        }
    }
    else
    {
      if(j>0)
      {
        j = hMatrix[j-1];
      }
      else
      {
        i++;
      }
    }
  }
  
  return 0;
}


int main()
{

    string text = "AAAAABABMONKEAAABAABAABA";
    string pattern = "MONKE";
    int* hmatrix = computeHMatrixForKMP(pattern);
    cout<< KMPMatch(text,hmatrix,pattern)<<endl;

}



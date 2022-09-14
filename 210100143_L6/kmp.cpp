#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

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

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

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
            return 0;
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
  
  return -1;
}

#endif

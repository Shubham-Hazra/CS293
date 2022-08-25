#include<iostream>
#include<bits/stdc++.h>
#include"dictionary.cpp"

using namespace std;


#ifndef PLANNER_H
#define PLANNER_H

// Defines a station
struct Station {
  string station;
};

class Planner {
  private:
    Dictionary planner;   //Defining a dictionary
  public:
    Planner()
    {
      planner = Dictionary();
    }
    bool add(string station1,float start_time,string station2,float finish_time) //Adds a new Journey to the dictionary
    {
      Journey j;
      j.start = station1;
      j.start_time = start_time;
      j.end = station2;
      j.finish_time = finish_time;
      return planner.insert(j);
    }

    bool query_station(string station1,float start_time) //Defines the function query_station to meet the specifications of the question
    {
      Entry *e = planner.get(station1);
      Journey *list = e->list;
      int count =0;
      for(int i = 0;i<e->num_journies;i++)
      {
        if(list[i].start_time >= start_time)
        {
          cout<<list[i].start_time<<" "<<list[i].end<<endl;
          count++;
        }
      }
      if(count>0)
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    bool query_journey(string station1,float start_time,string station2) //Defines the function query_journey to meet the specifications of the question
    {
      Entry *e = planner.get(station1);
      Journey *list = e->list;
      float starttime=60000;
      float leave_time;
      string intermediate="\0";
      for(int i=0;i<e->num_journies;i++)
      {
        if(list[i].start_time>=start_time && strcmp(list[i].end.c_str(),station2.c_str())==0)
        {
          if(list[i].start_time<=starttime)
          {
            starttime = list[i].start_time;
            leave_time = 60000;
            intermediate="\0";
          }
        }
        if(list[i].start_time>=start_time && strcmp(list[i].end.c_str(),station2.c_str())!=0)
        {
          Entry *e1 = planner.get(list[i].end);
          Journey *list1 = e1->list;
          for(int j=0;j<e1->num_journies;j++)
          {
            if(strcmp(list1[j].end.c_str(),station2.c_str())==0)
            {
              if(list[i].start_time<starttime)
              {
                starttime = list[i].start_time;
                intermediate = list[i].end;
                leave_time = list1[j].start_time;
              }
            }
          }
        }
      }
      if(starttime==60000)
      {
        return false;
      }
      if(leave_time==60000)
      {
        cout<<starttime<<endl;
        return true;
      }
      cout<<starttime<<" "<<intermediate<<" "<<leave_time<<endl;
      return true;
    }

};

#endif


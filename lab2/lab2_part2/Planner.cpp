#include<bits/stdc++.h>
#include"planner.h"
using namespace std;

int main()
{
    Planner p = Planner();
    string s;
    do
    {
        cin>>s;
        if(s=="ADD")
        {
            string station_one,station_two;
            float start_time,finish_time;
            cin>>station_one>>start_time>>station_two>>finish_time;
            bool a =p.add(station_one,start_time,station_two,finish_time);
            if(a)
            {
                continue;
            }
            else
            {
                cout<<"Could not add journey.Planner already full"<<endl;
                continue;
            }
        }
        else if(s=="QUERY_STATION")
        {
            string station_one;
            float start_time;
            cin>>station_one>>start_time;
            bool a = p.query_station(station_one,start_time);
            if(a)
            {
                continue;
            }
            else
            {
                cout<<"No suitable journey found."<<endl;
                continue;
            }
        }
        else if(s=="QUERY_JOURNEY")
        {
            string station_one,station_two;
            float start_time;
            cin>>station_one>>start_time>>station_two;
            bool a = p.query_journey(station_one,start_time,station_two);
            if(a)
            {
                continue;
            }
            else
            {
                cout<<"No suitable journey found."<<endl;
            }
        }
    } while (s!="EXIT");
    
}
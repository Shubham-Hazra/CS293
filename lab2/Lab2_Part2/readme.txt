To implement Planner class I am using the dictionary.h and dictionary.cpp used in the inlab.
I have changed the dictionary class so that instead of storing integers as value, it now stores the pointer to 
an array of journies.
I have defined a struct called journey which stores the start station, start time, finish station and finish time.
I have fixed the sizes of the hash table and the array of journies.
I have made the key of the dictionary as the start station.
i have two new methods called insert and give_list.
Insert is used to insert a new journey into the list of journies.
Give_list returns the pointer to the array of journies.
Then in Planner class I have implemented a dictionary and made 3 new methods.
The 3 methods are used to respectively add a new journey, query_station and query_journey are defined to fit the 
specifications of the problem.
Then finally in Planner.cpp input is taken from the users and the respective commands are executed to make an iteractive module.
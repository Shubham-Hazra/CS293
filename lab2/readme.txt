NAME - SHUBHAM HAZRA
ROLL NO. - 210100143

Added a new member called bool isempty to the struct Entry and a new member int num_elements to 
class Dictionary. 

Implemented the hashValue function using the polynomial accumulation as the hash-map
technique and the fibonacci compression technique.

Implemented findFreeIndex to use the probing method in which if a place is filled 
it checks the next place and so on.

Default constructor initializes N to size of the array that is 64 and initializes A to
array of 64 entries, sets the entries member function isempty to true and num_elements to 0.

Get function is Implemented to first check at the index with the hash hash value then move
forward by 1 place and so on.

Put and remove both use the get function to get the entry and then modifies the isempty member and num_elements
accordingly.

#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <cassert>
#include "sort.cpp"

using namespace std;

vector<string> parse;
void split (string str, char seperator)  
{  
    parse.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            parse.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
}  

int main(int argc, char** argv)
{
    chrono::time_point<chrono::system_clock> start, end;
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    while(true)
    {
    
    SorterTree tree=SorterTree(pivot_chooser,num_entries);
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair

    Journey unsorted[num_entries];

    for(int i=0;i<num_entries;i++)
    {
        int JourneyCode;
        int price;
        cout<<"Enter Journey: ";
        cin>>JourneyCode>>price;
        Journey j = Journey(JourneyCode,price);
        unsorted[i] = j;
        
    }
    start = chrono::system_clock::now();
    for(int i=0;i<num_entries;i++)
    {
        tree.insertElement(unsorted[i].getJourneyCode(),unsorted[i].getPrice());
    }
    if(!tree.QuicksortWithBSTInsert(0,num_entries-1))
    {
        cout<<"Pivot returned by pivot chooser not found in the array."<<endl;
        return 1;
    }
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    // Also write code here to obtain different inputs as in the various parts of the question
    string s;
    cout<<">>>";
    int k=1;
    getline(cin,s);
    while(true){
            if(k!=1)
            {
                cout<<">>>";
            }
			getline(cin,s);
			split(s,' ');
			if(parse[0]=="PRINT"){
				if(parse[1]=="TREE")
                {
                    tree.getTree()->printBST("");
                }
                else if(parse[1]=="SORTED")
                {
                    tree.printArray();
                }
                else if(parse[1]=="UNSORTED")
                {
                    for (int i = 0; i < num_entries; i++)
                    {
                        cout<<"Journey code: "<<unsorted[i].getJourneyCode()<<"\tJourney Price:"<<unsorted[i].getPrice()<<endl;
                    }
                }
                else{
				    cout<<"INVALID REQUEST"<<endl;
			    }
			}else if(parse[0]=="IMBALANCE"){
				cout<<"The imbalance in the tree is: "<<tree.getTree()->getImbalance()<<endl;
			}else if(parse[0]=="COMPARISONS"){
				cout<<"Number of Comparisons: "<<tree.getComparisons()<<endl;
			}else if(parse[0]=="EXIT"){
                break;
            }else if(parse[0]=="TIME"){
                cout<<"Time elapsed: "<<elapsed_seconds.count()<<"s"<<endl;
            }
            else if(parse[0]=="CHANGE" && parse[1]=="SORT" && parse[2]=="MODE"){
                SorterTree* tree_new = new SorterTree(stoi(parse[3]),num_entries);
                for(int i=0;i<num_entries;i++)
                {
                    
                    tree_new->insertElement(unsorted[i].getJourneyCode(),unsorted[i].getPrice());
                }
                start = chrono::system_clock::now();
                if(!tree_new->QuicksortWithBSTInsert(0,num_entries-1))
                {
                    cout<<"Pivot returned by pivot chooser not found in the array."<<endl;
                    return 1;
                }
                end = chrono::system_clock::now();
                elapsed_seconds = end - start;
                tree = *tree_new; 
            }
			else{
				cout<<"INVALID REQUEST"<<endl;
			}
            k=0;

		}
        string str;
        cout<<"Do you want to quit? y or n: ";
        cin>>str;
        if(str=="y")
        {
            break;
        }
        else if(str=="n")
        {
            continue;
        }
    }
}


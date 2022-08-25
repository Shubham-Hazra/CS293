#include <bits/stdc++.h>
using namespace std;
#include "BST.cpp"

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

int main(){
	int i,j,k,N,t;
		cout<<"Enter the number of Nodes, you'd like to have?";
		cin>>N;
		BST *b1 = new BST();
		for(i = 0;i<N;i++){
				cin>>j>>k;
                b1->insert(j,k);
		}
        b1->printBST("");
		b1->customStore("test.txt");
        // BST *b1 = new BST();
        // b1->customLoad(4,"test.txt");
        // b1->printBST("");
	}

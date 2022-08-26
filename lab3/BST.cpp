#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS


//Constructor functions
BST::BST()
{ 
    root = new TreeNode();
    root->parent=NULL;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if(findjourney(JourneyCode)) //Returns false if JourneyCode already present
    {
        return false;  
    }
    if(root->JourneyCode==0 && root->price==0) //For empty tree, initializes root
    {
        root->JourneyCode=JourneyCode;
        root->price=price;
        return true;
    }
    TreeNode* ptr_parent=NULL;
    TreeNode* ptr=root;
    
    while(ptr!=NULL) // General insertion at the leaves
    {
        if(price>ptr->price) // Finds the leaf to insert at
        {  
            ptr_parent=ptr;
            ptr = ptr->right;
            continue;
        }
        else
        {
            ptr_parent=ptr;
            ptr=ptr->left;
            continue;
        }
    }
    if(ptr_parent->price>=price) // Checks whether to insert as left or right child
    {
        ptr_parent->left=new TreeNode(JourneyCode,price);
        ptr_parent->left->parent=ptr_parent;
    }
    else
    {
        ptr_parent->right= new TreeNode(JourneyCode,price);
        ptr_parent->right->parent=ptr_parent;
    }
    return true;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{   
    TreeNode* ptr = root;
    while (ptr!=NULL) //Looping till ptr becomes NULL
    {
        if(price==ptr->price) // Checks for the price and moves to left or right child accordingly
        {
            if(JourneyCode==ptr->JourneyCode) // Checks if the JourneyCodes are equal and returns true if equal else continues
            {
                return true;
            }
            else
            {
                ptr=ptr->left;
                continue;
            }
        }
        else if(price>ptr->price)
        {
            ptr = ptr->right;
            continue;
        }
        else
        {
            ptr=ptr->left;
            continue;
        }
    }
    return false;
   
}

//Returns true if an entry with the given journey code is found 
bool BST::findjourney(int JourneyCode)
{
    return findjourney(JourneyCode,root);
}

//Function for recursion to find JourneyCode
bool BST::findjourney(int JourneyCode,TreeNode* ptr)  
{
    if(ptr==NULL) // Returns false if pointer is NULL
    {
        return false;
    }
    if(ptr->JourneyCode==JourneyCode) // Checks at the pointer, returns true if found
    {
        return true;
    }
    else
    {
        return findjourney(JourneyCode,ptr->left)||findjourney(JourneyCode,ptr->right); // Checks the left and right subtree 
    }
}


//Returns the pointer to the given entry if found else returns NULL
TreeNode* BST::get(int JourneyCode,int price)
{
    TreeNode* ptr = root;
    while (ptr!=NULL)
    {
        if(price==ptr->price)
        {
            if(JourneyCode==ptr->JourneyCode)
            {
                return ptr;
            }
            else
            {
                ptr=ptr->left;
                continue;
            }
        }
        else if(price>ptr->price)
        {
            ptr = ptr->right;
            continue;
        }
        else
        {
            ptr=ptr->left;
            continue;
        }
    }
    return NULL;
   
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{

    if(findjourney(JourneyCode)==false)
    {
        return false;
    }
    TreeNode* element = get(JourneyCode,price);
    if(element==NULL)
    {
        return false;
    }
    if(element->left==NULL && element->right==NULL)
    {
        if(element->parent==NULL)
        {
            element->JourneyCode=0;
            element->price=0;
        }
        else
        {
            if(element==element->parent->left)
            {
                element->parent->left=NULL;
            }
            else
            {
                element->parent->right=NULL;
            }
        }
    }
    else if(element->left==NULL || element->right==NULL)
    {
        if(element->parent==NULL)
        {
            if(element->left==NULL)
            {
                root = element->right;
                element->right->parent=NULL;
            }
            else
            {
                root = element->left;
                element->left->parent=NULL;
            }
        }
        else
        {
            if(element->left==NULL)
            {
                if(element==element->parent->left)
                {
                    element->parent->left=element->right;
                    element->right->parent=element->parent;
                }
                else
                {
                    element->parent->right=element->right;
                    element->right->parent=element->parent;
                }
            }
            else
            {
                if(element==element->parent->left)
                {
                    element->parent->left=element->left;
                    element->left->parent=element->parent;
                }
                else
                {
                    element->parent->right=element->left;
                    element->left->parent=element->parent;
                }
            }
        }
    }
    else
    {
        TreeNode* ptr1=element->right;
        TreeNode* ptr1_parent = element;
        while(ptr1!=NULL)
        {
            ptr1_parent = ptr1;
            ptr1=ptr1->left;
        }
        TreeNode* succ = ptr1_parent;
        element->JourneyCode = succ->JourneyCode;
        element->price=succ->price;
        if(succ==succ->parent->right)
        {
            succ->parent->right=succ->right;
            if(succ->right!=NULL)
            {
                succ->right->parent=succ->parent;
            }
        }
        else
        {
            succ->parent->left=succ->right;
            if(succ->right!=NULL)
            {
                succ->right->parent=succ->parent;
            }
        }
    }
    return true;
}


//Returns the pointer to the successor of the given node if found or else returns NULL 
TreeNode* BST::successor(int JourneyCode,int price)
{
    TreeNode* element = get(JourneyCode,price);
    if(element->right!=NULL)
    {
        TreeNode* ptr1=element->right;
        TreeNode* ptr1_parent = element;
        while(ptr1!=NULL)
        {
            ptr1_parent = ptr1;
            ptr1=ptr1->left;
        }
        return ptr1_parent;
    }
    else
    {
        if(element->parent==NULL)
        {
            return NULL;
        }
        else
        {
            TreeNode* ptr = element->parent;
            while (ptr!=NULL && element==ptr->right)
            {
                element=ptr;
                ptr=ptr->parent;
            }
            return ptr;
        }
        
    }


}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if(typeOfTraversal==0)
    {
        preorder(root);
    }
    else if(typeOfTraversal==1)
    {
        postorder(root);

    }
    else if(typeOfTraversal==2)
    {
       inorder(root);
    }
}

//Function to use recursion to find preorder traversal
void BST::preorder(TreeNode* ptr)
{
    cout<<ptr->JourneyCode<<endl;
        if(ptr->left==NULL)
        {
            return;
        }
        else
        {
            preorder(ptr->left);
        }
        if(ptr->right==NULL)
        {
            return;
        }
        else
        {
            preorder(ptr->right);
        }

}

//Function to use recursion to find postorder traversal
void BST::postorder(TreeNode* ptr)
{
    if(ptr->left==NULL)
        {
            return;
        }
        else
        {
            postorder(ptr->left);
        }
        if(ptr->right==NULL)
        {
            return;
        }
        else
        {
            postorder(ptr->right);
        }
        cout<<ptr->JourneyCode<<endl;
}

//Function to use recursion to find inorder traversal
void BST::inorder(TreeNode* ptr)
{
     if(ptr->left==NULL)
        {
            return;
        }
        else
        {
            inorder(ptr->left);
        }
        cout<<ptr->JourneyCode<<endl;
        if(ptr->right==NULL)
        {
            return;
        }
        else
        {
            inorder(ptr->right);
        }
    
}



// Returns the price of the cheapest journey
int BST::getMinimum() 
{
    TreeNode* ptr_parent = NULL;
    TreeNode* ptr = root;
    while(ptr!=NULL)
    {
        ptr_parent=ptr;
        ptr=ptr->left;
    }
    return ptr_parent->price;
}

//Returns the pointer to the root 
TreeNode* BST::getroot()
{
    return root;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    return countJourneysInPriceBound(lowerPriceBound,upperPriceBound,root);
}


//Function to use recursion to get the number of journies
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound,TreeNode* ptr)
{
    if(ptr==NULL)
    {
        return 0;
    }
    if(ptr->price<=upperPriceBound && ptr->price>=lowerPriceBound)
    {
        return 1 + countJourneysInPriceBound(lowerPriceBound,upperPriceBound,ptr->left)+countJourneysInPriceBound(lowerPriceBound,upperPriceBound,ptr->right);
    }
    else
    {
        return countJourneysInPriceBound(lowerPriceBound,upperPriceBound,ptr->left)+countJourneysInPriceBound(lowerPriceBound,upperPriceBound,ptr->right);
    }
}


// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    ofstream outfile;
    outfile.open(filename);
    storeBST(outfile,root,NULL);
    outfile.close();
}


//Function to support recursion to store the BST
//Takes a file pointer as argument
void BST::storeBST(ofstream &outfile,TreeNode* ptr,TreeNode* ptr_parent)
{
    if(ptr==NULL)
    {
        return;
    }
    outfile<<ptr->JourneyCode<<","<<ptr->price<<",";
    if(ptr->left!=NULL && ptr->right!=NULL)
    {
        outfile<<"("<<",";
        storeBST(outfile,ptr->left,ptr);
        outfile<<")"<<",";
        outfile<<"{"<<",";
        storeBST(outfile,ptr->right,ptr);
        outfile<<"}"<<",";
    }
    else if(ptr->left!=NULL || ptr->right!=NULL)
    {
        if(ptr->left==NULL)
        {
            outfile<<"{"<<",";
            storeBST(outfile,ptr->right,ptr);
            outfile<<"}"<<",";
        }
        else
        {
            outfile<<"("<<",";
            storeBST(outfile,ptr->left,ptr);
            outfile<<")"<<",";
        }
    }
    else
    {
        return;
    }
}

	
// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.
 
void BST::customLoad (int flag, string filename)
{
    if(flag==4)  //To load the left subtree
    {
    ifstream infile;
    infile.open(filename);
    string s;
    infile>>s;
    vector<string> parse;
    parse.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= s.length())  
    {  
        if (s[i] == ',' || i == s.length())  
        {  
            endIndex = i;
            parse.push_back(s.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
    }
    TreeNode* ptr = root;
    int num_brackets;
    if(parse[2]=="(")
    {
        root->JourneyCode=stoi(parse[3]);
        root->price=stoi(parse[4]);
        num_brackets=1;
    }
    else
    {
        num_brackets=0;
    }
    for(int j=5;j<parse.size();j++)
    {
        if(num_brackets==0)
        {
            break;
        }
        if(parse[j]=="(")
        {
            TreeNode* node = new TreeNode();
            ptr->left = node;
            ptr->left->JourneyCode=stoi(parse[j+1]);
            ptr->left->price=stoi(parse[j+2]);
            ptr->left->parent=ptr;
            ptr->left->left=NULL;
            ptr->left->right=NULL;
            ptr = ptr->left;
            num_brackets++;
        }
        else if(parse[j]==")")
        {
            ptr = ptr->parent;
            num_brackets--;
        }
        else if(parse[j]=="{")
        {
            TreeNode* node = new TreeNode();
            ptr->right = node;
            ptr->right->JourneyCode=stoi(parse[j+1]);
            ptr->right->price=stoi(parse[j+2]);
            ptr->right->parent=ptr;
            ptr->right->left=NULL;
            ptr->right->right=NULL;
            ptr = ptr->right;
            num_brackets++;
        }
        else if(parse[j]=="}")
        {
            ptr=ptr->parent;
            num_brackets--;
        }
        else
        {
            continue;
        }
    }
    } 
    if(flag==3)  //To load the Full BST
    {
        ifstream infile;
    infile.open(filename);
    string s;
    infile>>s;
    vector<string> parse;
    parse.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= s.length())  
    {  
        if (s[i] == ',' || i == s.length())  
        {  
            endIndex = i;
            parse.push_back(s.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
    }
    TreeNode* ptr = root;
    root->JourneyCode=stoi(parse[0]);
    root->price=stoi(parse[1]); 
    for(int j=2;j<parse.size();j++)
    {
        if(parse[j]=="(")
        {
            TreeNode* node = new TreeNode();
            ptr->left = node;
            ptr->left->JourneyCode=stoi(parse[j+1]);
            ptr->left->price=stoi(parse[j+2]);
            ptr->left->parent=ptr;
            ptr->left->left=NULL;
            ptr->left->right=NULL;
            ptr = ptr->left;
        }
        else if(parse[j]==")")
        {
            ptr = ptr->parent;
        }
        else if(parse[j]=="{")
        {
            TreeNode* node = new TreeNode();
            ptr->right = node;
            ptr->right->JourneyCode=stoi(parse[j+1]);
            ptr->right->price=stoi(parse[j+2]);
            ptr->right->parent=ptr;
            ptr->right->left=NULL;
            ptr->right->right=NULL;
            ptr = ptr->right;
        }
        else if(parse[j]=="}")
        {
            ptr=ptr->parent;
        }
        else
        {
            continue;
        }
    }
    }
}


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}


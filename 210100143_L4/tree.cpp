// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  int shortestpath = shortest(root);
  int longestpath = longest(root);
  return longestpath - shortestpath;
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
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
        if(JourneyCode>ptr->JourneyCode) // Finds the leaf to insert at
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
    if(ptr_parent->JourneyCode>=JourneyCode) // Checks whether to insert as left or right child
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

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    

    
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  TreeNode* ptr = root;
    while (ptr!=NULL) //Looping till ptr becomes NULL
    {
        if(JourneyCode==ptr->JourneyCode) // Checks for the price and moves to left or right child accordingly
        {
            if(price==ptr->price) // Checks if the JourneyCodes are equal and returns true if equal else continues
            {
                return true;
            }
            else
            {
                ptr=ptr->left;
                continue;
            }
        }
        else if(JourneyCode>ptr->JourneyCode)
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
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
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
        if(JourneyCode==ptr->JourneyCode)
        {
            if(price==ptr->price)
            {
                return ptr;
            }
            else
            {
                ptr=ptr->left;
                continue;
            }
        }
        else if(JourneyCode>ptr->JourneyCode)
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

int BST::min(int a,int b)
  {
    if(a>=b)
    {
      return b;
    }
    else
    {
      return a;
    }
  }

int BST::max(int a,int b)
  {
    if(a>=b)
    {
      return a;
    }
    else
    {
      return b;
    }
  }

int BST::longest(TreeNode* ptr)
  {
    if(ptr->left==NULL && ptr->right==NULL)
    {
      return 1;
    }
    else if(ptr->left==NULL || ptr->right==NULL)
    {
        if(ptr->left==NULL)
        {
            return 1+longest(ptr->right);
        }
        else
        {
            return 1+longest(ptr->left);
        }
    }
    else
    {
      return 1+max(longest(ptr->left),longest(ptr->right));
    }
  }


int BST::shortest(TreeNode* ptr)
  {
    if(ptr->left==NULL && ptr->right==NULL)
    {
      return 1;
    }
    else if(ptr->left==NULL || ptr->right==NULL)
    {
        if(ptr->left==NULL)
        {
            return 1+shortest(ptr->right);
        }
        else
        {
            return 1+shortest(ptr->left);
        }
    }
    else
    {
      return 1+min(shortest(ptr->left),shortest(ptr->right));
    }
  }


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
        result.push_back(root->JourneyCode + "\n");
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


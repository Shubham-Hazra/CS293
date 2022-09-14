#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
TreeNode* node = new TreeNode(jrnyCode,price);
 if(find(jrnyCode)==1) //Returns false if JourneyCode already present
    {
        return false;  
    }
    if(root==NULL) //For empty tree, initializes root
    {
        root = node;
        return true;
    }
    TreeNode* ptr_parent=NULL;
    TreeNode* ptr=root;
    while(ptr!=NULL) // General insertion at the leaves
    {
        if(BSTLessThan(ptr,node)) // Finds the leaf to insert at
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
    if(BSTLessThan(node,ptr_parent)) // Checks whether to insert as left or right child
    {
        updateBSTParentChild(node,ptr_parent,true);
    }
    else
    {
        updateBSTParentChild(node,ptr_parent,false);
    }

    // After the node is insersted 
    // Backtrace the path to the root updating the values of height at each node
    ptr=node;
    ptr_parent=node->parent;

    // Back traces till ptr reaches root
    while(ptr_parent != NULL)
    {
      if(ptr_parent->left==ptr)
      {
        if(ptr_parent->right==NULL)
        {
          ptr_parent->height++;
        }
        else
        {
          if(ptr_parent->right->height>=ptr->height)
          {
            break;
          }
          else
          {
            ptr_parent->height++;
          }
        }
      }
      if(ptr_parent->right==ptr)
      {
        if(ptr_parent->left==NULL)
        {
          ptr_parent->height++;
        }
        else
        {
          if(ptr_parent->left->height>=ptr->height)
          {
            break;
          }
          else
          {
            ptr_parent->height++;
          }
        }
      }
      ptr=ptr_parent;
      ptr_parent=ptr_parent->parent;
    }


  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  TreeNode* node = new TreeNode(jrnyCode,0); // Creates a new TreeNode which will be used as the object to search using BSTlessThan
  if(findjourney(node,root))  // Searches for node starting at root
  {
    return 1; // Returns 1 if found
  }
  else
  {
    return -1; // Returns -1 if not found
  }
}

//Function for recursion to find JourneyCode
bool BST::findjourney(TreeNode* comp,TreeNode* ptr)  
{
    if(ptr==NULL) // Returns false if pointer is NULL
    {
        return false;
    }
    if(BSTLessThan(comp,ptr)) // Uses BSTlessThan. If journey code of comp is less than that of pointer, searches left branch of tree
    {
      return findjourney(comp,ptr->left);
    }
    else if(BSTLessThan(ptr,comp)) // Uses BSTlessThan. If journey code of comp is more than that of pointer, searches right branch of tree
    {
      return findjourney(comp,ptr->right);
    }
    else // If comp is neither smaller nor greater then it must be equal. Returns true.
    {
      return true;
    }
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  return true;
}



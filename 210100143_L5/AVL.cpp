#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  if(greatGrandParentNode==NULL) // If greatgrand parent is null then perform the rotation and set the root value to the parent node
  {
    TreeNode *T3 = parentNode->right;
    updateAVLParentChild(grandParentNode,parentNode,false);
    updateAVLParentChild(T3,grandParentNode,true);
    this->changeroot(parentNode);
    updateAVLParentChild(parentNode,NULL,true); // Set the parent of the parent node as null pointer 
    return true;
  }
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parentNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the right subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(greatGrandParentNode==NULL) // If greatgrand parent is null then perform the rotation and set the root value to the current node
  {
    TreeNode *T2 = currNode->left;
    TreeNode *T1 = currNode->right;
    updateAVLParentChild(grandParentNode,currNode,false);
    updateAVLParentChild(parentNode,currNode,true);
    updateAVLParentChild(T1,grandParentNode,true);
    updateAVLParentChild(T2,parentNode,false);
    updateAVLParentChild(currNode,NULL,true); // Set the parent of the current node to null pointer 
    this->changeroot(currNode);
    return true;
  }
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, false);
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parentNode (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parentNode and the right child of grandParentNode
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parentNode (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParentNode (i.e. of z).
       
  // Let's implement these updations below.
       
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the right child of grandParentNode.  That's
  // why we are doing a rotateRightLeft

  TreeNode *greatGrandParentNode = grandParent->parent;
  if(greatGrandParentNode==NULL) // If greatgrand parent is null then perform the rotation and set the root value to the parent node
  {
    TreeNode *T1 = currNode->left;
    TreeNode *T2 = currNode->right;
    updateAVLParentChild(grandParent,currNode,true);
    updateAVLParentChild(parent,currNode,false);
    updateAVLParentChild(T1,grandParent,false);
    updateAVLParentChild(T2,parent,true);
    updateAVLParentChild(currNode,NULL,true); // Set the parent of the current node to null pointer
    this->changeroot(currNode);
    return true;
  }
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T1 be the left child of currNode (i.e. of x)
  TreeNode *T1 = currNode->left;
  
  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that parentNode should be
  // made the right child of currNode
  updateAVLParentChild(parent, currNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should NOT be made the right child of currNode
  updateAVLParentChild(grandParent, currNode, true);
             
  // We use "true" as the third argument of the following call to indicate
  // that T2 should become the left child of ParentNode
  updateAVLParentChild(T2, parent, true);

  // We use "false" as the third argument of the following call to indicate
  // that T3 should NOT become the left child of grandParentNode
  updateAVLParentChild(T1, grandParent, false);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the right child of grandParentNode
  // That's why we are doing a rotateRightRight

  TreeNode *greatGrandParentNode = grandParent->parent;
  
  if(greatGrandParentNode==NULL) // If greatgrand parent is null then perform the rotation and set the root value to the parent node
  {
    TreeNode *T1 = parent->left;
    updateAVLParentChild(grandParent,parent,true);
    updateAVLParentChild(T1,grandParent,false);
    this->changeroot(parent);
    updateAVLParentChild(parent,NULL,true); // Set the parent of the parent node to null pointer
    return true;
  }
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T1 be the left child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T1 = parent->left;

  // Now replicate the single rotation for RightRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that currNode should be
  // made the right child of parentNode
  updateAVLParentChild(currNode, parent, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of parentNode
  updateAVLParentChild(grandParent, parent, true);

  // We use "false" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T1, grandParent, false);

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
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
        if(AVLLessThan(ptr,node)) // Finds the leaf to insert at
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
    if(AVLLessThan(node,ptr_parent)) // Checks whether to insert as left or right child
    {
        updateAVLParentChild(node,ptr_parent,true); // Updates the parent and child node appropriately using the function updateAVLParentChild
    }
    else
    {
        updateAVLParentChild(node,ptr_parent,false); // Updates the parent and child node appropriately using the function updateAVLParentChild
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
      // Checks for imbalance at the grandparent node and stops updating heights further if imbalance is found
      // since a rotation is needed and the heights of the nodes above the grandparent remains unchanged
      TreeNode* grandparent = ptr_parent->parent;
      ptr=ptr_parent;
      ptr_parent=ptr_parent->parent;
      if(grandparent!=NULL)
      {
        int diff;
        if(grandparent->left==NULL)
        {
          diff = grandparent->right->height+1;
        }
        else if(grandparent->right==NULL)
        {
          diff = grandparent->left->height+1;
        }
        else
        {
          diff = grandparent->left->height - grandparent->right->height;
        }
        if(diff>1 || diff<-1)
        {
          grandparent->height++;
          break;
        }
      }
    }

    // After inserting the node and updating the heights of the nodes upto root if no imbalance found 
    // or after updating heights till first imbalance found 
    // Searches for the type of rotation to be performed 
    ptr=node;
    TreeNode* parent = ptr->parent;
    if(parent==NULL)
    {
      return true;
    }
    TreeNode* grandparent = parent->parent;
    if(grandparent==NULL)
    {
      return true;
    }
    while(grandparent!=NULL) // Manages rotation when one child of the grandparent is null and updates the heights accordingly
    {
      if(grandparent->right==NULL || grandparent->left==NULL)
      {
        if(parent==grandparent->left && ptr ==parent->left)
          {
            rotateLeftLeft(ptr,parent,grandparent);
            grandparent->height-=2;
          }
          else if(parent==grandparent->left && ptr ==parent->right)
          {
            rotateLeftRight(ptr,parent,grandparent);
            grandparent->height-=2;
            parent->height--;
            ptr->height++;
          }
          else if(parent==grandparent->right && ptr ==parent->left)
          {
            rotateRightLeft(ptr,parent,grandparent);
            grandparent->height-=2;
            parent->height--;
            ptr->height++;
          }
          else
          {
            rotateRightRight(ptr,parent,grandparent);
            grandparent->height-=2;
          }
        return true;
      }
      else
      {
        // Manages normal rotations when the grandparent has both children
        // and updates the heights accordingly
        int diff =  grandparent->left->height - grandparent->right->height;
        if(diff<2 && diff>-2)
        { 
          grandparent = grandparent->parent;
          parent = parent->parent;
          ptr = ptr->parent;
          continue;
        }
        else
        {
          if(parent==grandparent->left && ptr ==parent->left)
          {
            rotateLeftLeft(ptr,parent,grandparent);
            grandparent->height-=2;
          }
          else if(parent==grandparent->left && ptr ==parent->right)
          {
            rotateLeftRight(ptr,parent,grandparent);
              grandparent->height-=2;
              parent->height--;
              ptr->height++;
          }
          else if(parent==grandparent->right && ptr ==parent->left)
          {
            rotateRightLeft(ptr,parent,grandparent);
            grandparent->height-=2;
            parent->height--;
            ptr->height++;
          }
          else
          {
            rotateRightRight(ptr,parent,grandparent);
            grandparent->height-=2;
          }
          return true;
        }
      }
    }


  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  TreeNode* node = new TreeNode(jrnyCode,0); // Creates a new TreeNode which will be used as the object to search using AVLlessThan
  if(findjourney(node,root)) // Searches for node starting at root
  {
    return 1; // Returns 1 if found
  }
  else
  {
    return -1; // Returns -1 if not found
  }
}

//Function for recursion to find JourneyCode
bool AVLTree::findjourney(TreeNode* comp,TreeNode* ptr)  
{
    if(ptr==NULL) // Returns false if pointer is NULL
    {
        return false;
    }
    if(AVLLessThan(comp,ptr)) // Uses AVLlessThan. If journey code of comp is less than that of pointer, searches left branch of tree
    {
      return findjourney(comp,ptr->left);
    }
    else if(AVLLessThan(ptr,comp)) // Uses AVLlessThan. If journey code of comp is more than that of pointer, searches right branch of tree
    {
      return findjourney(comp,ptr->right);
    }
    else
    {
      return true; // If comp is neither smaller nor greater then it must be equal. Returns true.
    }
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation(s) should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}



#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{
  int component = 1;
  for (int i = 0; i < numNodes; i++) // For all nodes checks if the node has a component number assigned to it
  {
    if (nodes[i].component_num == 0) // If component number not assigned, starts DFS from that node
    {
      if (trees == nullptr) // Creates a new BST for a new DFS and adds to the linked list of BSTs
      {
        BST *bst = new BST();
        listOfObjects<BST *> *new_tree = new listOfObjects<BST *>(bst);
        trees = new_tree;
        trees_tail = new_tree;
      }
      else
      {
        BST *bst = new BST();
        listOfObjects<BST *> *new_tree = new listOfObjects<BST *>(bst);
        trees_tail->next = new_tree;
        new_tree->prev = trees_tail;
        trees_tail = trees_tail->next;
      }
      connected_components = component;                         // Updates connected_components number
      DFS(&nodes[i], &nodes[i], component, trees_tail->object); // Calls the recursive DFS function
      component++;
    }
  }
  for (int i = 0; i < numNodes; i++) // Traverses over the list of nodes once to get the required information
  {
    if (nodes[i].visited == 1) // Counts and updates the number of nodes visited once
    {
      visited_once++;
    }
    else if (nodes[i].visited == 2) // Counts and updates the number of nodes visited twice
    {
      visited_twice++;
    }
    if (nodes[i].incycle) // Counts and updates the number of nodes in a cycle
    {
      nodes_incycle++;
    }
  }
}

// The function which recursively calls itself to perform DFS
void Graph::DFS(Node *root, Node *node, int component, BST *tree)
{
  listOfObjects<Node *> *ptr = node->adjacent;
  node->visited++;
  node->component_num = component;
  tree->insert(node->value); // Inserts the value in the node into the BST
  while (ptr != nullptr)     // For all nodes adjacent to node
  {
    if (ptr->object->visited == 0) // If the node was unvisited
    {
      ptr->object->parent = node;
      DFS(root, (ptr->object), component, tree); // Recursive call
    }
    else if (ptr->object->visited == 1 && node->parent != ptr->object) // If the node was visited only once
    {
      // ptr->object->incycle = true;
      // Node *ptr1 = node;
      // while (ptr1 != ptr->object && ptr1 != nullptr)
      // {
      //   ptr1->incycle = true;
      //   ptr1 = ptr1->parent;
      // }
      DFS(root, (ptr->object), component, tree); // Recursive call
    }
    ptr = ptr->next;
  }
}

// Function to print all the relevant results
void Graph::printResults()
{
  cout << "No.of connected components : " << connected_components << endl;
  cout << "No.of nodes visited once : " << visited_once << endl;
  cout << "No.of nodes visited twice : " << visited_twice << endl;
  cout << "No.of nodes that are present in a cycle : " << nodes_incycle << endl;
  listOfObjects<BST *> *ptr = trees;
  while (ptr != nullptr) // Prints all the BSTs for the respective connected components
  {
    ptr->object->printBST("", false);
    cout << endl;
    ptr = ptr->next;
  }
  return;
}

// Constructor of the BST
BST::BST()
{
  root = new TreeNode();
  root->parent = NULL;
}

// Insert function for the BST
bool BST::insert(int val)
{
  if (root->value == 0) // For empty tree, initializes root
  {
    root->value = val;
    return true;
  }
  TreeNode *ptr_parent = NULL;
  TreeNode *ptr = root;

  while (ptr != NULL) // General insertion at the leaves
  {
    if (val >= ptr->value) // Finds the leaf to insert at
    {
      ptr_parent = ptr;
      ptr = ptr->right;
      continue;
    }
    else
    {
      ptr_parent = ptr;
      ptr = ptr->left;
      continue;
    }
  }
  if (ptr_parent->value > val) // Checks whether to insert as left or right child
  {
    ptr_parent->left = new TreeNode(val);
    ptr_parent->left->parent = ptr_parent;
  }
  else
  {
    ptr_parent->right = new TreeNode(val);
    ptr_parent->right->parent = ptr_parent;
  }
  return true;
}

// Prints the BST
void BST::printBST(const string &prefix, bool isLeft = false)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->value << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

#endif

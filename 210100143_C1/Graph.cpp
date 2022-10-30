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
    int time = 0;
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
      connected_components = component; // Updates connected_components number
      stack_push(&nodes[i]);
      DFS(component, trees_tail->object, time); // Calls the recursive DFS function
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
void Graph::DFS(int component, BST *tree, int time)
{
  while (stack != nullptr) // Doing till stack isn't empty
  {
    Node *node = stack_pop(); // Getting the top element from the stack and also removing it from the stack
    listOfObjects<Node *> *ptr = node->adjacent;
    if (node->visited == 0) // If it is the first time getting visited, assigning an arrival time
    {
      node->arrTime = time;
      time++;
    }
    node->visited++;                 // Incrementing the visited value
    node->component_num = component; // Assigning the component value
    tree->insert(node->value);       // Inserts the value in the node into the BST
    while (ptr != nullptr)           // Checking for cycles
    {
      if (ptr->object->arrTime < node->arrTime && node->parent != ptr->object) // If arrival time of adjacent node is less than current and node is not the parent, cycle must be present
      {
        ptr->object->incycle = true;
        Node *ptr1 = node;
        while (ptr1 != ptr->object && ptr1 != nullptr)
        {
          ptr1->incycle = true;
          ptr1 = ptr1->parent;
        }
      }
      ptr = ptr->next;
    }
    ptr = node->adjacent;
    if (node->visited < 3) // If the node is visited less than three times i.e one or two times
    {
      while (ptr != nullptr) // For all nodes adjacent to node
      {
        if (ptr->object->visited == 0) // If the node was unvisited
        {
          ptr->object->parent = node; // Assigning the parent when it is visited the first time
          stack_push(ptr->object);
          DFS(component, tree, time); // Recursive call
        }
        else if (ptr->object->visited == 1 && node->parent != ptr->object) // If the node was visited only once
        {
          stack_push(ptr->object);
          DFS(component, tree, time); // Recursive call
        }
        ptr = ptr->next;
      }
    }
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

// Pops the topmost element and returns it
Node *Graph::stack_pop()
{
  if (stack_tail == nullptr) // If stack empty, returns null
  {
    return nullptr;
  }
  else if (stack_tail->prev == nullptr) // If stack only has one element
  {
    Node *temp = stack_tail->object;
    stack_tail = nullptr;
    stack = nullptr;
    return temp;
  }
  else
  {
    Node *temp = stack_tail->object;
    stack_tail = stack_tail->prev;
    stack_tail->next = nullptr;
    return temp;
  }
}

// Pushes the new element into the stack
void Graph::stack_push(Node *node)
{
  if (stack == nullptr) // If stack is empty
  {
    listOfObjects<Node *> *new_node = new listOfObjects<Node *>(node);
    stack = new_node;
    stack_tail = new_node;
  }
  else
  {
    listOfObjects<Node *> *new_node = new listOfObjects<Node *>(node);
    stack_tail->next = new_node;
    new_node->prev = stack_tail;
    stack_tail = stack_tail->next;
  }
}

// Returns the topmost element in the stack
Node *Graph::stack_top()
{
  if (stack_tail == nullptr) // If stack is empty, returns null
  {
    return nullptr;
  }
  else
  {
    return stack_tail->object;
  }
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
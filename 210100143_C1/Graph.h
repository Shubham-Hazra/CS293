#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <vector>
#include <limits>

// Template class to use as a node in linked lists
template <typename T>
class listOfObjects
{
public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;

  // Constructor
  listOfObjects(T initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }

  // Destructor
  ~listOfObjects() { ; }
};

struct TreeNode
{
  int value;        // Value
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root

  // Constructors

  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
  TreeNode(int val, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(val), left(leftChild), right(rightChild), parent(parent) {}
};

// The implementation of a binary search tree
class BST
{
  TreeNode *root; // The pointer to the root node
  vector<string> result;

public:
  // Constructors!
  BST();
  BST(TreeNode *root);
  // Methods
  void printBST(const string &prefix, bool isLeft);
  bool insert(int val);
};

class Node
{
  // insert other fields and methods as appropriate
public:
  int value;
  int visited;
  int arrTime;
  listOfObjects<Node *> *adjacent;
  bool incycle;
  int component_num;
  Node *parent;

  Node()
  {
    visited = 0;
    arrTime = numeric_limits<int>::max(); // Initializing arrival times to a really large value
    adjacent = nullptr;
    incycle = false;
    component_num = 0;
    parent = nullptr;
  }
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation

  int connected_components;          // Number of connected components in the graph
  int visited_once;                  // Number of nodes visited once
  int visited_twice;                 // Number of nodes visited_twice
  int nodes_incycle;                 // Number of nodes present in atleast one cycle
  listOfObjects<BST *> *trees;       // The head of the linked list contaning pointers to BSTs
  listOfObjects<BST *> *trees_tail;  // The tail of the linked list containing pointers to BSTs
  listOfObjects<Node *> *stack;      // The bottom of the stack
  listOfObjects<Node *> *stack_tail; // The top of the stack

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    connected_components = 0;
    visited_once = 0;
    visited_twice = 0;
    nodes_incycle = 0;
    stack = nullptr;
    stack_tail = nullptr;
    trees = nullptr;
    trees_tail = nullptr;
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    while (countEdges < numEdges)
    {
      do
      {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);
      bool edge_already_present = false; // Variable to check if edge was already present
      if (nodes[n1].adjacent == nullptr) // If adjacency list was empty, initializes and adds the edge
      {
        listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[n2]);
        nodes[n1].adjacent = new_node;
      }
      else
      {
        listOfObjects<Node *> *ptr = nodes[n1].adjacent;
        while (ptr->next != nullptr) // Traverses through the adjacency list to check if edge was already present
        {
          if (ptr->object == &nodes[n2])
          {
            edge_already_present = true; // If edge present turns this to true
            break;
          }
          ptr = ptr->next;
        }
        if (ptr->object == &nodes[n2])
        {
          edge_already_present = true; // If edge present turns this to true
        }
        if (edge_already_present) // If edge present moves on to next iteration
        {
          continue;
        }
        else // If edge not present, adds the edge
        {
          listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[n2]);
          ptr->next = new_node;
          ptr->next->prev = ptr;
        }
      }
      if (nodes[n2].adjacent == nullptr)
      {
        listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[n1]);
        nodes[n2].adjacent = new_node;
      }
      else
      {
        listOfObjects<Node *> *ptr = nodes[n2].adjacent;
        while (ptr->next != nullptr) // Traverses through the adjacency list to check if edge was already present
        {
          if (ptr->object == &nodes[n1])
          {
            edge_already_present = true; // If edge present turns this to true
            break;
          }
          ptr = ptr->next;
        }
        if (ptr->object == &nodes[n1])
        {
          edge_already_present = true; // If edge present turns this to true
        }
        if (edge_already_present) // If edge present moves on to next iteration
        {
          continue;
        }
        else // If edge not present, adds the edge
        {
          listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[n1]);
          ptr->next = new_node;
          ptr->next->prev = ptr;
        }
      }

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
    }

    // Add appropriate code as necessary for your implementation
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void DFS(int component, BST *tree, int time); // The function which recursively calls itself to do DFS
  void modifiedDFS();
  void printResults();
  Node *stack_pop();           // Pops the topmost element from the stack and returns it
  void stack_push(Node *node); // Pushes the new  element to the top of the stack
  Node *stack_top();           // Returns the pointer to the topmost element
};

#endif

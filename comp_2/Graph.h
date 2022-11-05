#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

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

// The class to represent the a node in the graph
class Node
{
public:
  int value;                        // The value in the node
  listOfObjects<Node *> *out_edges; // Out going edges
  listOfObjects<Node *> *in_edges;  // Incoming edges
  listOfObjects<Node *> *similar;   // Nodes that are similar
  listOfObjects<Node *> *similar_tail;
  Node *parent;
  Node *max_similar; // Similar node with the maximum value

  Node()
  {
    parent = nullptr;
    in_edges = nullptr;
    out_edges = nullptr;
    similar = nullptr;
    similar_tail = nullptr;
    max_similar = nullptr;
  }
};

// The main graph class
class Graph
{
  int numNodes; // Number of nodes
  int numEdges; // Number of edges
  fstream graphFile;

  Node *nodes;

public:
  Graph()
  {
    cin >> numNodes;

    nodes = new Node[numNodes];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
      nodes[i].max_similar = &nodes[i];
    }

    // Adds all the edges
    int n1, n2;
    while (!(n1 == -2 && n2 == -2))
    {
      cin >> n1;
      cin >> n2;
      n1--;
      n2--;
      bool edge_already_present = false;  // Variable to check if edge was already present
      if (nodes[n1].out_edges == nullptr) // If adjacency list was empty, initializes and adds the edge
      {
        listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[n2]);
        nodes[n1].out_edges = new_node;
      }
      else
      {
        listOfObjects<Node *> *ptr = nodes[n1].out_edges;
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
      if (nodes[n2].in_edges == nullptr)
      {
        listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[n1]);
        nodes[n2].in_edges = new_node;
      }
      else
      {
        listOfObjects<Node *> *ptr = nodes[n2].in_edges;
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
      numEdges++;
    }

    // Adds the similar nodes defined by the user
    n1 = 0;
    n2 = 0;
    while (!(n1 == -2 && n2 == -2))
    {
      cin >> n1;
      cin >> n2;
      n1--;
      n2--;
      bool similarity_already_present = false; // Variable to check if similarity was already present
      if (nodes[n1].similar == nullptr)        // If adjacency list was empty, initializes and adds the similarity
      {
        listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[n2]);
        nodes[n1].similar = new_node;
      }
      else
      {
        listOfObjects<Node *> *ptr = nodes[n1].similar;
        while (ptr->next != nullptr) // Traverses through the adjacency list to check if similarity was already present
        {
          if (ptr->object == &nodes[n2])
          {
            similarity_already_present = true; // If similarity present turns this to true
            break;
          }
          ptr = ptr->next;
        }
        if (ptr->object == &nodes[n2])
        {
          similarity_already_present = true; // If similarity present turns this to true
        }
        if (similarity_already_present) // If similarity present moves on to next iteration
        {
          continue;
        }
        else // If similarity not present, adds the similarity
        {
          listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[n2]);
          ptr->next = new_node;
          ptr->next->prev = ptr;
        }
      }
    }
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
  }

  void max_similar();
  void print_source_nodes(string outfile_name);    // Function to print the source nodes
  void print_similar_nodes(string outfile_name);   // Function to print the similar pair of nodes
  void print_collapsed_graph(string outfile_name); // Function to print the collapsed graph
};

#endif

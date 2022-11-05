#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#include <fstream>

using namespace std;

bool is_similar(Node *node1, Node *node2);              // Checks for similarity and updates the similar list
int count(listOfObjects<Node *> *nodes);                // Returns length of the list
bool present(Node *node, listOfObjects<Node *> *nodes); // Checks if node is present in the list nodes

// Finds the similar transitive node with maximum value
void Graph::max_similar()
{
  int changes = 1;
  while (changes != 0)
  {
    changes = 0;
    for (int i = 0; i < numNodes; i++)
    {
      for (int j = 0; j < numNodes; j++)
      {
        if (is_similar(&nodes[i], &nodes[j]))
        {
          if (nodes[i].max_similar->value > nodes[j].max_similar->value)
          {
            nodes[j].max_similar = nodes[i].max_similar;
            changes++;
          }
          else if (nodes[i].max_similar->value < nodes[j].max_similar->value)
          {
            nodes[i].max_similar = nodes[j].max_similar;
            changes++;
          }
        }
      }
    }
  }
}

// Returns length of the list
int count(listOfObjects<Node *> *nodes)
{
  int count = 0;
  listOfObjects<Node *> *ptr = nodes;
  while (ptr != nullptr)
  {
    count++;
    ptr = ptr->next;
  }
  return count;
}
// Recursively checks for similarity and updates the similar list
bool is_similar(Node *node1, Node *node2)
{
  if (node1->similar != nullptr)
  {
    listOfObjects<Node *> *ptr = node1->similar;
    while (ptr != nullptr)
    {
      if (ptr->object->value == node2->value)
      {
        return true;
      }
      ptr = ptr->next;
    }
  }
  if (node1->in_edges != nullptr && node1->in_edges->next == nullptr)
  {
    if (node1->in_edges->object->value == node2->value)
    {
      return true;
    }
  }
  if (node1->in_edges != nullptr && node2->in_edges != nullptr)
  {
    if (count(node1->in_edges) != count(node2->in_edges))
    {
      return false;
    }
    listOfObjects<Node *> *ptr = node1->in_edges;
    while (ptr != nullptr)
    {
      listOfObjects<Node *> *ptr1 = node2->in_edges;
      {
        bool similar_found = false;
        while (ptr1 != nullptr)
        {
          if (is_similar(ptr->object, ptr1->object))
          {
            similar_found = true;
            break;
          }
          ptr1 = ptr1->next;
        }
        if (!similar_found)
        {
          return false;
        }
      }
      ptr = ptr->next;
    }
    listOfObjects<Node *> *ptr2 = node2->in_edges;
    while (ptr2 != nullptr)
    {
      listOfObjects<Node *> *ptr3 = node1->in_edges;
      {
        bool similar_found = false;
        while (ptr3 != nullptr)
        {
          if (is_similar(ptr2->object, ptr3->object))
          {
            similar_found = true;
            break;
          }
          ptr3 = ptr3->next;
        }
        if (!similar_found)
        {
          return false;
        }
      }
      ptr2 = ptr2->next;
    }
    return true;
  }
  return false;
}

// Checks if node is present in the list nodes
bool present(Node *node, listOfObjects<Node *> *nodes)
{
  if (nodes == nullptr)
  {
    return false;
  }
  listOfObjects<Node *> *ptr = nodes;
  while (ptr != nullptr)
  {
    if (ptr->object->value == node->value)
    {
      return true;
    }
    ptr = ptr->next;
  }
  return false;
}

// Prints the source nodes
void Graph::print_source_nodes(string outfile_name)
{
  ofstream outfile;
  outfile.open(outfile_name, std::ios_base::app);
  outfile << "Source Nodes: ";
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].in_edges == nullptr) // If no incoming edges then it is source node
    {
      outfile << nodes[i].value << " ";
    }
  }
}

// To print the pairs of similar nodes
void Graph::print_similar_nodes(string outfile_name)
{
  ofstream outfile;
  outfile.open(outfile_name, std::ios_base::app);
  int changes = 1;
  while (changes != 0)
  {
    changes = 0;
    for (int i = 0; i < numNodes; i++)
    {
      for (int j = 0; j < numNodes; j++)
      {
        if (is_similar(&nodes[i], &nodes[j]) && (!present(&nodes[j], nodes[i].similar))) // Adds the non-source nodes to the similar list
        {
          if (nodes[i].similar == nullptr)
          {
            listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[j]);
            nodes[i].similar = new_node;
            nodes[i].similar_tail = new_node;
            changes++;
          }
          else
          {
            listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[j]);
            nodes[i].similar_tail->next = new_node;
            new_node->prev = nodes[i].similar_tail;
            nodes[i].similar_tail = nodes[i].similar_tail->next;
            changes++;
          }
        }
      }
    }
  }
  outfile << "Similar node pairs: ";
  for (int i = 0; i < numNodes; i++)
  {
    listOfObjects<Node *> *ptr = nodes[i].similar;
    while (ptr != nullptr)
    {
      outfile << "(" << nodes[i].value << ", " << ptr->object->value << ")"
              << " ";
      ptr = ptr->next;
    }
  }
  outfile << endl;
}

// To print the collapsed graph
void Graph::print_collapsed_graph(string outfile_name)
{
  ofstream outfile;
  outfile.open(outfile_name, std::ios_base::app);
  listOfObjects<Node *> *collapsed_nodes = nullptr; // List to store the final collapsed nodes
  listOfObjects<Node *> *collapsed_nodes_tail = nullptr;
  int num_collapsed_nodes = 0;
  max_similar();
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].similar == nullptr)
    {
      if (!present(nodes[i].max_similar, collapsed_nodes))
      {
        if (collapsed_nodes == nullptr)
        {
          listOfObjects<Node *> *new_node = new listOfObjects<Node *>(&nodes[i]);
          collapsed_nodes = new_node;
          collapsed_nodes_tail = new_node;
          num_collapsed_nodes++;
        }
        else
        {
          collapsed_nodes_tail->next = new listOfObjects<Node *>(&nodes[i]);
          collapsed_nodes_tail->next->prev = collapsed_nodes_tail;
          collapsed_nodes_tail = collapsed_nodes_tail->next;
          num_collapsed_nodes++;
        }
      }
    }
    else
    {
      if (!present(nodes[i].max_similar, collapsed_nodes))
      {
        if (collapsed_nodes == nullptr)
        {
          listOfObjects<Node *> *new_node = new listOfObjects<Node *>(nodes[i].max_similar);
          collapsed_nodes = new_node;
          collapsed_nodes_tail = new_node;
          num_collapsed_nodes++;
        }
        else
        {
          collapsed_nodes_tail->next = new listOfObjects<Node *>(nodes[i].max_similar);
          collapsed_nodes_tail->next->prev = collapsed_nodes_tail;
          collapsed_nodes_tail = collapsed_nodes_tail->next;
          num_collapsed_nodes++;
        }
      }
    }
  }
  // Print the collapsed nodes
  listOfObjects<Node *> *ptr = collapsed_nodes;
  outfile << "Collapsed graph:" << endl
          << endl;
  outfile << num_collapsed_nodes << ": ";
  while (ptr != nullptr)
  {
    outfile << ptr->object->value << " ";
    ptr = ptr->next;
  }
  outfile << endl;
  Node *new_graph_nodes = new Node[num_collapsed_nodes]; // New array to store the final collapsed nodes of the new graph
  ptr = collapsed_nodes;
  for (int i = 0; i < num_collapsed_nodes; i++)
  {
    new_graph_nodes[i].value = ptr->object->max_similar->value;
    new_graph_nodes[i].max_similar = &new_graph_nodes[i];
    ptr = ptr->next;
  }
  for (int i = 0; i < numNodes; i++)
  {
    listOfObjects<Node *> *ptr = nodes[i].out_edges;
    // Adding edges to the collapsed graph
    while (ptr != nullptr)
    {
      if (nodes[i].max_similar->value != ptr->object->max_similar->value)
      {
        int a;
        for (int j = 0; j < num_collapsed_nodes; j++)
        {
          if (new_graph_nodes[j].value == nodes[i].max_similar->value)
          {
            a = j;
            break;
          }
        }
        if (!present(ptr->object->max_similar, new_graph_nodes[a].out_edges))
        {
          if (new_graph_nodes[a].out_edges == nullptr)
          {
            listOfObjects<Node *> *new_node = new listOfObjects<Node *>(ptr->object->max_similar);
            new_graph_nodes[a].out_edges = new_node;
          }
          else
          {
            listOfObjects<Node *> *new_node = new listOfObjects<Node *>(ptr->object->max_similar);
            listOfObjects<Node *> *ptr1 = new_graph_nodes[a].out_edges;
            while (ptr1->next != nullptr)
            {
              ptr1 = ptr1->next;
            }
            ptr1->next = new_node;
          }
        }
      }
      ptr = ptr->next;
    }
  }
  // Printing the collapsed graph edges
  for (int i = 0; i < num_collapsed_nodes; i++)
  {
    listOfObjects<Node *> *ptr = new_graph_nodes[i].out_edges;
    while (ptr != nullptr)
    {
      outfile << new_graph_nodes[i].value << " " << ptr->object->value << endl;
      ptr = ptr->next;
    }
  }
}

#endif
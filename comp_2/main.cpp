#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main()
{
  Graph *myGraph; // The graph
  myGraph = new Graph();
  if (myGraph == nullptr)
  {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }
  string outfile_name = "outGraph.txt";
  ofstream outfile;
  outfile.open(outfile_name, std::ios::out | ios::trunc);
  outfile.close();
  outfile.open(outfile_name, std::ios_base::app);
  myGraph->print_source_nodes(outfile_name); // Prints the source nodes
  outfile << endl
          << endl;
  myGraph->print_similar_nodes(outfile_name); // Prints the pair of similar nodes
  outfile << endl;
  myGraph->print_collapsed_graph(outfile_name); // Prints the collapsed graph
  return 0;
}

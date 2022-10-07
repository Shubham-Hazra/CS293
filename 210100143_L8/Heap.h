#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T>
class TreeNode
{
public:
  T object;
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

  TreeNode(T initObj)
  {
    object = initObj;
    left = right = parent = nullptr;
  }
  ~TreeNode() { ; }
};

template <typename T>
class Heap
{
public:
  TreeNode<T> *root;
  int num_elements;

public:
  Heap()
  {
    root = nullptr;
    num_elements = 0;
  }
  ~Heap();
  void free(TreeNode<T> *node);
  void insert(T obj);
  void Heapify(TreeNode<T> *root);
  T delMax();
  T getMax() { return root->object; }
  void printHeap(TreeNode<T> *node);
  void swap(TreeNode<T> *child, TreeNode<T> *parent);
  TreeNode<T> *getroot();
  void displayAboveThresh(T thresh);
};

#endif

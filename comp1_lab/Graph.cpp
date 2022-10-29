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
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].component_num == 0)
    {
      if (trees == nullptr)
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
      connected_components = component;
      DFS(&nodes[i], &nodes[i], component, trees_tail->object);
      component++;
    }
  }
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visited == 1)
    {
      visited_once++;
    }
    else if (nodes[i].visited == 2)
    {
      visited_twice++;
    }
    if (nodes[i].incycle)
    {
      nodes_incycle++;
    }
  }
}

void Graph::DFS(Node *root, Node *node, int component, BST *tree)
{
  listOfObjects<Node *> *ptr = node->adjacent;
  node->visited++;
  node->component_num = component;
  tree->insert(node->value);
  while (ptr != nullptr)
  {
    if (ptr->object->visited == 0)
    {
      ptr->object->parent = node;
      DFS(root, (ptr->object), component, tree);
    }
    else if (ptr->object->visited == 1 && node->parent != ptr->object)
    {
      // ptr->object->incycle = true;
      // Node *ptr1 = node;
      // while (ptr1 != ptr->object && ptr1 != nullptr)
      // {
      //   ptr1->incycle = true;
      //   ptr1 = ptr1->parent;
      // }
      DFS(root, (ptr->object), component, tree);
    }
    ptr = ptr->next;
  }
}

void Graph::printResults()
{
  cout << "No.of connected components : " << connected_components << endl;
  cout << "No.of nodes visited once : " << visited_once << endl;
  cout << "No.of nodes visited twice : " << visited_twice << endl;
  cout << "No.of nodes that are present in a cycle : " << nodes_incycle << endl;
  listOfObjects<BST *> *ptr = trees;
  while (ptr != nullptr)
  {
    ptr->object->printBST("", false);
    cout << endl;
    ptr = ptr->next;
  }
  return;
}

BST::BST()
{
  root = new TreeNode();
  root->parent = NULL;
}

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

void BST::getBST(const string &prefix, bool isLeft = false)
{
  if (root != nullptr)
  {
    result.push_back(prefix);

    result.push_back(isLeft ? "|--" : "|__");

    // print the value of the node
    result.push_back(to_string(root->value) + "\n");
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    getBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    getBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

void BST::clearResult()
{
  result.clear();
}

vector<string> BST::getResult()
{
  return result;
}

#endif

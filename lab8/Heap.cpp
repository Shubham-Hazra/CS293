#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

// Returns the pointer to the root
template <typename T>
TreeNode<T> *Heap<T>::getroot()
{
	return root;
}

// Destructor for the heap
// Deletes all nodes
template <typename T>
Heap<T>::~Heap()
{
	free(root);
}

// Recuursive function to delete all nodes below given node
template <typename T>
void Heap<T>::free(TreeNode<T> *node)
{
	if (node->left != NULL)
	{
		free(node->left);
	}
	if (node->right != NULL)
	{
		free(node->right);
	}
	delete node;
}

// Function to insert into the heap
template <typename T>
void Heap<T>::insert(T obj)
{
	// insert your code here
	if (root == NULL)
	{
		TreeNode<T> *node = new TreeNode<T>(obj);
		root = node;
		num_elements++;
		return;
	}
	TreeNode<T> *ptr = root;
	TreeNode<T> *node = new TreeNode<T>(obj);
	if (num_elements == 1)
	{
		root->left = node;
		node->parent = root;
		num_elements++;
		if (root->object < node->object)
		{
			swap(node, ptr);
		}
		return;
	}
	if (num_elements == 2)
	{
		root->right = node;
		node->parent = root;
		num_elements++;
		if (root->object < node->object)
		{
			swap(node, ptr);
		}
		return;
	}
	int steps = (num_elements + 1) / 2;
	while (steps / 2 != 0)
	{
		int t = steps % 2;
		if (t == 1)
		{
			ptr = ptr->right;
		}
		else
		{
			ptr = ptr->left;
		}
		steps /= 2;
	}
	if (ptr->left == NULL)
	{
		ptr->left = node;
		node->parent = ptr;
		num_elements++;
	}
	else
	{
		ptr->right = node;
		node->parent = ptr;
		num_elements++;
	}
	while (ptr != NULL)
	{
		if ((ptr->object) < (node->object))
		{
			swap(node, ptr);
			ptr = ptr->parent;
			node = node->parent;
		}
		else
		{
			break;
		}
	}

	return;
}

// Function to delete the maximum element and return it
template <typename T>
T Heap<T>::delMax()
{
	if (num_elements == 0)
	{
		T *temp = new T[1];
		cout << "NO MORE ELEMENTS IN THE HEAP.PRINTING GARBAGE VALUE" << endl;
		return (*temp);
	}
	if (num_elements == 1)
	{
		T temp = root->object;
		root = NULL;
		num_elements--;
		return temp;
	}
	if (num_elements == 2)
	{
		T temp = root->object;
		root->left->parent = NULL;
		root = root->left;
		num_elements--;
		return temp;
	}
	if (num_elements == 3)
	{
		T temp = root->object;
		swap(root->right, root);
		root->right = NULL;
		num_elements--;
		Heapify(root);
		return temp;
	}
	TreeNode<T> *ptr = root;
	int steps = num_elements / 2;
	while (steps / 2 != 0)
	{
		int t = steps % 2;
		if (t == 1)
		{
			ptr = ptr->right;
		}
		else
		{
			ptr = ptr->left;
		}
		steps /= 2;
	}
	if (ptr->right == NULL)
	{
		T temp = root->object;
		swap(ptr->left, root);
		ptr->left = NULL;
		num_elements--;
		Heapify(root);
		return temp;
	}
	else
	{
		T temp = root->object;
		swap(ptr->right, root);
		ptr->right = NULL;
		num_elements--;
		Heapify(root);
		return temp;
	}
}

// Function to implement heapify
// i.e. the left branch of root and right branch of root both are heaps, then adjust root to make it a complete heap
template <typename T>
void Heap<T>::Heapify(TreeNode<T> *root)
{
	TreeNode<T> *ptr = root;
	if (ptr->left == NULL && ptr->right == NULL)
	{
		return;
	}
	else if (ptr->left == NULL || ptr->right == NULL)
	{
		if (ptr->left == NULL)
		{
			if (ptr->object < ptr->right->object)
			{
				swap(ptr->right, ptr);
			}
			return;
		}
		else
		{
			if (ptr->object < ptr->left->object)
			{
				swap(ptr->left, ptr);
			}
			return;
		}
	}
	else
	{
		if (ptr->left->object < ptr->object)
		{
			if (ptr->right->object < ptr->object)
			{
				return;
			}
			else
			{
				swap(ptr->right, ptr);
				Heapify(ptr->right);
			}
		}
		else
		{
			if (ptr->left->object < ptr->right->object)
			{
				swap(ptr->right, ptr);
				Heapify(ptr->right);
			}
			else
			{
				swap(ptr->left, ptr);
				Heapify(ptr->left);
			}
		}
	}
}

// Function to print the heap
template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
	// static bool isleft = true;
	// static string prefix = "";
	// string temp = "";
	// T *arr = new T[num_elements];
	// int num = num_elements;
	// for (int i = 0; i < num; i++)
	// {
	// 	arr[i] = delMax();
	// 	cout << arr[i] << " ";
	// }
	// cout << endl;
	// for (int i = 0; i < num; i++)
	// {
	// 	insert(arr[i]);
	// }
	// if (node != NULL)
	// {
	// 	cout << prefix;
	// 	if (node == root)
	// 	{
	// 		cout << node->object << endl;
	// 		isleft = true;
	// 		printHeap(node->left);
	// 		prefix = "";
	// 		isleft = false;
	// 		printHeap(node->right);
	// 	}
	// 	else
	// 	{
	// 		if (isleft)
	// 		{
	// 			cout << "|--" << node->object << endl;
	// 			isleft = true;
	// 			prefix = prefix + "│   ";
	// 			temp = prefix;
	// 			printHeap(node->left);
	// 			isleft = false;
	// 			prefix = temp;
	// 			printHeap(node->right);
	// 		}
	// 		else
	// 		{
	// 			cout << "|__" << node->object << endl;
	// 			temp = prefix;
	// 			isleft = true;
	// 			prefix = prefix + "│   ";
	// 			printHeap(node->left);
	// 			prefix = temp + "    ";
	// 			isleft = false;
	// 			printHeap(node->right);
	// 		}	// static bool isleft = true;
	// static string prefix = "";
	// string temp = "";
	// 	}
	// }
	printHeap(node, "", false);
}
template <typename T>
void Heap<T>::printHeap(TreeNode<T> *root, const string &prefix, bool isLeft)
{
	if (root != nullptr)
	{
		cout << prefix;

		cout << (isLeft ? "|--" : "|__");

		// print the value of the node
		cout << root->object << endl;
		TreeNode<T> *curr = root;
		root = root->left;
		// enter the next tree level - left and right branch
		printHeap(root, prefix + (isLeft ? "│   " : "    "), true);
		root = curr->right;
		printHeap(root, prefix + (isLeft ? "│   " : "    "), false);
		root = curr;
	}
}

// template <typename T>
// void Heap<T>::displayAboveThresh(T thresh)
// {
// 	if (getMax() < thresh)
// 	{
// 		return;
// 	}
// 	T *arr = new T[num_elements];
// 	int num = num_elements;
// 	for (int i = 0; i < num; i++)
// 	{
// 		arr[i] = delMax();
// 		if (arr[i] < thresh)
// 		{
// 			break;
// 		}
// 		cout << arr[i] << " ";
// 	}
// 	cout << endl;
// }

// Function to swap the values in two pointers
template <typename T>
void Heap<T>::swap(TreeNode<T> *child, TreeNode<T> *parent)
{
	if (parent == NULL || child == NULL)
	{
		return;
	}
	T temp = child->object;
	child->object = parent->object;
	parent->object = temp;

	return;
}
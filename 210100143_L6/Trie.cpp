#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif

using namespace std;

Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

Trie::~Trie() {
  recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node) {
  if (node == nullptr) {
    return;
  }
  else {
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      recursiveDelete(currNode);
      node->branch[i] = nullptr;
    }
    if (node != root) {
      delete node;
    }
    return;
  }
}


// Insert function to insert words in a station name into the trie
// Takes in the word and the index of the string in the dictionary as arguments
// Traverses through the word letter by letter using their correseponding positions in the english alphabet(from 1 to 26)
// Finds the correct position of the word in the trie and then change isWord to be true
// Add the indexOfName to the indices linked list
// Returns true for successful insertion
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  for(int i=0;i<len;i++)
  {
    int val = ('a' <= wordInName[i])?(int(wordInName[i])-97):(int(wordInName[i])-65);
    if(currNode->branch[val]==NULL)
    {
      TrieNode* new_node = new TrieNode();
      currNode->branch[val] = new_node;
      currNode->numNonNullBranches++;
      currNode = currNode->branch[val];
    }
    else
    {
      currNode = currNode->branch[val];
    }
  }
  currNode->isWord = true;
  listOfObjects<int>* new_index = new listOfObjects<int>(indexOfName);
  listOfObjects<int>* ptr = currNode->indices;
  if(ptr == NULL)
  {
    currNode->indices = new_index;
    return true;   
  }
  while(ptr->next != NULL)
  {
    ptr = ptr->next;
  }
  ptr->next = new_index;

  return true;                        ;
}


// Delete function used to delete station names from the trie
// Takes in the word to be deleted and the full name of station
// Finds the node at which the last letter is stored 
// Sets isWord to false and removes the index of the word from the indices list appropriately
// Also cuts of a branch of the word appropriately
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = ('a' <= wordInName[0])?(int(wordInName[0])-97):(int(wordInName[0])-65);
  int len = wordInName.length();
  for(int i=0;i<len;i++ && currNode != NULL)
  {
    int val = ('a' <= wordInName[i])?(int(wordInName[i])-97):(int(wordInName[i])-65);
    currNode = currNode->branch[val];
  }
  if(currNode->isWord==false)
  {
    return false;
  }
  int index;
  int index_count = 0;
  listOfObjects<int>* index_ptr = currNode->indices;
  while(index_ptr != NULL)
  {
    if(nameDict->getKeyAtIndex(index_ptr->object)==name)
    {
      index = index_ptr->object;
    }
    index_count++;
    index_ptr = index_ptr->next;
  }
  if(index_count==1)
  {
    currNode->indices = NULL;
    int count = 0;
    for(int i=0;i<NUM_CHARS;i++)
    {
      if(currNode->branch[i] != NULL)
      {
        count++;
      }
    }
    if(count>0)
    {
      currNode->isWord = false;
    }
    else
    {
      TrieNode *curr_node = root;
      int wordcount;
      for(int i=0;i<len;i++)
      {
        int val = ('a' <= wordInName[i])?(int(wordInName[i])-97):(int(wordInName[i])-65);
        int count = 0;
        for(int i=0;i<NUM_CHARS;i++)
        {
          if(curr_node->branch[i] != NULL)
          {
            count++;
          }
        }
        if(count == 1)
        {
          if(curr_node->isWord == true)
          {
            lastBranchNode = curr_node;
            lastBranchChar = val;
          }
        }
        else
        {
          lastBranchNode = curr_node;
          lastBranchChar = val;
        }
        curr_node = curr_node->branch[val];
      }
      if(wordcount>1)
      {
        lastBranchNode->branch[lastBranchChar] = NULL;
      }
      else
      {
        lastBranchNode->branch[lastBranchChar] = NULL;
      }
    }
  }
  else
  {
    listOfObjects<int>* index_ptr = currNode->indices;
    if(index_ptr->object == index)
    {
      currNode->indices = currNode->indices->next;
    }
    else
    {
      while(index_ptr->next->next != NULL)
      {
        if(index_ptr->next->object == index)
        {
          break;
        }
        index_ptr = index_ptr->next;
      }
      index_ptr->next = index_ptr->next->next;
    }
  }

  return true;
}

// Searches for station names with the given prefix as prefix 
// Adds all the matches to the currCompletions linked list
// Returns currCompletions
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = NULL;
  for(int i=0;i<len;i++)
  {
    if(currNode == NULL)
    {
      break;
    }
    int val = ('a' <=prefix[i])?(int(prefix[i])-97):(int(prefix[i])-65);
    currNode = currNode->branch[val];
  }
  if(currNode == NULL)
  {
    return NULL;
  }
  currCompletions = recursiveAddCompletions(currNode,currCompletions);
  return currCompletions;
  
}


// Adds all the children of given node to the currCompletions linked list
// Returns currCompletions
listOfObjects<string> * Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if(node->isWord == true)
  {
    currCompletions = addCompletions(node,currCompletions);
  }

  for(int i=0; i<NUM_CHARS;i++)
  {
    if(node->branch[i] != NULL)
    {
      currCompletions = recursiveAddCompletions(node->branch[i],currCompletions);
    }
    else
    {
      continue;
    }
  }

  return currCompletions;

}

// Finds the exact matches of the given word
// Adds the matches to the linked list and returns it
listOfObjects<string> * Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  if(node->isWord == false)
  {
    return currCompletions;
  }
  else
  {
    listOfObjects<int>* index_ptr = node->indices;
    if(currCompletions == NULL)
    {
      listOfObjects<string>* new_string = new listOfObjects<string>(nameDict->getKeyAtIndex(index_ptr->object));
      currCompletions = new_string;
      index_ptr = index_ptr->next;
    }
    listOfObjects<string>* comp_ptr = currCompletions;
    while(comp_ptr->next != NULL)
    {
      comp_ptr = comp_ptr->next;
    }
    while(index_ptr != NULL)
    {
      listOfObjects<string>* new_string = new listOfObjects<string>(nameDict->getKeyAtIndex(index_ptr->object));
      comp_ptr->next = new_string;
      index_ptr = index_ptr->next;
      comp_ptr = comp_ptr->next;
    }

      return currCompletions;
  }
  


}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name) {
  listOfObjects<string> *currCompletion = completions;
  bool isPresent = false;
  while (currCompletion != nullptr) {
    if (currCompletion->object == name) {
      isPresent = true;
      break;
    }
    currCompletion = currCompletion->next;
  }
  return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

bool Trie::isPresent(string wordInName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    currNode = currNode->branch[letter];
  }

  return currNode->isWord;
  
}

// Edit version 1: Added printTrie and recursivePrintTrie functions
// to help in debugging

void Trie::printTrie()
{
  recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight)
{
  if (node != nullptr) {
    cout << prefix;
    
    cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');
    
    // If this trie node has isWord set to true, print "(isWord)" and
    // also the list of complete station names (accessed through indices
    // in nameDict) associated with this trie node.
    if (node->isWord) {
      cout << "(isWord)";
      listOfObjects<int> *currIndices = node->indices;
      while (currIndices != nullptr) {
	cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
	currIndices = currIndices->next;
      }
    }
    else {
      cout << "()";
    }
    cout << endl;
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      bool childrenToRight = false;
      for (int j = i+1; j < NUM_CHARS; j++) {
	if (node->branch[j] != nullptr) {
	  childrenToRight = true;
	  break;
	}
      }
      if (currNode != nullptr) {
	recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1

#endif

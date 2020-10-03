#pragma once
#include <algorithm>
#include <cctype>
#include <string>

namespace utstl {

struct TrieNode {
  bool isEndWord;
  constexpr static int ALPHABET_SIZE = 26;
  TrieNode *children[ALPHABET_SIZE];

  TrieNode() : isEndWord(false) {
    for (int i = 0; i < ALPHABET_SIZE; ++i)
      children[i] = nullptr;
  }

  void markAsLeaf() { isEndWord = true; }

  void unMarkAsLeaf() { isEndWord = false; }
};

class Trie {
  TrieNode *root;

private:
  int getIndex(char t) const { return t - 'a'; }

  // cleanup takes in a node and delete it along with all
  // of its child nodes
  void cleanup(TrieNode *node) {
    if (!node)
      return;

    for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
      cleanup(node->children[i]);
    }

    delete node;
  }

  // hasChildren returns true if the given node has one or more
  // non null child pointers
  bool hasChildren(TrieNode *node) const {
    if (!node)
      return false;

    for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
      if (node->children[i] != nullptr)
        return true;
    }

    return false;
  }

  bool remove(TrieNode *node, std::string key, int level) {
    if (!root)
      return false;

    // This is the base case, that is when we have reached the end
    if (level == key.length()) {
      // If the current node does not have any child nodes
      // then simply delete that node
      if (!hasChildren(node)) {
        delete node;
        return true;
      }

      // If it does have a child node then do not delete the node
      // just unmark that node has the end of the word
      node->unMarkAsLeaf();
      return false;
    }

    // Get index of the key
    auto idx = getIndex(key[level]);

    // Check if the given index is valid or not
    TrieNode *newNode = node->children[idx];
    // If newNode is a null pointer then do nothing and
    // return false as the word doesn't exist in the structure
    if (!newNode)
      return false;

    auto deleted = remove(newNode, key, level + 1);

    // If deleted then remove that node as a child
    if (deleted)
      node->children[idx] = nullptr;

    // If the current node now is useless then remove it
    if (!hasChildren(node)) {
      delete node;
      return true;
    }

    return false;
  }

public:
  Trie() : root(new TrieNode()) {}

  // insert inserts the given string to the trie
  void insert(std::string key) {
    if (key.empty())
      return;

    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    TrieNode *currentNode = root;
    int idx = 0;

    for (int level = 0; level < key.length(); ++level) {
      idx = getIndex(key[level]);

      if (currentNode->children[idx] == nullptr) {
        currentNode->children[idx] = new TrieNode();
      }

      currentNode = currentNode->children[idx];
    }

    currentNode->markAsLeaf();
  }

  // search returns true if the word exists in the trie and false if it doesn't
  bool search(std::string key) const {
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    TrieNode *currentNode = root;

    for (int i = 0; i < key.length(); ++i) {
      int idx = getIndex(key[i]);

      // Check if the currentNode has the given character
      if (currentNode->children[idx] == nullptr)
        return false;

      // Move ahead
      currentNode = currentNode->children[idx];
    }

    return currentNode && currentNode->isEndWord;
  }

  void remove(std::string key) { remove(root, key, 0); }

  ~Trie() { cleanup(root); }
};
} // namespace utstl
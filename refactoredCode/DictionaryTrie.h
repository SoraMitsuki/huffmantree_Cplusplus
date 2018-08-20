/**
  * Partner1:
  * Name: Jiaqi Fan
  * PID: A12584051
  * Partner2:
  * Name: Xuanru Zhu
  * PID: A91064234
  * Date: 1/26/2017
  * PA2
  */

/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H
#define nChild 27

#include <vector>
#include <string>
#include <stack>

/**
 * The class for the Node of the mulit-way trie
 */
class Node{
public:
  bool word = false;
  std::string str;
  unsigned int freq = 0;
  Node* children[nChild];
  Node();
};
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:
  
  Node* root; // the root of the trie

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();
 
  /* Helper method for getting the ferq for test */
  int getFreq(std::string word) const;

private:
  // Add your own data members and methods here

  /* Helper method for auto completion */
  void autoComplete(std::vector<Node*>& nodes,
                  std::vector<std::string>& words, unsigned int maxNumFreq);

  /* Helper method for exhaustive search algorithm*/
  void eSearch(std::stack<Node*>& search, std::vector<Node*>& nodes);

  /* Helper method for the destructor */
  void deleteAll(Node* node, int index);
};

#endif // DICTIONARY_TRIE_H

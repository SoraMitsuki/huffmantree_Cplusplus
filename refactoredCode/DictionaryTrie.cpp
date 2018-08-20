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
// this file holdes all the function for Trie, insert and find
// constructor and dectructor detail described in DictionaryTrie.h file
//
#include "util.h"
#include "DictionaryTrie.h"
#include <stack>
/* Constructor of the Node */
Node::Node(){
  // create total of 27 elements because we have to handle "space"
  int total = 27;
  for(int i = 0; i < total; i++){
    children[i] = NULL;
  }
}
/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
  root = new Node(); //constructore to create a new trie
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  // handle the magic number 
  int space = 26;
  int a = 97;
  int z = 122;
  //check the param is null or not
  if(word == ""){
    return false;
  }//end check if
  Node* node = root; // set the first to root
  for(int i = 0; word[i] != '\0'; i++){
    if(word[i] == ' '){
      if(node->children[space] == NULL){
        node->children[space] = new Node();
      }//end internal if
      node = node->children[space] = new Node();
    }//end first if
    else if(word[i] >= a && word[i] <= z){
      if(node->children[word[i] - 'a'] == NULL){
        //create word symbol spot
        node->children[word[i] - 'a'] = new Node();
      }
      node = node->children[word[i] - 'a'];
    }//end else if
    else{
      std::cout << "invalid input" << std::endl;
      return false;
    }//end else
  }
  //if the frep greater than the node frep
  if(node->word == true){
    if(freq > node->freq){
      //set the new frep
      node->freq = freq;
    }//end internal if
    return false;
  }//end 3rd if
  else{
    node->word = true;
    node->freq = freq;
    node->str = word;
    return true;
  }//end 3rd else
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  //handle magic number 
  int space = 26;
  //check for the param is empty or not
  if(word == ""){
    return false;
  }
  //processd to find return true when find otherwise false
  Node* node = root;
  for(int i = 0; word[i] != '\0'; i++){
    if(word[i] == ' '){
      if(node->children[space] == NULL){
        return false;
      }//end internal if
      else{
        node = node ->children[space];
      }//end internal else
    }//end if
    else{ 
      if(node->children[word[i] - 'a'] == NULL){
      return false;
      }//end internal if 2
      else{
        node = node->children[word[i] - 'a'];
      }//end internal else 2
    }//end else if
  }
  if(node->word){
    return true;
  }//end 2nd if
  else{
    return false;
  }//end 2nd else
}

/* Helper mehtod for get freq for testing
 */
int DictionaryTrie::getFreq(std::string word) const
{
  int space = 26;
  if(word == ""){
    return 0;
  }
  //find the word
  if(find(word)){
    Node* node = root;
    //loop through the word to the last node and get the freq
    for(int i = 0; word[i] != '\0'; i++){
      if(word[i] == ' '){
        node = node->children[space];
      }
      else{
        node = node->children[word[i] - 'a'];
      }
    }
    return node->freq;
  }
  else{
    return 0;
  }

}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, 
						 unsigned int num_completions){
    //for magic numbers
  int letterA = 97;
  int letterZ = 122;
  int space = 26;
  std::vector<Node*> allNodes; // for storing DFS nodes
  std::vector<std::string> words; // for returning freq words
  if(prefix == ""){ // check if prefix is empty
    std::cout << "Invalid Input. Please retry with correct input" << 
    std::endl;
    return words;
  }
  Node* node = root;
  std::stack<Node*> search; // for DFS
  // find althorigthm to get to the desired node
  for(int i = 0; prefix[i] != '\0'; i++){
    if(prefix[i] < letterA || prefix[i] > letterZ){
      if(prefix[i] != ' '){
        std::cout << "Invalid Input. Please retry with correct input" << 
        std::endl;
        return words;
      }
    }//end outer if
    if(prefix[i] == ' '){
      if(node->children[space] == NULL){
        return words; // if doesn't contain the prefix
      }//end internal if
      else{
        node = node->children[space];
      }//end internal else
    }
    else{
      if(node->children[prefix[i] - 'a'] == NULL){
        return words;
      }//end internal if
      else{
        node = node->children[prefix[i] - 'a'];
      }//end internal else
    }
  }
  search.push(node); // push the node to the stack
  eSearch(search, allNodes); //do the DFS
  // get num_completions freq words
  autoComplete(allNodes, words, num_completions);
  return words;
}

/* Helper method for find the most freqent word */
void DictionaryTrie::autoComplete(std::vector<Node*>& nodes, 
		std::vector<std::string>& words, unsigned int maxNumFreq){
  unsigned int freq = 0;
  unsigned int maxFreq = 0;
  std::string freqWord = "";
  std::vector<Node*>::iterator it;
  for(unsigned int i = 0; i < maxNumFreq; i++){
    if(nodes.empty()){ // if the node vector is empty
      return;
    }
    for(it = nodes.begin(); it != nodes.end(); ++it){
      if((freq = getFreq((*it)->str)) > maxFreq){ // get the most frequent
        freqWord = (*it)->str; // update word
        maxFreq = freq; // update max frequency
      }
    }
    words.push_back(freqWord); // store the word into the vector
    for(it = nodes.begin(); it != nodes.end(); ++it){// delete the word's node
      if((*it)->str == freqWord){
        nodes.erase(it);
        break;
      }
    }
    maxFreq = 0; // reset maxFreq
    freq = 0; // reset freq 
    freqWord = ""; // reset freqWord
  }
}

/* Helper method for exhaustive search algorithm*/
void DictionaryTrie::eSearch(std::stack<Node*>& search, 
                                         std::vector<Node*>& nodes){
  Node* node = NULL;
  int total = 27;
  while(!search.empty()){ // check the stack is empty
    node = search.top(); // get the top elem
    search.pop(); // pop the top elem
    if(node->word){ // if it is a valid word
      nodes.push_back(node); // push the node into the node vector
    }
    for(int i = 0; i < total; i++){
      if(node->children[i] != NULL){// put every valid child into the stack
        search.push(node->children[i]);
      }
    }
  }
}

/* Helper method for the destructor */
void DictionaryTrie::deleteAll(Node* node, int index){
  int total = 27;
  for(int i = 0; i < total; i++){
    if(node->children[i] != NULL){ //set everything to null
      deleteAll(node->children[i], 0); //recurrsion deleteall
    }
  }
  delete node;
}
/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  int index = 0;
  deleteAll(root, index); //empty the tries
}

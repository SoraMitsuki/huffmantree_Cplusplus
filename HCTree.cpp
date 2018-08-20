/**
  * Partner1:
  * Name: Jiaqi Fan
  * PID: A12584051
  * Partner2:
  * Name: Xuanru Zhu
  * PID: A91064234
  * Date: 2/15/2017
  * PA3
  */
// the .cpp file that implemented all the function that mentioned in 
// .h file
// the huffman tree class should be all implemented here

#include "HCTree.h"
#include <algorithm>
#include <stack> 

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
  //create new nodes to put in the queue
  for(int i = 0; i < freqs.size(); i++){
    if(freqs[(byte)i] > 0){
      HCNode* node = new HCNode(freqs[(byte)i], (byte)i, 0, 0, 0);
      pq.push(node);
    }
  }
  //loop through the queue
  while(pq.size() > 1){
    //left node is the first one in the queue
    lNode = pq.top();
    pq.pop();
    //right node is the second one
    rNode = pq.top();
    pq.pop();
    //this is the vector for leaves
    if(lNode->c0 == NULL && lNode->c1 == NULL){
      leaves[lNode->symbol] = lNode;
    }
    if(rNode->c0 == NULL && rNode->c1 == NULL){
      leaves[rNode->symbol] = rNode;
    }
    //create parent node for HF tree
    HCNode* parent = new HCNode((lNode->count + rNode->count), 0, 0, 0, 0);
    if(lNode->symbol > rNode->symbol){
      parent->symbol = lNode->symbol;
    }
    else{
      //set symbol of parent
      parent->symbol = rNode->symbol;
    }
    //set 0 child and 1 child and parent pointer
    lNode->p = parent;
    rNode->p = parent;
    parent->c0 = lNode;
    parent->c1 = rNode;
    pq.push(parent);
  }
  root = pq.top();
  pq.pop();
  // if there is only one character
  if(root->c0 == NULL && root->c1 == NULL){
    root->c1 = new HCNode(root->count, root->symbol, 0, 0, 0);
    root->c1->p = root;
    leaves[root->symbol] = root->c1;
  }
}
/**
 * helper method for compress we need encode the header for the 
 * output file
 * PARA is the output stream
 */
void HCTree::encodeTree(ofstream& out) const{
  //use stack to help us build the tree
  std::stack<HCNode*> build;
  HCNode* node;
  std::vector<char> tree;
  //push the first node into the stack
  build.push(root);
  while(!build.empty()){
    //loop until the stack is empty
    node = build.top();
    build.pop();
    //if it is a left and right node are empty
    if(node->c0 == NULL && node->c1 == NULL){
      //push a 1 and the symbol into vector
      tree.push_back('1');
      tree.push_back(node->symbol);
    }
    else{
      //else push a 0 into vector
      tree.push_back('0');
    }
    //if the left child is not null
    if(node->c0 != NULL){
      build.push(node->c0);
    }
    //if the right child is not null
    if(node->c1 != NULL){
      build.push(node->c1);
    } 
  }
  //put the size into the out
  out << tree.size() << endl;
  //loop and push everything in vector into output
  for(int i = 0; i < tree.size(); i++){
    out << tree[i];
  }
}
/**
 * helper method for uncompress we need take the encoded file
 * and uncompress it
 * PARAM@: is the input stream, and the number of bytes in line
 */
void HCTree::reBuild(ifstream& in, int count){
  //create a char array for read
  char cInfo[count];
  in.read(cInfo, count);
  //initialize the iterator to 0
  int it = 0;
  //set root to newNode
  root = new HCNode(0, 0, 0, 0, 0);
  it++;
  //increase the iterator and call the recursive helper method
  buildTree(cInfo, it, root, count);
}
/**
 * revusive helper method for reBuild we need this method to construct
 * the whole huffman's tree
 * PARAM@: the char pointer contain data, iterator it and the end of 
 * the file
 */
void HCTree::buildTree(char* cInfo, int it, HCNode* node, int end){
  //base case
  if(it == end){
    return;
  }
  //if the char is 0
  else if(cInfo[it] == '0'){
    //we create a new node
    HCNode* newNode = new HCNode(0, 0, 0, 0, 0);
    //if the right child is null
    if(node->c1 == NULL){
      //we set the newnode's parents to node
      newNode->p = node;
      node->c1 = newNode;
      it++; //increase iterator
      //recursive
      buildTree(cInfo, it, newNode, end);
    }
    //if the left node is null repeat the process 
    else if(node->c0 == NULL){
      newNode->p = node;
      node->c0 = newNode;
      it++;
      buildTree(cInfo, it, newNode, end);
    }
    else{
      //if all full delete the newnode prevent from memory leak
      delete newNode;
      //call recursive on the parents node
      buildTree(cInfo, it, node->p, end);
    }
  }
  //if char array reads a 1
  else if(cInfo[it] == '1'){
    it++; //iterator increate
    //create a new node
    HCNode* newNode = new HCNode(0, 0, 0, 0, 0);
    //set the new node's symbol
    newNode->symbol = cInfo[it];
    //check for the right child
    if(node->c1 == NULL){
      newNode->p = node;
      node->c1 = newNode;
    }
    //check for the left child
    else if(node->c0 == NULL){
      newNode->p = node;
      node->c0 = newNode;
    }
    //else decrease the iterator twice to the parents
    else{
      it--;
      it--;
      //delete the new Node
      delete newNode;
    }
    it++;
    //if the node's leftchild is null
    if(node->c0 == NULL){
      //call recursive method on node
      buildTree(cInfo, it, node, end);
    }
    else{
      //if the iterator reaches the end
      if(it == end){
        //build base on node
        buildTree(cInfo, it, node, end);
      }
      else{
	//else build based on node's parents
        buildTree(cInfo, it, node->p, end);
      }
    }
  }
}
  
/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const{
  //find symbol in leave vector
  HCNode* nRoot = leaves[symbol];
  byte tempSymb;
  //create a code vector
  std::vector<int> code;
  //traverse up the tree to root
  while(nRoot != root){
    tempSymb = nRoot->symbol;
    nRoot = nRoot->p;
    //go to parent and find bit
    if((nRoot->c1)->symbol == tempSymb){
      code.push_back(1);
    }
    else if((nRoot->c0)->symbol == tempSymb){
      code.push_back(0);
    }
  }
  std::reverse(code.begin(), code.end());
  for(unsigned int i = 0; i < code.size(); i++){
    out.writeBit(code[i]);
  } 
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const{
  //find symbol in leave vector
  HCNode* nRoot = leaves[symbol];
  byte tempSymb;
  //create a code vector
  std::vector<char> code;
  //traverse up the tree to root
  while(nRoot != root){
    tempSymb = nRoot->symbol;
    nRoot = nRoot->p;
    //go to parent and find bit
    if((nRoot->c0)->symbol == tempSymb){
      code.push_back('0');
    }
    else{
      //push 1
      code.push_back('1');
    }
  }
  //reverse string
  std::reverse(code.begin(), code.end());
  for(unsigned int i = 0; i < code.size(); i++){
    out << code[i];
  } 
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const{
  //this hold the code
  int code;
  HCNode* node = root;
  while(1){
    //base case when both childs are null
    if(node->c0 == NULL && node->c1 == NULL){
      break;
    }
    //call readBit to get the bits
    code = in.readBit();
    //if the code is 0 then
    if(code == 0){
      //set node to left child
      node = node->c0;
    }
    //else set it to right child
    else if(code == 1){
      node = node->c1;
    }
  } 
  return node->symbol;
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const{
  char code;
  //node is the being looked at next for the code
  HCNode* node = root;
  //loop until there are no more children 
  while(1){
    if(node->c0 == NULL && node->c1 == NULL){
      break; // if this is the leaf(symbol) node
    }
    //read the input file
    code = in.get();
    if(in.eof()){
      return 0; // if it is end of the file
    }
    //check if it is a 0
    if(code == '0'){
      //go to c0
      node = node->c0;
    }
    //check if it is a 1
    else if(code == '1'){
      //go to c1
      node = node->c1;
    }
  }
  //once at a leaf node
  return node->symbol;
}
/**
 * Helper method that delete all the nodes to empty the tree
 */
void HCTree::deleteAll(HCNode* node){
  if(node == NULL){
    return;
  }
  //recersive delete all left child 
  deleteAll(node->c0);
  //and the delete all the right child
  deleteAll(node->c1);
  delete node;
}

/**
 * Destructor of the HCTree;
 */
HCTree::~HCTree(){
  deleteAll(root);
}

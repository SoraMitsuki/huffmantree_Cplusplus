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
// the main class that will compress the input file and encode it to 
// output file.

#include <iostream>
#include <fstream>
#include "HCTree.h"

using namespace std;

/*
 * this main method taked 2 argument
 * argv[1] = the input file with words inside
 * argv[2] = the output file that contain the encoding from the input file
 */
int main( int argc, char** argv){
  //create input and output stream
  ifstream inFile;
  ofstream outFile;
  byte nextByte;
  long totalBytes = 0;
  //check the number of arguments
  if(argc != 3){
    std::cout << "Invalid number of arguments" << std::endl;
    return -1;
  }
  //open the input file by ifstream
  inFile.open(argv[1], ios::binary);
  if(!inFile.is_open()){
    //check if the input file is legal or not
    std::cout << "Cannot open the input file" << std::endl;
    return -1;
  }
  // check if the file is empty
  inFile.seekg(0, inFile.end);
  if(inFile.tellg() == 0){
    outFile.open(argv[2]);
    outFile << "";
    std::cout << "This is an empty file, no thing to process" << std::endl;
    return 0;
  }
  inFile.seekg(0, inFile.beg);
  //create a vector with size 256 and all 0s
  std::vector<int> freqs(256, 0);
  while(1){
    //reord the frequency of the input words
    nextByte = (byte)inFile.get();
    //reach the end and break
    if(inFile.eof()){ 
      break;
    }
    freqs[nextByte]++;
    totalBytes++;
  }
  //close the input stream and start building the tree
  inFile.close();
  HCTree tree;
  tree.build(freqs);
  //open the output file
  outFile.open(argv[2], ios::binary);
  if(!outFile.is_open()){
    //is the output file is ilegal return -1
    std::cout << "Cannot open the output file" << std::endl;
    return -1;
  }
  outFile << totalBytes << endl;
  // encode the tree to the file
  tree.encodeTree(outFile);
  inFile.open(argv[1], ios::binary);
  if(!inFile.is_open()){
    //check for the input file is legal or not because we opened it again
    std::cout << "Cannot open the input file" << std::endl;
    return -1;
  }
  //use bit output stream to wrtie bytes
  BitOutputStream output(outFile);
  while(1){
    nextByte = (byte)inFile.get();
    //break at the end of file
    if(inFile.eof()){
      break;
    }
    //encode until the end of file
    tree.encode(nextByte, output); 
  }
  //clean output
  output.flush();
  //close both stream for input and uot file
  inFile.close();
  outFile.close();
  
  return 0;
}

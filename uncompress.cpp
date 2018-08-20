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
// the main class that will uncompress the file that encoded by compressor.

#include <iostream>
#include <fstream>
#include "HCTree.h"

using namespace std;
/*
 * this main method taked 2 argument
 * argv[1] = the input file which is the file comtain endocing
 * argv[2] = the output file that contain the decoding from the input file
 */
int main( int argc, char** argv){
  //create input output stream
  ifstream inFile;
  ofstream outFile;
  std::string total;
  //all the bytes in the file
  long totalBytes = 0;
  std::string count;
  int countByte = 0;
  //check for number of arugment when calling the main method
  if(argc != 3){
    std::cout << "Invalid number of arguments" << std::endl;
    return -1;
  }
  //open the input file
  inFile.open(argv[1], ios::binary);
  if(!inFile.is_open()){
    //check the input file is legal or not
    std::cout << "Cannot open the input file" << std::endl;
    return -1;
  }
  // check if the file is empty
  inFile.seekg(0, inFile.end);
  if(inFile.tellg() == 0){
    std::cout << "This is an empty file" << std::endl;
    outFile.open(argv[2]);
    outFile << "";
    return 0;
  }
  //set the beginning and the end of file to read
  inFile.seekg(0, inFile.beg);
  getline(inFile, total);
  //get the total bytes of the file
  totalBytes = stoi(total);
  getline(inFile, count);
  //get the byte for a line
  countByte = stoi(count);
  // rebuild the tree
  HCTree tree;
  //call rebuild tree based on the encoded input
  tree.reBuild(inFile, countByte);
  outFile.open(argv[2], ios::binary);
  if(!outFile.is_open()){
    //check the legality of the output file
    std::cout << "Cannot open the output file" << std::endl;
    return -1;
  }
  //read them using bit input stream
  BitInputStream input(inFile);
  for(long i = 0; i < totalBytes; i++){
    outFile.put(tree.decode(input));
  }
  //close the ofstream
  inFile.close();
  outFile.close();

  return 0;
}

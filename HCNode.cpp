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
// this is node class for huffman tree
#include "HCNode.h"

bool HCNode::operator<(const HCNode& other) const{
  if(count != other.count){
    return count > other.count;
  }
  else{
    return symbol < other.symbol;
  }
}

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
// the .cpp file that contain all the function for bitoutput stream
// all method should implemented here

#include <iostream>
#include "BitOutputStream.h"
 
/**Send the buffer to the output, and clear it
 */ 
void BitOutputStream::flush(){
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/** Write the least significant bit of the argument to 
 *  the bit buffer, and increment the bit buffer index.
 *  But flush the buffer first, if it is full.
 */
void BitOutputStream::writeBit(int i){
  // Is the bit buffer full? then flush it.
  if(nbits == full){
    flush();
  }
  // Write the least significant bit of i into the buffer
  // at the current index
  unsigned char mask = (i & 1) << (full - nbits - offset);
  buf = buf | mask;
  
  // Increment the index
  nbits++;
}


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
// the .cpp file that contain all the function for bitinpit stream
// all method should implemented here
#include <iostream>
#include "BitInputStream.h"

/**Fill the buffer from the input */
void BitInputStream::fill(){
  buf = in.get();
  nbits = 0;
}

/**Read the next bit from the bit buffer.
 * Fill the buffer from the input stream first if needed.
 * Return 1 if the bit read is 1;
 * Return 0 if the bit read is 0;
 */
int BitInputStream::readBit(){
  int bit;
  // If all bits in the buffer are read, fill the buffer first
  if(nbits == full){
    fill();
  }

  // Get the bit at the appriopriate location in the bit
  // buffer, and return the approriate int
  unsigned char extractedBit = (unsigned)buf >> (full - nbits - offset);
  bit = extractedBit & 1;
  // Increment the index
  nbits++;
  return bit;
}


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
// the .h file that contain all the function for bitoutput stream
// all method should implemented in the .cpp file

#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <iostream>

class BitOutputStream{
private:
  char buf; // one byte buffer of bits
  int nbits; // how many bits have been written to buf
  std::ostream & out; // reference to the output stream to use
  int full = 8;
  int offset = 1;
  
public:
  /**Initialize a BitOutputStream that will use
   * the given ostream for output
   */ 
  BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
    // clear buffer and bit counter
  }
  
  /**Send the buffer to the output, and clear it
   */ 
  void flush();
  
  /** Write the least significant bit of the argument to 
   *  the bit buffer, and increment the bit buffer index.
   *  But flush the buffer first, if it is full.
   */
  void writeBit(int i);
};
#endif

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
// the .h file that contain all the function for bitinpit stream
// all method should implemented in the .cpp file

#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <iostream>

class BitInputStream{
private:
  char buf; // one byte buffer of bits
  int nbits; // how many bits have been read from buf
  std::istream & in; // the input stream to use
  int full = 8;
  int offset = 1;
public:

  /**Initialize a BitInputStream that will use
   * the given istream for input.
   */  
  BitInputStream(std::istream & is) : in(is){
    buf = 0; // clear buffer
    nbits = 8; // initialize bit index
  }
  
  /**Fill the buffer from the input */
  void fill();

  /**Read the next bit from the bit buffer.
   * Fill the buffer from the input stream first if needed.
   * Return 1 if the bit read is 1;
   * Return 0 if the bit read is 0;
   */
  int readBit();
};
#endif

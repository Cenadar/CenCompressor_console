CenCompressor_console
=====================

CenCompressor_console is arhiver by a Huffman method, written in C++ with Qt

Archive specification:
  * 5 null bits
  * 3 bits means number of unused bits which is added after tree information

  * 256 bits (32 bytes) - mask of used characters [N of them is turned on]
  * N bytes - length of each used character code
  * unused bits
  * sequence of codes

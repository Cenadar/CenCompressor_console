#include <QtCore/QCoreApplication>
#include "ccompressor.h"
#include <iostream>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  /*cout << "HELLO WORLD!" << endl;
  cout << argv[0] << endl;*/

  CCompressor Compressor;

  try {
    Compressor.compress("input.txt", "output.txt");
    cout << "Compressed succesffully" << endl;
  } catch(const char* error_message) {
    cout << "ERROR: Compress faild:" << endl;
    cout << error_message << endl;
  }
  return 0;


  //return a.exec();
}

#include <QtCore/QCoreApplication>
#include "ccompressor.h"
#include <iostream>

int main(int argc, char *argv[]) {
  string input_file_name = argc > 1 ? argv[1] : "input.txt";
  string output_file_name = argc > 2 ? argv[2] : "output.txt";
  QCoreApplication a(argc, argv);

  CCompressor Compressor;

  try {
    Compressor.compress(input_file_name, output_file_name);
    cout << "Compressed succesffully" << endl;
  } catch(string error_message) {
    cout << "ERROR: Compress failed:" << endl;
    cout << error_message << endl;
  }
  return 0;

  //return a.exec();
}

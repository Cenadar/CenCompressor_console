#include <QtCore/QCoreApplication>
#include "ccompressor.h"
#include <iostream>

void usage() {
  cout <<
  "  Cenadar Compressor Console by Maxim Bevza, K25\n"
  "\n"
  "  Usage: ./cencompressor_console <command> <archive_name> <file_name>\n"
  "\n"
  "  <Commands>\n"
  "    a: Archivate\n"
  "    x: eXtract\n";
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    usage();
    return 0;
  }
  if (string(argv[1]) == "a") {
    CCompressor Compressor;
    Compressor.compress(argv[3], argv[2]);
  } else if (string(argv[1]) == "x") {
    CCompressor Compressor;
    Compressor.uncompress(argv[2], argv[3]);
  } else {
    usage();
    return 0;
  }

/*  string input_file_name = argc > 1 ? argv[1] : "gcg";//"input.txt";
  string output_file_name = argc > 2 ? argv[2] : "output.txt";
  QCoreApplication a(argc, argv);

  CCompressor Compressor;

  try {
    Compressor.compress(input_file_name, output_file_name);
    Compressor.uncompress(output_file_name, input_file_name + ".dearc");
  } catch(string error_message) {
    cout << "ERROR! Compress failed: " << endl;
    cout << error_message << endl;
  }
  return 0;

  //return a.exec();*/
}

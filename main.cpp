#include <QtCore/QCoreApplication>
#include "ccompressor.h"
#include "logger.h"
#include <iostream>

void usage() {
  cout <<
  "  Cenadar Compressor Console by Maxim Bevza, K25\n"
  "\n"
  "  Usage: cencompressor_console <command> <archive_name> <file_name>\n"
  "\n"
  "  <Commands>\n"
  "    a: Archivate\n"
  "    x: eXtract\n";
}

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {  
  if (argc < 4) {
    usage();
    return 0;
  }  
  if (string(argv[1]) == "a") {
    ICompressor *Compressor =
        new CCompressor(new CFileByteReader(argv[3]),
                        new CFileByteWriter(argv[2]),
                        new CStreamLogger(cerr, false),
                        CCompressor::UseLogger |
                        CCompressor::DeleteReader |
                        CCompressor::DeleteWriter |
                        CCompressor::DeleteLogger);
    Compressor->compress();

    delete Compressor;
  } else if (string(argv[1]) == "x") {
    ICompressor *Compressor =
        new CCompressor(new CFileByteReader(argv[2]),
                        new CFileByteWriter(argv[3]),
                        new CStreamLogger(cerr, false),
                        CCompressor::UseLogger |
                        CCompressor::DeleteReader |
                        CCompressor::DeleteWriter |
                        CCompressor::DeleteLogger);
    Compressor->uncompress();

    delete Compressor;
  } else {
    usage();
    return 0;
  }
}

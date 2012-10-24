#include <QtCore/QCoreApplication>
#include "ccompressor.h"
#include "logger.h"
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
    CCompressor *Compressor =
        new CCompressor(new CFileByteReader(argv[3]),
                        new CFileByteWriter(argv[2]),
                        new CFileLogger("log.txt", false));
    Compressor->compress();

    delete Compressor;
  } else if (string(argv[1]) == "x") {
    CCompressor *Compressor =
        new CCompressor(new CFileByteReader(argv[2]),
                        new CFileByteWriter(argv[3]),
                        new CFileLogger("log.txt", false));
    Compressor->uncompress();

    delete Compressor;
  } else {
    usage();
    return 0;
  }
}

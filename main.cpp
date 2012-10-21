#include <QtCore/QCoreApplication>
#include "ccompressor.h"
#include <logger.h>
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
    ILogger *logger = new CFileLogger("log.txt", true);

    CFileByteReader *BR = new CFileByteReader(argv[3]);
    CCompressor Compressor(BR, logger);
    Compressor.compress(argv[2]);
    delete BR;

    delete logger;
  } else if (string(argv[1]) == "x") {
    ILogger *logger = new CFileLogger("log.txt", true);

    CFileByteReader *BR = new CFileByteReader(argv[2]);
    CCompressor Compressor(BR, logger);
    Compressor.uncompress(argv[3]);
    delete BR;

    delete logger;
  } else {
    usage();
    return 0;
  }
}

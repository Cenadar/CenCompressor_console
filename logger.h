#ifndef LOOGER_H
#define LOOGER_H

#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void debug();

class ILogger {
 public:
  virtual ~ILogger() {}

  void virtual log(const string& val) = 0;
};


class CLogger: public ILogger {
 public:
  CLogger(bool include_time_): include_time(include_time_) {}
  ~CLogger() {}

 protected:
  const string get_time();

  bool include_time;
};


class CFileLogger: public CLogger {
 public:
  CFileLogger(const string& file_name, bool include_time_):
    CLogger(include_time_),
    fout(file_name.c_str()) {}

  CFileLogger(const char* file_name, bool include_time_):
    CLogger(include_time_),
    fout(file_name) {}

  ~CFileLogger() {fout.close();}

  void log(const string &val);
private:
  ofstream fout;
};


class CStreamLogger: public CLogger {
 public:
  CStreamLogger(ostream &out_, bool include_time_):
    CLogger(include_time_),
    out(&out_) {}

  void log(const string &val);
 private:
  ostream *out;
};

string itoa(size_t v);

#endif // LOOGER_H

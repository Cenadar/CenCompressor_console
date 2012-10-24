#ifndef LOOGER_H
#define LOOGER_H

#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void debug();

class ILogger {
 public:
  ILogger(bool include_time_): include_time(include_time_) {}
  virtual ~ILogger() {}

  void virtual log(const char* val) = 0;
  void log(const string& val) {log(val.c_str());}
  const string get_time() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime (&rawtime);
    string res = asctime(timeinfo);
    return res.substr(0, res.size() - 1);
  }
 protected:
  bool include_time;
};


class CFileLogger: public ILogger {
 public:
  CFileLogger(const string& file_name, bool include_time_):
    ILogger(include_time_),
    fout(file_name.c_str()) {}

  CFileLogger(const char* file_name, bool include_time_):
    ILogger(include_time_),
    fout(file_name) {}

  ~CFileLogger() {fout.close();}

  void log(const char* val) {
    if (include_time) fout << get_time() << ": ";
    fout << val << endl;
  }
 private:
  ofstream fout;
};


string itoa(size_t v);

#endif // LOOGER_H

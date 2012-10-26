#include "logger.h"

string itoa(size_t v) {
 if (v == 0) return "0";
 string res;
 while(v > 0) {
   res += v%10 + '0';
   v /= 10;
 }
 return string(res.rbegin(), res.rend());
}

const string CLogger::get_time() {
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime (&rawtime);
  string res = asctime(timeinfo);
  return res.substr(0, res.size() - 1);
}

void CFileLogger::log(const string &val) {
  if (include_time) fout << get_time() << ": ";
  fout << val << endl;
}

void CStreamLogger::log(const string &val) {
  if (include_time) (*out) << get_time() << ": ";
  (*out) << val << endl;
}

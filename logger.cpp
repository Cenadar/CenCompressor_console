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

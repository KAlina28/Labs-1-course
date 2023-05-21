#include "util.h"
#include "io.h"

//так
//#include "io.c"
//или так
//void logDebug(char s) {
//    char c = s;
//    s = c;
//}

double max(double a, double b) {
  logDebug('m');
  if (a > b) return a;
  return b;
}


#include <stdio.h>
#include "cstring_jslike.h"

int main() {
  string str1 $init$, str2;
  str1 = STRING_PROTOTYPE.charCodeAt(3, 65,66,67);
  str2 = STRING_PROTOTYPE.concat2(str1, STRING("2333"));
  printf("%s\n", str1->c_str);
  printf("%s\n", str2->c_str);
  return 0;
}
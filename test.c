#include <stdio.h>
#include "cstring_jslike.h"

int main() {
  string str1 = fromCharCode(3, 65, 66, 67);
  printf("str1 is: %s\n", str1->c_str);

  string str2 = concat2(str1, STRING("2333"));
  printf("str2 is: %s\n", str2->c_str);

  string str3 = concat(3, str1, STRING(" "), str2);
  printf("str1 + space + str2 is: %s\n", str3->c_str);

  printf("str1.charAt(2) is: %c\n", charAt(str1, 2));

  return 0;
}
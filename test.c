#include <stdio.h>
#include "cstring_jslike.h"

int main() {
  // ASCII fromCharCode
  string str1 = fromCharCode(3, 65, 66, 67);
  printf("str1 is: %s\n", str1->c_str);
  printf("\n");

  // String literal
  string str2 = concat2(str1, LITERAL("2333"));
  printf("str2 is: %s\n", str2->c_str);
  printf("\n");

  // String concat
  string str3 = concat(3, str1, LITERAL(" "), str2);
  printf("str1 + space + str2 is: %s\n", str3->c_str);
  printf("\n");

  // ASCII charAt & charCodeAt
  printf("str1.charAt(2) is: %c\n", charAt(str1, 2));
  printf("str1.charCodeAt(2) is: %d\n", charCodeAt(str1, 2));
  printf("\n");

  // UTF-8 charAt
  string str4 = LITERAL(u8"怎么说");
  printf("'%s'.charAtU(2) is: %s\n", str4->c_str, charAtU(str4, 2)->c_str);
  printf("\n");

  // ASCII endWith
  printf("str1.endWith('BC') is: %s\n", endsWithT(str1, LITERAL("BC")) ? "true" : "false");
  printf("str1.endWith('B') is: %s\n", endsWithT(str1, LITERAL("B")) ? "true" : "false");
  printf("str1.endWith('B', 2) is: %s\n", endsWith(str1, LITERAL("B"), 2) ? "true" : "false");
  printf("\n");

  // UTF-8 string length
  string str5 = LITERAL(u8"霹雳霹雳🍻");
  printf("length('%s') is: %llu\n", str5->c_str, length(str5));
  printf("\n");

  return 0;
}
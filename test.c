#include <stdio.h>
#include "cstring_jslike.h"

int main() {
  // ASCII fromCharCode
  string str1 = fromCharCode(3, 65, 66, 67);
  printf("str1 is: %s\n", STR(str1));
  printf("\n");

  // String literal
  string str2 = concat2(str1, LITERAL("2333"));
  printf("str2 is: %s\n", STR(str2));
  printf("\n");

  // String concat
  /// You don't need to free the LITERAL string
  // (as it's allocated by alloca method)
  // and can be released automatically after function call
  string str3 = concat(3, str1, LITERAL(" "), str2);
  printf("str1 + space + str2 is: %s\n", STR(str3));
  printf("\n");

  // ASCII charAt & charCodeAt
  printf("str1.charAt(2) is: %c\n", charAt(str1, 2));
  printf("str1.charCodeAt(2) is: %d\n", charCodeAt(str1, 2));
  printf("\n");

  // UTF-8 charAt
  /// You **MUST** delete(free) the string manually
  // (as it's allocated by malloc method)
  string str4 = STRING(u8"怎么说");
  printf("'%s'.charAtU(2) is: %s\n", STR(str4), STR(charAtU(str4, 2)));
  /// Delete(free) the string like this:
  $STRING(str4);
  printf("\n");

  // ASCII endWith
  printf("str1.endWith('BC') is: %s\n", endsWithT(str1, LITERAL("BC")) ? "true" : "false");
  printf("str1.endWith('B') is: %s\n", endsWithT(str1, LITERAL("B")) ? "true" : "false");
  printf("str1.endWith('B', 2) is: %s\n", endsWith(str1, LITERAL("B"), 2) ? "true" : "false");
  printf("\n");

  // UTF-8 string length
  string str5 = STRING(u8"霹雳霹雳🍻");
  printf("str5 is: %s\n", STR(str5));
  printf("length(str5) is: %llu\n", length(str5));
  printf("\n");

  // String To GBK
  printf("str5 in GBK is: %s\n", OPT(str5));
  $STRING(str5);
  printf("\n");

  return 0;
}
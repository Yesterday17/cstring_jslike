#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include "cstring_jslike.h"

int main() {
  // ASCII fromCharCode
  string str1 = fromCharCode(3, 65, 66, 67);
  printf("str1 is: %s\n", STR(str1));
  printf("\n");

  // String literal
  /// You don't need to free the LITERAL string
  // (as it's allocated by alloca method)
  // and can be released automatically after function call
  string str2 = concat2(str1, LITERAL("2333"));
  printf("str2 is: %s\n", STR(str2));
  printf("\n");

  // String concat
  string str3 = concat(3, str1, LITERAL(" "), str2);
  printf("str3 = str1 + space + str2 is: %s\n", STR(str3));
  printf("\n");

  // ASCII charAt & charCodeAt
  printf("str1.charAt(2) is: %c\n", charAt(str1, 2));
  printf("str1.charCodeAt(2) is: %d\n", charCodeAt(str1, 2));
  printf("\n");

  // UTF-8 charAtU
  /// You **MUST** delete(free) the string manually
  // (as it's allocated by malloc method)
  string str4 = STRING(u8"怎么说");
  printf("str4 is: %s\n", STR(str4));
  printf("str4.charAtU(2) is: %s\n", STR(charAtU(str4, 2)));
  printf("\n");

  // ASCII endWith
  printf("str1.endWith('BC') is: %s\n", endsWithD(str1, LITERAL("BC")) ? "true" : "false");
  printf("str1.endWith('B') is: %s\n", endsWithD(str1, LITERAL("B")) ? "true" : "false");
  printf("str1.endWith('B', 2) is: %s\n", endsWith(str1, LITERAL("B"), 2) ? "true" : "false");
  printf("\n");

  // UTF-8 endWithU
  string str5 = STRING(u8"啊我死了");
  printf("str5 is: %s\n", STR(str5));
  printf("str5.endWithU('我死了') is: %s\n", endsWithUD(str5, LITERAL(u8"我死了")) ? "true" : "false");
  printf("str5.endWithU('啊') is: %s\n", endsWithUD(str5, LITERAL(u8"啊")) ? "true" : "false");
  printf("str5.endWithU('我', 1) is: %s\n", endsWithU(str5, LITERAL(u8"我"), 1) ? "true" : "false");
  printf("str5.endWithU('我', 2) is: %s\n", endsWithU(str5, LITERAL(u8"啊我"), 2) ? "true" : "false");
  printf("\n");

  // UTF-8 string length
  string str6 = STRING(u8"霹雳霹雳🍻");
  printf("str6 is: %s\n", STR(str6));
  printf("length(str6) is: %zu\n", length(str6));
  printf("\n");

  // String To GBK
  printf("str6 in GBK is: %s\n", OPT(str6));
  printf("\n");

  // UTF-8 character size
  printf("UTF-8 size of the character at str6[3] is: %d\n", ucharSize(str6, 3));
  printf("\n");

  // includes
  printf("str1.includes('bC') is: %s\n", includes(str1, LITERAL("bC")) ? "true" : "false");
  printf("str1.includes('BC') is: %s\n", includes(str1, LITERAL("BC")) ? "true" : "false");

  // indexOf, lastIndexOf
  /// Returns the length of searched string if not found
  // (as size_t is unsigned)
  printf("str1.indexOf('BC') is: %zu\n", indexOf(str1, LITERAL("BC"), 0));
  printf("str6.indexOf('雳') is: %zu\n", indexOf(str6, LITERAL(u8"雳"), 0));
  printf("str6.lastIndexOf('雳') is: %zu\n", lastIndexOf(str6, LITERAL(u8"雳"), 0));
  printf("\n");

  // padEnd & padStart
  printf("str6.padEnd(100, 'strPadEnd') is: %s\n", STR(padEnd(str6, 100, LITERAL("strPadEnd"))));
  printf("str6.padEndD(25) is: %s\n", STR(padEndD(str6, 25)));
  printf("str6.padStart(100, 'strPadStart') is: %s\n", STR(padStart(str6, 100, LITERAL("strPadStart"))));
  printf("str6.padStartD(25) is: %s\n", STR(padStartD(str6, 25)));
  printf("\n");

  // repeat
  printf("str6.repeat(10) is: %s\n", STR(repeat(str6, 10)));
  printf("\n");

  // slice
  printf("str3.slice(5, 9) is: %s\n", STR(slice(str3, 5, 9)));
  printf("str3.slice(5, -1) is: %s\n", STR(slice(str3, 5, -1)));
  printf("str3.slice(-6, 11) is: %s\n", STR(slice(str3, -6, 11)));
  printf("str3.slice(-6, -4) is: %s\n", STR(slice(str3, -6, -4)));
  printf("str3.slice(-6) is: %s\n", STR(sliceD(str3, -6)));
  printf("\n");

  // split
  string str7 = STRING("first, second, third, fourth");
  string *str7_split;
  size_t str7_split_len = split(str7, LITERAL(", "), &str7_split);
  printf("str7 is: %s\n", STR(str7));
  printf("str7.split(', ') is:\n");
  printf("  len: %zu\n", str7_split_len);
  for (size_t i = 0; i < str7_split_len; i++)
    printf("  %zu: %s\n", i + 1, STR(str7_split[i]));
  printf("\n");

  /// Delete(free) the string like the following ones do:
  $STRING(str1);
  $STRING(str2);
  $STRING(str3);
  $STRING(str4);
  $STRING(str5);
  $STRING(str6);
  $STRING(str7);

  return 0;
}
#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include "cstring_jslike.h"

int main() {
  // ASCII fromCharCode
  stringbuf str1 = fromCharCode(3, 65, 66, 67);
  printf("str1 is: %s\n", CSTR(str1));
  printf("\n");

  // String literal
  /// You don't need to free the string, but you need to free stringbuf
  // (as it's allocated by alloca method)
  // and can be released automatically after function call
  stringbuf str2 = concat2(str1, LITERAL("2333"));
  printf("str2 is: %s\n", CSTR(str2));
  printf("\n");

  // String concat
  stringbuf str3 = concat(3, str1, LITERAL(" "), str2);
  printf("str3 = str1 + space + str2 is: %s\n", CSTR(str3));
  printf("\n");

  // ASCII charAt & charCodeAt
  printf("str1.charAt(2) is: %c\n", *charAt(str1, 2));
  printf("str1.charCodeAt(2) is: %d\n", charCodeAt(str1, 2));
  printf("\n");

  // UTF-8 charAtU
  /// You **MUST** delete(free) the string manually
  // (as it's allocated by malloc method)
  stringbuf str4 = STR_BUF("怎么说");
  printf("str4 is: %s\n", CSTR(str4));
  printf("str4.charAt(2) is: %s\n", charAt(str4, 2));
  printf("str4.charAtU(2) is: %s\n", CSTR(charAtU(str4, 2)));
  printf("\n");

  // ASCII endWith
  printf("str1.endWith('BC') is: %s\n", endsWithD(str1, LITERAL("BC")) ? "true" : "false");
  printf("str1.endWith('B') is: %s\n", endsWithD(str1, LITERAL("B")) ? "true" : "false");
  printf("str1.endWith('B', 2) is: %s\n", endsWith(str1, LITERAL("B"), 2) ? "true" : "false");
  printf("\n");

  // UTF-8 endWithU
  stringbuf str5 = STR_BUF("啊我死了");
  printf("str5 is: %s\n", CSTR(str5));
  printf("str5.endWithU('我死了') is: %s\n", endsWithUD(str5, LITERAL("我死了")) ? "true" : "false");
  printf("str5.endWithU('啊') is: %s\n", endsWithUD(str5, LITERAL("啊")) ? "true" : "false");
  printf("str5.endWithU('我', 1) is: %s\n", endsWithU(str5, LITERAL("我"), 1) ? "true" : "false");
  printf("str5.endWithU('我', 2) is: %s\n", endsWithU(str5, LITERAL("啊我"), 2) ? "true" : "false");
  printf("\n");

  // UTF-8 string length
  stringbuf str6 = STR_BUF("霹雳霹雳🍻");
  printf("str6 is: %s, u8 str6 is: %s\n", CSTR(str6), U8_CSTR(str6));
  printf("length(str6) is: %zu\n", length(str6));
  printf("\n");

  // String To GBK
  printf("str6 in GBK is: %s\n", CSTR(str6));
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
  printf("str6.indexOf('雳') is: %zu\n", indexOf(str6, LITERAL("雳"), 0));
  printf("str6.lastIndexOf('雳') is: %zu\n", lastIndexOf(str6, LITERAL("雳"), 0));

  // padEnd & padStart
  printf("str6.padEnd(100, 'strPadEnd') is: %s\n", CSTR(padEnd(str6, 100, LITERAL("strPadEnd"))));
  printf("str6.padStart(100, 'strPadStart') is: %s\n", CSTR(padStart(str6, 100, LITERAL("strPadStart"))));
  printf("\n");

  // repeat
  printf("str6.repeat(10) is: %s\n", CSTR(repeat(str6, 10)));
  printf("\n");

  // slice
  printf("str3.slice(5, 9) is: %s\n", CSTR(slice(str3, 5, 9)));
  printf("str3.slice(5, -1) is: %s\n", CSTR(slice(str3, 5, -1)));
  printf("str3.slice(-6, 11) is: %s\n", CSTR(slice(str3, -6, 11)));
  printf("str3.slice(-6, -4) is: %s\n", CSTR(slice(str3, -6, -4)));
  printf("str3.slice(-6) is: %s\n", CSTR(sliceD(str3, -6)));
  printf("\n");

  /// Delete(free) the string like the following:
  $STR_BUF(str1);
  $STR_BUF(str2);
  $STR_BUF(str3);
  $STR_BUF(str4);
  $STR_BUF(str5);
  $STR_BUF(str6);

  return 0;
}
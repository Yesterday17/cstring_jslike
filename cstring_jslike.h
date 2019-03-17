//
// Created by Yesterday17 on 3/15.
//

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef CSTRING_JSLIKE_CSTRING_JSLIKE_H
#define CSTRING_JSLIKE_CSTRING_JSLIKE_H

#define $init$ newEmptyString()
#define STR_BUF(c) newString(u8##c)
#define $STR_BUF(c) deleteString(c)

#ifndef _WIN32
#define ALLOCA alloca
#else
#define ALLOCA _alloca
#endif
#define STRING(c) newLiteralString(c, (String*) ALLOCA(sizeof(String)), NULL)
#define LITERAL(c) newLiteralString(u8##c, (String*) ALLOCA(sizeof(String)), NULL)
#define BUILD_STR(str) newLiteralString((str)->c_str, (String*) ALLOCA(sizeof(String)), (char*) ALLOCA(sizeof(char)*(str)->unitCnt))
#define _SIZED_LITERAL(size) newLiteralString((char*) ALLOCA(sizeof(char) * (size)), (String*) ALLOCA(sizeof(String)), NULL)

typedef struct String {
  size_t unitCnt;
  size_t bufSize;
  size_t length;
  char *c_str;
} String;
typedef String *string;
typedef string stringbuf;

// Create string
stringbuf newEmptyString();
stringbuf newSizedString(size_t size);
stringbuf newString(char *c);
string newLiteralString(char *c, string str, char *buf);

// Release string
void deleteString(stringbuf str);
string freeAssign(string *dest, string src);

// Basic utilities
#define STRING_EQUAL 0
#define STRING_LARGER 1
#define STRING_SMALLER -1
int compareString(string str1, string str2);
stringbuf reverseString(string str);
stringbuf cloneString(string str);

// Methods & prototype methods
stringbuf fromCharCode(uint64_t count, ...);

#define charAt(str,index) _charAt((str),(index),ALLOCA(sizeof(char)*3))
char* _charAt(string str, size_t index, char *buf);
int charCodeAt(string str, size_t index);
stringbuf concat(uint64_t count, ...);
bool endsWith(string src, string search, size_t len);
bool includes(string src, string pattern);
size_t indexOf(string str, string pattern, size_t from);
size_t lastIndexOf(string str, string pattern, size_t from);
stringbuf padEnd(string str, size_t len, string toPad);
stringbuf padStart(string str, size_t len, string toPad);
stringbuf repeat(string str, size_t times);
stringbuf slice(string str, int64_t beginSlice, int64_t endSlice);

// Help methods
stringbuf concat2(string a, string b);
#define endsWithD(src, search) endsWith(src, search, src->length)
#define padEndD(str, len) padEnd(str, len, LITERAL(" "))
#define padStartD(str, len) padStart(str, len, LITERAL(" "))
#define sliceD(str, beginSlice) slice(str, beginSlice, str->length)

// UTF-8 methods
#define charAtU(str,index) _charAtU((str), (index), _SIZED_LITERAL(5))
string _charAtU(string str, size_t index, stringbuf buf);
bool endsWithU(string src, string search, size_t len);

// UTF-8 help methods
size_t length(string src);
uint8_t ucharSize(string str, size_t offset);
#define endsWithUD(src, search) endsWithU(src, search, src->unitCnt)

// Help macros
#define U8_CSTR(str) str->c_str

// Encoding
char *stringToGBK(string str);
#define CSTR(str) stringToGBK(str)
char *cstrToGBK(char *src, size_t len, char *buf);

#endif //CSTRING_JSLIKE_CSTRING_JSLIKE_H

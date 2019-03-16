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
#define STRING(c) newLiteralString(c, (String*) alloca(sizeof(String)), NULL)
#define LITERAL(c) newLiteralString(u8##c, (String*) alloca(sizeof(String)), NULL)
#define BUILD_STR(str) newLiteralString((str)->c_str, (String*) alloca(sizeof(String)), (char*) alloca(sizeof(char)*(str)->unitCnt))
#else
#define STRING(c) newLiteralString(c, (String*) _alloca(sizeof(String)), NULL)
#define LITERAL(c) newLiteralString(u8##c, (String*) _alloca(sizeof(String)), NULL)
#define BUILD_STR(str) newLiteralString((str)->c_str, (String*) _alloca(sizeof(String)), (char*) _alloca(sizeof(char)*(str)->unitCnt))
#endif

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
const int STRING_EQUAL = 0;
const int STRING_LARGER = 1;
const int STRING_SMALLER = 2;
uint8_t compareString(string str1, string str2);
stringbuf reverseString(string str);
stringbuf cloneString(string str);

// Methods & prototype methods
stringbuf fromCharCode(uint64_t count, ...);
char charAt(string str, size_t index);
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
bool endsWithD(string src, string search);
stringbuf padEndD(string str, size_t len);
stringbuf padStartD(string str, size_t len);
stringbuf sliceD(string str, int64_t beginSlice);

// UTF-8 methods
string charAtU(string str, size_t index);
bool endsWithU(string src, string search, size_t len);

// UTF-8 help methods
size_t length(string src);
uint8_t ucharSize(string str, size_t offset);
bool endsWithUD(string src, string search);

// Help macros
#define U8_CSTR(str) str->c_str

// Encoding
char *stringToGBK(string str);
#define CSTR(str) stringToGBK(str)

#endif //CSTRING_JSLIKE_CSTRING_JSLIKE_H

//
// Created by Yesterday17 on 3/15.
//

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef CSTRING_JSLIKE_CSTRING_JSLIKE_H
#define CSTRING_JSLIKE_CSTRING_JSLIKE_H

#define $init$ = newEmptyString()
#define STRING(c) newLiteralString(c, (String*) malloc(sizeof(String)), true)
#define $STRING(c) deleteString(c)

#ifndef _WIN32
#define LITERAL(c) newLiteralString(c, (String*) alloca(sizeof(String)), false)
#else
#define LITERAL(c) newLiteralString(c, (String*) _alloca(sizeof(String)), false)
#endif

typedef struct String {
  size_t length;
  size_t size;
  size_t len;
  char *c_str;
} String;
typedef String *string;

// Create string
string newEmptyString();
string newSizedString(size_t size);
string newLiteralString(char *c, string str, bool copy);

// Release string
void deleteString(string str);
string freeAssign(string *dest, string src);

// Basic utilities
#define STRING_EQUAL 0
#define STRING_LARGER 1
#define STRING_SMALLER 2
uint8_t compareString(string str1, string str2);
string reverseString(string str);
string cloneString(string str);

// Methods & prototype methods
string fromCharCode(uint64_t count, ...);
char charAt(string str, size_t index);
int charCodeAt(string str, size_t index);
string concat(uint64_t count, ...);
bool endsWith(string src, string search, size_t len);
bool includes(string src, string pattern);
size_t indexOf(string str, string pattern, size_t from);
size_t lastIndexOf(string str, string pattern, size_t from);
string padEnd(string str, size_t len, string toPad);
string padStart(string str, size_t len, string toPad);
string repeat(string str, size_t times);
string slice(string str, int64_t beginSlice, int64_t endSlice);
size_t split(string str, string separator, string **array);

// Help methods
string concat2(string a, string b);
#define endsWithD(src, search) endsWith(src, search, src->length)
#define padEndD(str, len) padEnd(str, len, LITERAL(" "))
#define padStartD(str, len) padStart(str, len, LITERAL(" "))
#define sliceD(str, beginSlice) slice(str, beginSlice, str->length)

// UTF-8 methods
string charAtU(string str, size_t index);
bool endsWithU(string src, string search, size_t len);

// UTF-8 help methods
size_t length(string src);
uint8_t ucharSize(string str, size_t offset);
#define endsWithUD(src, search) endsWithU(src, search, src->len)

// Help macros
#define STR(str) str->c_str

// Encoding
char *stringToGBK(string str);
#define OPT(str) stringToGBK(str)

#endif //CSTRING_JSLIKE_CSTRING_JSLIKE_H

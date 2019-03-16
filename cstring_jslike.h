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
  uint64_t length;
  uint64_t size;
  size_t len;
  char *c_str;
} String;
typedef String *string;

// Create string
string newEmptyString();
string newSizedString(uint64_t size);
string newLiteralString(char *c, string str, bool copy);

// Release string
void deleteString(string str);
string freeAssign(string *dest, string src);

// Methods & prototype methods
string fromCharCode(uint64_t count, ...);
char charAt(string str, uint64_t index);
int charCodeAt(string str, uint64_t index);
string concat(uint64_t count, ...);
bool endsWith(string src, string search, uint64_t length);

// Help methods
string charAtU(string str, uint64_t index);
string concat2(string a, string b);
bool endsWithT(string src, string search);
size_t length(string src);

// Help macros
#define STR(str) str->c_str

// Encoding
char *stringToGBK(string str);
#define OPT(str) stringToGBK(str)

#endif //CSTRING_JSLIKE_CSTRING_JSLIKE_H

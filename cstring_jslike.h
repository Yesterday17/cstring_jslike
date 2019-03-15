//
// Created by Yesterday17 on 3/15.
//

#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>

#ifndef CSTRING_JSLIKE_CSTRING_JSLIKE_H
#define CSTRING_JSLIKE_CSTRING_JSLIKE_H

#define $init$ = newEmptyString()
#define LITERAL(c) newLiteralString(c, (String*) alloca(sizeof(string)))

typedef struct String {
  uint64_t length;
  uint64_t size;
  size_t len;
  char *c_str;
} String;
typedef String *string;

string newEmptyString();
string newSizedString(uint64_t size);
string newLiteralString(char *c, string str);

void deleteString(string str);
string freeAssign(string *dest, string src);

// Methods & prototype methods.
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

#endif //CSTRING_JSLIKE_CSTRING_JSLIKE_H

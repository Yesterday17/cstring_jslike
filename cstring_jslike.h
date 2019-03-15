//
// Created by t on 3/15.
//

#include <stdint.h>

#ifndef CSTRING_JSLIKE_CSTRING_JSLIKE_H
#define CSTRING_JSLIKE_CSTRING_JSLIKE_H

#define $init$ = newEmptyString()
#define STRING(c) newString(c)

struct String;
typedef struct String *string;

typedef struct String {
  uint64_t length;
  uint64_t size;
  char *c_str;
} String;

string newEmptyString();
string newSizedString(uint64_t size);
string newString(char *c);

void deleteString(string str);
string freeAssign(string* dest, string src);

string fromCharCode(uint64_t count, ...);
char charAt(string str, int index);
string concat(uint64_t count, ...);
string concat2(string a, string b);

#endif //CSTRING_JSLIKE_CSTRING_JSLIKE_H

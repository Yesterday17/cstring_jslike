//
// Created by t on 3/15.
//

#include <stdint.h>
#include <stdbool.h>

#ifndef CSTRING_JSLIKE_CSTRING_JSLIKE_H
#define CSTRING_JSLIKE_CSTRING_JSLIKE_H

#define $init$ = newEmptyString()
#define STRING(c) newString(c)
// FIXME: Sting literal causing memory leak.

typedef struct String {
  uint64_t length;
  uint64_t size;
  char *c_str;
} String;
typedef String *string;

string newEmptyString();
string newSizedString(uint64_t size);
string newString(char *c);

void deleteString(string str);
string freeAssign(string *dest, string src);

// Methods & prototype methods.
string fromCharCode(uint64_t count, ...);
char charAt(string str, uint64_t index);
int charCodeAt(string str, uint64_t index);
string concat(uint64_t count, ...);
bool endsWith(string src, string search, uint64_t length);

// Help methods
string concat2(string a, string b);
bool endsWithT(string src, string search);

#endif //CSTRING_JSLIKE_CSTRING_JSLIKE_H

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

typedef struct StringPrototype {
  string (*charCodeAt)(uint64_t , ...);
  string (*concat2)(string, string);
} StringPrototype;

typedef struct String {
  char *c_str;
  uint64_t length;
} String;

extern StringPrototype STRING_PROTOTYPE;

string newEmptyString();
string newSizedString(uint64_t size);
string newString(char *c);

#endif //CSTRING_JSLIKE_CSTRING_JSLIKE_H

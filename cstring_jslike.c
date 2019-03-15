//
// Created by t on 3/15.
//
#include "cstring_jslike.h"
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#define STRING_START_SIZE 16

/**
 * The fromCharCode() method returns a string created from the specified sequence of ASCII code units.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/fromCharCode
 * @param count The number of units.
 * @param ... Units.
 * @return A string contains the units.
 */
// TODO: Implement UTF-16 code units.
string fromCharCode(uint64_t count, ...) {
  string str = newSizedString(count);

  va_list args;
  va_start(args, count);
  for (int i = 0; i < count; i++) {
    int character = va_arg(args, int);
    str->c_str[i] = (char) character;
  }
  va_end(args);

  str->length = count;
  return str;
}

string concat2(string a, string b) {
  string ans = newSizedString(a->length + b->length);
  memcpy(ans->c_str, a->c_str, a->length);
  memcpy(ans->c_str + a->length, b->c_str, b->length);

  ans->length = a->length + b->length;
  return ans;
}

string concat(uint64_t count, ...) {
  string str = newEmptyString();
  uint64_t length = 0;

  va_list args;
  va_start(args, count);
  for (int i = 0; i < count; i++) {
    string str2 = va_arg(args, string);
    length += str->length;
    freeAssign(&str, concat2(str, str2));
  }
  va_end(args);

  str->length = length;
  return str;
}

/**
 * https://stackoverflow.com/questions/466204/rounding-up-to-next-power-of-2
 */
uint64_t findNext2Exp(uint64_t v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

/**
 * Initialize a string with STRING_START_SIZE.
 * @return An empty string.
 */
string newEmptyString() {
  string str = (String *) malloc(sizeof(String));
  str->c_str = (char *) malloc(sizeof(char) * STRING_START_SIZE);
  memset(str->c_str, '\0', STRING_START_SIZE);
  str->length = 0;
  return str;
}

/**
 * Initialize a string with size needed.
 * @param size The size.
 * @return A string with size.
 */
string newSizedString(uint64_t size) {
  if (size < STRING_START_SIZE) return newEmptyString();

  uint64_t next = findNext2Exp(size);
  if (next == size) {
    next = findNext2Exp(size + 1);
  }

  string str = (String *) malloc(sizeof(String));
  str->c_str = (char *) malloc(sizeof(char) * next);
  memset(str->c_str, '\0', STRING_START_SIZE);

  return str;
}

/**
 * Initialize a string from c_str.
 * @param c The c_str.
 * @return A string initialized with c.
 */
string newString(char *c) {
  string str = newEmptyString();
  strcpy(str->c_str, c);
  str->length = strlen(str->c_str);
  return str;
}

/**
 * Delete a string.
 * @param str The string
 */
void deleteString(string str) {
  free(str->c_str);
  free(str);
}

/**
 * Assign a string and free the previous one.
 * @param dest The string to free & assign.
 * @param src The string to be assigned.
 * @return (Optional) The string assigned.
 */
string freeAssign(string *dest, string src) {
  deleteString(*dest);
  *dest = src;
  return *dest;
}
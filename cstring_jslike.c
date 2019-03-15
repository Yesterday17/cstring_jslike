//
// Created by t on 3/15.
//
#include "cstring_jslike.h"
#include <malloc.h>
#include <stdarg.h>
#include <string.h>

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

/**
 * The String's charAt() method returns a char consisting of the single ASCII code unit located at the specified offset into the string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/charAt
 * @param str
 * @param index
 * @return A character at index, or 0 on error.
 */
// TODO: Implement UTF-16 code unit.
char charAt(string str, uint64_t index) {
  if (index >= 0 && index <= str->length - 1) {
    return str->c_str[index];
  } else {
    return 0;
  }
}

/**
 * The charCodeAt() method returns an integer between 0 and 65535 representing the ASCII code unit at the given index.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/charCodeAt
 * @param str
 * @param index
 * @return
 */
// TODO: Implement UTF-16 code unit.
int charCodeAt(string str, uint64_t index) {
  return charAt(str, index);
}

// TODO: charPointAt

/**
 * The concat() method concatenates the string arguments to the calling string and returns a new string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/concat
 * @param count The number of strings to concat.
 * @param ... The strings to concat.
 * @return A new string.
 */
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
 * The endsWith() method determines whether a string ends with the characters of a specified string, returning true or false as appropriate.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/endsWith
 * @param src
 * @param search
 * @param length
 * @return
 */
bool endsWith(string src, string search, uint64_t length) {
  bool match = true;
  if (src->length < length) {
    length = src->length;
  }

  for (int i = 0; i < search->length; i++) {
    if (charAt(src, length - 1 - i) != charAt(search, search->length - 1 - i)) {
      return false;
    }
  }

  return true;
}

bool endsWithT(string src, string search) {
  return endsWith(src, search, src->length);
}

string concat2(string a, string b) {
  string ans = newSizedString(a->length + b->length);
  memcpy(ans->c_str, a->c_str, a->length);
  memcpy(ans->c_str + a->length, b->c_str, b->length);

  ans->length = a->length + b->length;
  return ans;
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
  str->size = STRING_START_SIZE - 1;
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
  memset(str->c_str, '\0', next);

  str->length = 0;
  str->size = next - 1;
  return str;
}

/**
 * Initialize a string from c_str.
 * @param c The c_str.
 * @return A string initialized with c.
 */
string newString(char *c) {
  string str = (String *) malloc(sizeof(String));

  str->length = strlen(c);
  str->size = str->length;

  str->c_str = (char *) malloc(sizeof(char) * (str->length + 1));
  strcpy(str->c_str, c);
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
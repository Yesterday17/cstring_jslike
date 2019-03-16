//
// Created by Yesterday17 on 3/15.
//
#include "cstring_jslike.h"
#include <stdarg.h>
#include <string.h>

#ifndef _WIN32
#include <iconv.h>
#else
#include <windows.h>
#endif

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
  uint64_t length = 0, len = 0;

  va_list args;
  va_start(args, count);
  for (int i = 0; i < count; i++) {
    string str2 = va_arg(args, string);
    length += str->length;
    len += str->len;
    freeAssign(&str, concat2(str, str2));
  }
  va_end(args);

  str->length = length;
  str->len = len;
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
// TODO: Make endsWith UTF-8 compatible
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

/**
 * The String's charAtU() method returns a string consisting of the UTF-8 code unit located at the specified offset into the UTF-8 string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/charAt
 * @param str
 * @param index
 * @return A character at index, or 0 on error.
 */
string charAtU(string str, uint64_t index) {
  string result = newSizedString(5);
  uint64_t size = 1;
  if (index >= 0 && index < length(str)) {
    int i, j;
    for (i = 0; i <= index; i++) {
      unsigned char c = (unsigned char) str->c_str[i];
      if (c >= 0 && c <= 127) i += 0, size = 1;
      else if ((c & 0xE0) == 0xC0) i += 1, size = 2;
      else if ((c & 0xF0) == 0xE0) i += 2, size = 3;
      else if ((c & 0xF8) == 0xF0) i += 3, size = 4;
    }
    for (j = 0; j < size; i++, j++) {
      result->c_str[j] = str->c_str[i];
    }
    result->c_str[j] = '\0';
    result->length = size;
  }

  return result;
}

string concat2(string a, string b) {
  string ans = newSizedString(a->length + b->length);
  memcpy(ans->c_str, a->c_str, a->length);
  memcpy(ans->c_str + a->length, b->c_str, b->length);

  ans->length = a->length + b->length;
  return ans;
}

bool endsWithT(string src, string search) {
  return endsWith(src, search, src->length);
}

/**
 * Calculate the length of a UTF-8 string.
 * @param src The UTF-8 string.
 * @return The actual length of the string.
 */
size_t length(string src) {
  size_t size = 0;
  for (int i = 0; i < src->length; i++) {
    unsigned char c = (unsigned char) src->c_str[i];
    if (c >= 0 && c <= 127) i += 0;
    else if ((c & 0xE0) == 0xC0) i += 1;
    else if ((c & 0xF0) == 0xE0) i += 2;
    else if ((c & 0xF8) == 0xF0) i += 3;
    else return 0;
    size++;
  }
  return size;
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
  str->len = 0;
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
  str->len = length(str);
  return str;
}

/**
 * Initialize a literal string from c_str
 *
 * <b>Please do not call this function directly</b>
 * @param c The c_str
 * @param mem memory allocated on stack
 * @return
 */
string newLiteralString(char *c, string str, bool copy) {
  str->length = strlen(c);
  str->size = str->length;

  if (copy) {
    str->c_str = (char *) malloc(sizeof(char) * str->length);
    strcpy(str->c_str, c);
  } else {
    str->c_str = c;
  }
  str->len = length(str);
  return str;
}

/**
 * Delete a string.
 *
 * The string **MUST NOT** be created by string literal
 * WHICH MAY CAUSE **SEGMENTATION FAULT**
 * (as it's allocated by alloca, and trying to free stack memory causes segmentation fault)
 *
 * @param str The string to delete.
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
  if (*dest != src) {
    deleteString(*dest);
    *dest = src;
  }
  return *dest;
}

#ifndef _WIN32
char *stringToGBK(string str) {
  char *result = (char *) malloc(sizeof(char) * str->length), *out_buf = result;
  memset(result, 0, str->length);

  size_t in_len = str->length, out_len = str->length;
  char *in_buf = str->c_str;

  iconv_t cd = iconv_open("GBK", "UTF-8");
  if (cd != (iconv_t) - 1) {
    if (iconv(cd, &in_buf, &in_len, &out_buf, &out_len) == 0) {
      iconv_close(cd);
    }
  }
  return result;
}
#else
char *stringToGBK(string str) {
  char *src = str->c_str, *result = (char *) malloc(sizeof(char) * str->length);

  WCHAR *w_str;
  int i = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
  if (i > 0) {
    w_str = (WCHAR *) malloc((size_t) i * 2);
    MultiByteToWideChar(CP_UTF8, 0, src, -1, w_str, i);
    i = WideCharToMultiByte(CP_ACP, 0, w_str, -1, NULL, 0, NULL, NULL);
    if (str->length >= i) {
      WideCharToMultiByte(CP_ACP, 0, w_str, -1, result, i, NULL, NULL);
      result[i] = 0;
    }
    free(w_str);
  }

  return result;
}
#endif
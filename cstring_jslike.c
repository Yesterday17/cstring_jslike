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

//////////////////////////////////////////////////////////////////
/// Basic Utilities
//////////////////////////////////////////////////////////////////
uint8_t compareString(string str1, string str2) {
  if (str1->length != str2->length) return false;
  if (str1->len != str2->len) return false;
  for (int i = 0; i < str1->length; i++) {
    if (STR(str1)[i] > STR(str2)[i]) {
      return STRING_LARGER;
    } else if (STR(str1)[i] < STR(str2)[i]) {
      return STRING_SMALLER;
    }
  }
  return STRING_EQUAL;
}

//////////////////////////////////////////////////////////////////
/// Methods & prototype methods
//////////////////////////////////////////////////////////////////

/**
 * The fromCharCode() method returns a string created from the specified sequence of ASCII code units.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/fromCharCode
 * @param count The number of units.
 * @param ...
 * @return
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
char charAt(string str, size_t index) {
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
int charCodeAt(string str, size_t index) {
  return charAt(str, index);
}

// TODO: charPointAt

/**
 * The concat() method concatenates the string arguments to the calling string and returns a new string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/concat
 * @param count The number of strings to concat.
 * @param ... The strings to concat.
 * @return
 */
string concat(uint64_t count, ...) {
  string str = newEmptyString();
  size_t length = 0, len = 0;

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
bool endsWith(string src, string search, size_t length) {
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
 * The includes() method determines whether one string may be found within another string, returning true or false as appropriate.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/includes
 * @param src
 * @param pattern
 * @return
 */
bool includes(string src, string pattern) {
  return (strstr(STR(src), STR(pattern)) != NULL);
}

/**
 * The indexOf() method returns the index within the calling String of the first occurrence of the specified value, starting the search at fromIndex.
 * Returns its length if the value is not found.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/indexOf
 * @param str
 * @param pattern
 * @param from
 * @return
 */
size_t indexOf(string str, string pattern, size_t from) {
  char *occur = strstr(STR(str) + from, STR(pattern));
  if (occur != NULL) {
    return occur - STR(str);
  } else {
    return str->length;
  }
}

//////////////////////////////////////////////////////////////////
/// UTF-8 Methods
//////////////////////////////////////////////////////////////////

/**
 * The String's charAtU() method returns a string consisting of the UTF-8 code unit located at the specified offset into the UTF-8 string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/charAt
 * @param str
 * @param index
 * @return A character at index, or 0 on error.
 */
string charAtU(string str, size_t index) {
  string result = newSizedString(5);
  size_t size = ucharSize(str, 0);
  if (index >= 0 && index < str->len) {
    size_t offset = 0, j;
    for (int i = 0; i < index; i++) {
      size = ucharSize(str, offset);
      offset += size;
    }
    for (j = 0; j < size; offset++, j++) {
      result->c_str[j] = str->c_str[offset];
    }
    result->c_str[offset] = '\0';
    result->length = size;
    result->len = length(result);
  }
  return result;
}

/**
 * The endsWithU() method determines whether a string ends with the characters of a specified UTF-8 string, returning true or false as appropriate.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/endsWith
 * @param src
 * @param search
 * @param length
 * @return
 */
bool endsWithU(string src, string search, size_t len) {
  if (src->length < len) {
    len = src->length;
  }

  for (int i = 0; i < search->len; i++) {
    if (compareString(charAtU(src, len - 1 - i), charAtU(search, search->len - 1 - i)) != STRING_EQUAL) {
      return false;
    }
  }
  return true;
}

//////////////////////////////////////////////////////////////////
/// Help Methods
//////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////
/// UTF-8 Help Methods
//////////////////////////////////////////////////////////////////

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
 * Get the size of UTF-8 character at current offset
 * @param str
 * @param offset
 * @return
 */
uint8_t ucharSize(string str, size_t offset) {
  if (offset >= str->length) return 0;
  while (true) {
    unsigned char c = (unsigned char) str->c_str[offset];
    if ((c >> 7) == 0b0) {
      return 1;
    } else if (c >> 6 == 0b10) {
      offset--;
    } else if (c >> 5 == 0b110) {
      return 2;
    } else if (c >> 4 == 0b1110) {
      return 3;
    } else if (c >> 3 == 0b11110) {
      return 4;
    }
  }
}

bool endsWithTU(string src, string search) {
  return endsWithU(src, search, src->len);
}

/**
 * https://stackoverflow.com/questions/466204/rounding-up-to-next-power-of-2
 */
size_t findNext2Exp(size_t v) {
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
string newSizedString(size_t size) {
  if (size < STRING_START_SIZE) return newEmptyString();

  size_t next = findNext2Exp(size);
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
    str->c_str = (char *) malloc(sizeof(char) * str->length + 1);
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

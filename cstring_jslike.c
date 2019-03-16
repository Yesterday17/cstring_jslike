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
/// Help functions
//////////////////////////////////////////////////////////////////

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
 * https://stackoverflow.com/a/8534275
 */
char *strrev(char *str) {
  char *p1, *p2;
  if (!str || !*str)
    return str;
  for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
  }
  return str;
}

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

string reverseString(string str) {
  string rev = newSizedString(str->length);
  strcpy(STR(rev), STR(str));
  strrev(STR(rev));
  return rev;
}

// TODO: Add reverseStringU method

string cloneString(string str) {
  return newLiteralString(STR(str), (String *) malloc(sizeof(String)), true);
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
  if (index <= str->length - 1) {
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
    length += str2->length;
    len += str2->len;
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
 * @param len
 * @return
 */
bool endsWith(string src, string search, size_t len) {
  if (src->length < len) {
    len = src->length;
  }

  for (int i = 0; i < search->length; i++) {
    if (charAt(src, len - 1 - i) != charAt(search, search->length - 1 - i)) {
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

/**
 * The lastIndexOf() method returns the index within the calling String object of the last occurrence of the specified value, searching backwards from fromIndex.
 * Returns length if the value is not found.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/lastIndexOf
 * @param str
 * @param pattern
 * @param from
 * @return
 */
size_t lastIndexOf(string str, string pattern, size_t from) {
  string r_str = reverseString(str), r_pattern = reverseString(pattern);
  size_t index = indexOf(r_str, r_pattern, from);
  deleteString(r_str);
  deleteString(r_pattern);
  return str->length - index - 1;
}

/**
 * The padEnd() method pads the current string with a given string (repeated, if needed) so that the resulting string reaches a given length.
 * The padding is applied from the end (right) of the current string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/padEnd
 * @param str
 * @param len
 * @param toPad
 * @return
 */
// TODO: Implement padEndU
string padEnd(string str, size_t len, string toPad) {
  if (str->length >= len) return cloneString(str);
  string result = newSizedString(len);
  memcpy(STR(result), STR(str), str->length);

  for (size_t offset = str->length; offset < len; offset += toPad->length) {
    memcpy(STR(result) + offset,
           STR(toPad),
           offset + toPad->length > len ? len - offset : toPad->length);
  }

  result->length = len;
  result->len = length(result);
  return result;
}

/**
 * The padStart() method pads the current string with another string (multiple times, if needed) until the resulting string reaches the given length.
 * The padding is applied from the start (left) of the current string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/padStart
 * @param str
 * @param len
 * @param toPad
 * @return
 */
// TODO: Implement padStartU
string padStart(string str, size_t len, string toPad) {
  if (str->length >= len) return cloneString(str);
  string result = newSizedString(len);
  memcpy(STR(result) + len - str->length, STR(str), str->length);

  for (size_t offset = 0; offset < len - str->length; offset += toPad->length) {
    memcpy(STR(result) + offset,
           STR(toPad),
           offset + toPad->length > len - str->length ? len - offset - str->length : toPad->length);
  }

  result->length = len;
  result->len = length(result);
  return result;
}

/**
 * The repeat() method constructs and returns a new string which contains the specified number of copies of the string on which it was called, concatenated together.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/repeat
 * @param str
 * @param times
 * @return
 */
string repeat(string str, size_t times) {
  string result = newSizedString(str->length * times);
  for (size_t i = 0; i < times; i++) {
    memcpy(STR(result) + str->length * i, STR(str), str->length);
  }
  result->length = times * str->length;
  result->len = times * str->len;
  return result;
}

/**
 * The slice() method extracts a section of a string and returns it as a new string, without modifying the original string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/slice
 * @param str
 * @param beginSlice
 * @param endSlice
 * @return
 */
// TODO: Implement sliceU
string slice(string str, int64_t beginSlice, int64_t endSlice) {
  if (beginSlice < 0) beginSlice = str->length + beginSlice;
  if (beginSlice < 0) beginSlice = 0;
  if (endSlice < 0) endSlice = str->length + endSlice;
  if (endSlice >= str->length) endSlice = str->length;
  if (beginSlice >= str->length || endSlice < 0 || beginSlice >= endSlice)
    return newEmptyString();

  size_t len = (size_t) (endSlice - beginSlice);
  string result = newSizedString(len);
  memcpy(STR(result), STR(str) + beginSlice, len);

  result->length = len;
  result->len = length(result);
  return result;
}

/**
 * The split() method splits a String into an array of strings by separating the string into substrings, using a specified separator string to determine where to make each split.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/split
 * @param str
 * @param separator
 * @param array
 * @return
 */
size_t split(string str, string separator, string **array) {
  size_t count = 1, index_previous = 0, index = 0, i = 0;
  if (separator->length == 0) {
    *array = NULL;
    return 0;
  }
  for (index = 0; index = indexOf(str, separator, index) + 1, index < str->length; count++);

  *array = malloc(sizeof(String) * count);
  for (index = 0; i < count; i++, index_previous = index) {
    size_t len;
    if (i != count - 1) {
      index = indexOf(str, separator, index) + separator->length;
      len = index - index_previous - separator->length;
    } else {
      index = str->length;
      len = index - index_previous;
    }

    string s = newSizedString(len);
    memcpy(STR(s), STR(str) + index_previous, len);
    s->length = len;
    s->len = length(s);
    (*array)[i] = s;
  }

  return count;
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
  if (index < str->len) {
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

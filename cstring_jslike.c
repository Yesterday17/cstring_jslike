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
// FIXME: Not compatible for UTF-8
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
  if (str1->unitCnt != str2->unitCnt) return false;
  if (str1->length != str2->length) return false;
  for (int i = 0; i < str1->unitCnt; i++) {
    if (U8_CSTR(str1)[i] > U8_CSTR(str2)[i]) {
      return STRING_LARGER;
    } else if (U8_CSTR(str1)[i] < U8_CSTR(str2)[i]) {
      return STRING_SMALLER;
    }
  }
  return STRING_EQUAL;
}

// FIXME: Not compatible for UTF-8
stringbuf reverseString(string str) {
  stringbuf rev = newSizedString(str->unitCnt);
  strcpy(U8_CSTR(rev), U8_CSTR(str));
  strrev(U8_CSTR(rev));
  return rev;
}

// TODO: Add reverseStringU method

stringbuf cloneString(string str) {
  return newLiteralString(U8_CSTR(str), (String *) malloc(sizeof(String)), (char*) malloc(sizeof(str->unitCnt)));
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
stringbuf fromCharCode(uint64_t count, ...) {
  stringbuf str = newSizedString(count);

  va_list args;
  va_start(args, count);
  for (int i = 0; i < count; i++) {
    int character = va_arg(args, int);
    str->c_str[i] = (char) character;
  }
  va_end(args);

  str->unitCnt = count;
  str->length = length(str);
  return str;
}

/**
 * The String's charAt() method returns a char consisting of the single ASCII code unit located at the specified offset into the string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/charAt
 * @param str
 * @param index
 * @return A char pointer of character(GBK) at index, or NULL on error.
 */
// TODO: Implement UTF-16 code unit.
// FIXME: Memory leak problem
char* charAt(string str, size_t index) {
  string u8Char = charAtU(str, index);
  if (u8Char == NULL)
    return NULL;
  return CSTR(u8Char);
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
  if (index <= str->unitCnt - 1) {
    return str->c_str[index];
  } else {
    return 0;
  }
}

// TODO: charPointAt

/**
 * The concat() method concatenates the string arguments to the calling string and returns a new string.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/concat
 * @param count The number of strings to concat.
 * @param ... The strings to concat.
 * @return
 */
stringbuf concat(uint64_t count, ...) {
  stringbuf str = newEmptyString();
  size_t unitCnt = 0, length = 0;

  va_list args;
  va_start(args, count);
  for (int i = 0; i < count; i++) {
    string str2 = va_arg(args, string);
    unitCnt += str2->unitCnt;
    length += str2->length;
    freeAssign(&str, concat2(str, str2));
  }
  va_end(args);

  str->unitCnt = unitCnt;
  str->length = length;
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
  if (src->unitCnt < len) {
    len = src->unitCnt;
  }

  for (int i = 0; i < search->unitCnt; i++) {
    if (charCodeAt(src, len - 1 - i) != charCodeAt(search, search->unitCnt - 1 - i)) {
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
  return (strstr(U8_CSTR(src), U8_CSTR(pattern)) != NULL);
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
  char *occur = strstr(U8_CSTR(str) + from, U8_CSTR(pattern));
  if (occur != NULL) {
    return occur - U8_CSTR(str);
  } else {
    return str->unitCnt;
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
  stringbuf r_str = reverseString(str), r_pattern = reverseString(pattern);
  size_t index = indexOf(r_str, r_pattern, from);
  deleteString(r_str);
  deleteString(r_pattern);
  return str->unitCnt - index - 1;
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
stringbuf padEnd(string str, size_t len, string toPad) {
  if (str->unitCnt >= len) return cloneString(str);
  stringbuf result = newSizedString(len);
  memcpy(U8_CSTR(result), U8_CSTR(str), str->unitCnt);

  for (size_t offset = str->unitCnt; offset < len; offset += toPad->unitCnt) {
    memcpy(U8_CSTR(result) + offset,
           U8_CSTR(toPad),
           offset + toPad->unitCnt > len ? len - offset : toPad->unitCnt);
  }

  result->unitCnt = len;
  result->length = length(result);
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
stringbuf padStart(string str, size_t len, string toPad) {
  if (str->unitCnt >= len) return cloneString(str);
  stringbuf result = newSizedString(len);
  memcpy(U8_CSTR(result) + len - str->unitCnt, U8_CSTR(str), str->unitCnt);

  for (size_t offset = 0; offset < len - str->unitCnt; offset += toPad->unitCnt) {
    memcpy(U8_CSTR(result) + offset,
           U8_CSTR(toPad),
           offset + toPad->unitCnt > len - str->unitCnt ? len - offset - str->unitCnt : toPad->unitCnt);
  }

  result->unitCnt = len;
  result->length = length(result);
  return result;
}

/**
 * The repeat() method constructs and returns a new string which contains the specified number of copies of the string on which it was called, concatenated together.
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/repeat
 * @param str
 * @param times
 * @return
 */
stringbuf repeat(string str, size_t times) {
  stringbuf result = newSizedString(str->unitCnt * times);
  for (size_t i = 0; i < times; i++) {
    memcpy(U8_CSTR(result) + str->unitCnt * i, U8_CSTR(str), str->unitCnt);
  }
  result->unitCnt = times * str->unitCnt;
  result->length = times * str->length;
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
stringbuf slice(string str, int64_t beginSlice, int64_t endSlice) {
  if (beginSlice < 0) beginSlice = str->unitCnt + beginSlice;
  if (beginSlice < 0) beginSlice = 0;
  if (endSlice < 0) endSlice = str->unitCnt + endSlice;
  if (endSlice >= str->unitCnt) endSlice = str->unitCnt;
  if (beginSlice >= str->unitCnt || endSlice < 0 || beginSlice >= endSlice)
    return newEmptyString();

  size_t unitCnt = (size_t) (endSlice - beginSlice);
  stringbuf result = newSizedString(unitCnt);
  memcpy(U8_CSTR(result), U8_CSTR(str) + beginSlice, unitCnt);

  result->unitCnt = unitCnt;
  result->length = length(result);
  return result;
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
 // FIXME: Memory leak problem
 stringbuf charAtU(string str, size_t index) {
  stringbuf result = newSizedString(5);
  size_t size = ucharSize(str, 0);
  if (index < str->length) {
    size_t offset = 0, j;
    for (int i = 0; i < index; i++) {
      size = ucharSize(str, offset);
      offset += size;
    }
    for (j = 0; j < size; offset++, j++) {
      result->c_str[j] = str->c_str[offset];
    }
    result->c_str[offset] = '\0';
    result->unitCnt = size;
    result->length = length(result);
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
  if (src->unitCnt < len) {
    len = src->unitCnt;
  }

  for (int i = 0; i < search->length; i++) {
    if (compareString(charAtU(src, len - 1 - i), charAtU(search, search->length - 1 - i)) != STRING_EQUAL) {
      return false;
    }
  }
  return true;
}

//////////////////////////////////////////////////////////////////
/// Help Methods
//////////////////////////////////////////////////////////////////

stringbuf concat2(string a, string b) {
  stringbuf ans = newSizedString(a->unitCnt + b->unitCnt);
  memcpy(ans->c_str, a->c_str, a->unitCnt);
  memcpy(ans->c_str + a->unitCnt, b->c_str, b->unitCnt);

  ans->unitCnt = a->unitCnt + b->unitCnt;
  return ans;
}

/**
 * Default behavior of endWith: Use the actual 'end' of src
 * @param src
 * @param search
 * @return
 */
bool endsWithD(string src, string search) {
  return endsWith(src, search, src->unitCnt);
}

/**
 * Default behavior of padEnd: Use ' '(space) to padEnd
 * @param str
 * @param len
 * @return
 */
stringbuf padEndD(string str, size_t len) {
  return padEnd(str, len, LITERAL(" "));
}

/**
 * Default behavior of padStart: Use ' '(space) to padStart
 * @param str
 * @param len
 * @return
 */
stringbuf padStartD(string str, size_t len) {
  return padStart(str, len, LITERAL(" "));
}

/**
 * Default behavior of slice: Use str->length to fill endSlice
 * @param str
 * @param beginSlice
 * @return
 */
stringbuf sliceD(string str, int64_t beginSlice) {
  return slice(str, beginSlice, str->unitCnt);
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
  for (int i = 0; i < src->unitCnt; i++) {
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
  if (offset >= str->unitCnt) return 0;
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

bool endsWithUD(string src, string search) {
  return endsWithU(src, search, src->length);
}

/**
 * Initialize a string with STRING_START_SIZE.
 * @return An empty string.
 */
stringbuf newEmptyString() {
  stringbuf str = (String *) malloc(sizeof(String));
  str->c_str = (char *) calloc(STRING_START_SIZE, sizeof(char));

  str->unitCnt = 0;
  str->bufSize = STRING_START_SIZE - 1;
  str->length = 0;
  return str;
}

/**
 * Initialize a string with size needed.
 * @param size The size.
 * @return A string with size.
 */
stringbuf newSizedString(size_t size) {
  if (size < STRING_START_SIZE) return newEmptyString();

  size_t next = findNext2Exp(size);
  if (next == size) {
    next = findNext2Exp(size + 1);
  }

  stringbuf str = (String *) malloc(sizeof(String));
  str->c_str = (char *) calloc(next, sizeof(char));

  str->unitCnt = 0;
  str->bufSize = next - 1;
  str->length = 0;
  return str;
}

/**
 * Initialize a string from c_str.
 * @param c The c_str.
 * @return A string initialized with c.
 */
stringbuf newString(char *c) {
  size_t bufSize = strlen(c) + 1;
  return newLiteralString(c, (String *) malloc(sizeof(String)), (char*) malloc(sizeof(char) * bufSize));;
}

/**
 * Initialize a literal string from c_str
 *
 * <b>Please do not call this function directly</b>
 * @param c The c_str
 * @param mem memory allocated on stack
 * @return
 */
string newLiteralString(char *c, string str, char *buf) {
  str->unitCnt = strlen(c);
  str->bufSize = str->unitCnt;

  if (buf != NULL) {
    str->c_str = buf;
    strcpy(str->c_str, c);
  } else {
    str->c_str = c;
  }
  str->length = length(str);
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
void deleteString(stringbuf str) {
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

char *stringToGBK(string str) {
  char *src = str->c_str;
  return cstrToGBK(src, str->unitCnt);
}

#ifndef _WIN32
char *cstrToGBK(char *src, size_t len) {
  char *result = (char *) malloc(sizeof(char) * len), *out_buf = result;
  memset(result, 0, len);

  size_t in_len = len, out_len = len;
  char *in_buf = src;

  iconv_t cd = iconv_open("GBK", "UTF-8");
  if (cd != (iconv_t) - 1) {
    if (iconv(cd, &in_buf, &in_len, &out_buf, &out_len) == 0) {
      iconv_close(cd);
    }
  }
  return result;
}
#else
char *cstrToGBK(char *src, size_t len) {
  char *result = NULL;

  WCHAR *w_str;
  int i = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
  if (i > 0) {
    w_str = (WCHAR *) malloc((size_t) i * sizeof(WCHAR));
    MultiByteToWideChar(CP_UTF8, 0, src, -1, w_str, i);
    i = WideCharToMultiByte(CP_ACP, 0, w_str, -1, NULL, 0, NULL, NULL);
    result = (char *) malloc(sizeof(char) * (i + 1));
    WideCharToMultiByte(CP_ACP, 0, w_str, -1, result, i, NULL, NULL);
    result[i] = 0;
    free(w_str);
  }

  return result;
}
#endif

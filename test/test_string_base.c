//
// Created by KAAAsS on 2019/3/17.
//
#include "unity.h"

#include "../cstring_jslike.h"

#define EQ(a,b) compareString((a), (b)) == STRING_EQUAL

void test_create_string() {
  string test = LITERAL("Test");
  TEST_ASSERT_MESSAGE(test != NULL, "String is not created.");

  stringbuf testBuf = STR_BUF("TestBuf");
  TEST_ASSERT_MESSAGE(testBuf != NULL, "String is not created.");
  $STR_BUF(testBuf);
}

void test_compareString() {
  string asciiA = LITERAL("AB");
  string asciiB = LITERAL("ABC");
  string asciiC = LITERAL("ABD");
  string u8A = LITERAL("在吗");
  string u8B = LITERAL("在吗？");
  string inte = LITERAL("在吗？buzai, cnm");

  TEST_ASSERT_EQUAL_INT(STRING_SMALLER, compareString(asciiA, asciiB));
  TEST_ASSERT_EQUAL_INT(STRING_SMALLER, compareString(asciiB, asciiC));
  TEST_ASSERT_EQUAL_INT(STRING_EQUAL, compareString(asciiA, asciiA));
  TEST_ASSERT_EQUAL_INT(STRING_LARGER, compareString(asciiB, asciiA));
  TEST_ASSERT_EQUAL_INT(STRING_LARGER, compareString(asciiC, asciiB));
  TEST_ASSERT_EQUAL_INT(STRING_EQUAL, compareString(u8A, u8A));
  TEST_ASSERT_EQUAL_INT(STRING_EQUAL, compareString(inte, inte));
  TEST_ASSERT_EQUAL_INT(STRING_SMALLER, compareString(u8A, u8B));
  TEST_ASSERT_EQUAL_INT(STRING_LARGER, compareString(inte, u8B));
}

void test_reverseString() {
  TEST_ASSERT(EQ(LITERAL("abcde"), LITERAL("edcba")));
  TEST_ASSERT(EQ(LITERAL("1919"), LITERAL("9191")));
  // TODO: Add test case for UTF-8 string
}

void test_cloneString() {
  string orgStr = LITERAL("Origin");
  stringbuf newStr = cloneString(orgStr);
  TEST_ASSERT(orgStr != newStr);
  TEST_ASSERT(EQ(orgStr, newStr));
  $STR_BUF(newStr);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_create_string);
  RUN_TEST(test_compareString);
  RUN_TEST(test_reverseString);
  RUN_TEST(test_cloneString);

  return UNITY_END();
}

//
// Created by KAAAsS on 2019/3/17.
//
#include "unity.h"

#include "../cstring_jslike.h"

#define EQ(a,b) compareString((a), (b)) == STRING_EQUAL

void test_create_string() {
  string test = LITERAL("Test");
  TEST_ASSERT_MESSAGE(test != NULL, "String is not created.");
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

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_create_string);
  RUN_TEST(test_compareString);

  return UNITY_END();
}

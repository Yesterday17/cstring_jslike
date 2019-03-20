//
// Created by guyis on 2019/3/18.
//
#include "common.h"

void test_charAtU() {
  string str = LITERAL("贴，都可以贴");
  TEST_ASSERT_EQUAL(true, EQ(LITERAL("贴"), charAtU(str, 0)));
  TEST_ASSERT_EQUAL(false, EQ(LITERAL("贴"), charAtU(str, 1)));
  TEST_ASSERT_EQUAL(true, EQ(LITERAL("都"), charAtU(str, 2)));
  TEST_ASSERT_EQUAL(true, EQ(LITERAL("贴"), charAtU(str, 5)));
}

void test_length() {
  string ascii = LITERAL("AB");
  string u8 = LITERAL("在吗");
  string inte = LITERAL("在吗？buzai, cnm");
  TEST_ASSERT_EQUAL_INT(2, length(ascii));
  TEST_ASSERT_EQUAL_INT(2, length(u8));
  TEST_ASSERT_EQUAL_INT(13, length(inte));
}

void test_ucharSize() {
  string str = LITERAL("Aα啊🍋");
  TEST_ASSERT_EQUAL_INT(1, ucharSize(str, 0));
  TEST_ASSERT_EQUAL_INT(2, ucharSize(str, 1));
  TEST_ASSERT_EQUAL_INT(3, ucharSize(str, 3));
  TEST_ASSERT_EQUAL_INT(4, ucharSize(str, 6));
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_charAtU);
  RUN_TEST(test_length);
  RUN_TEST(test_ucharSize);

  return UNITY_END();
}

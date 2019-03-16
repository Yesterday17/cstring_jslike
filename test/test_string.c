//
// Created by KAAAsS on 2019/3/17.
//
#include "unity.h"

#include "../cstring_jslike.h"

void test_create_string() {
  string test = LITERAL("Test");
  TEST_ASSERT_MESSAGE( test != NULL, "String is not created." );
}

int main () {
  UNITY_BEGIN();

  RUN_TEST(test_create_string);

  return UNITY_END();
}

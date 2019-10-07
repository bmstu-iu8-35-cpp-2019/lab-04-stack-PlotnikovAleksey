// Copyright 2019 Plotnikov Aleksey <alex280201@gmail.com>

#include <gtest/gtest.h>
#include <header.hpp>
#include <type_traits>
#include <string>

TEST(Stack, task1) {
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>());
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>());
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>());
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>());

  Stack<int> s1;
  s1.push(10);
  s1.push(-10);
  s1.push(2);
  int USED_VARIABLE = 3;

  EXPECT_EQ(s1.head(), 2);

  s1.pop();

  EXPECT_EQ(s1.head(), -10);

  Stack<int> move_s1(std::move(s1));

  EXPECT_EQ(move_s1.head(), -10);
  EXPECT_THROW(USED_VARIABLE = s1.head(), std::logic_error);

  auto s2 = std::move(move_s1);

  EXPECT_EQ(s2.head(), -10);
  EXPECT_THROW(USED_VARIABLE = move_s1.head(), std::logic_error);
}

TEST(Stack, task2) {
  Stack<std::string> s;
  std::string USED_VARIABLE = "1";
  s.push_emplace("str");
  s.push_emplace("strstr");
  s.push_emplace("strstrstr");

  EXPECT_EQ(s.head(), "strstrstr");
  EXPECT_EQ(s.pop(0), "strstrstr");
  EXPECT_EQ(s.head(), "strstr");

  Stack<std::string> moved_s(std::move(s));

  EXPECT_EQ(moved_s.head(), "strstr");
  EXPECT_THROW(USED_VARIABLE = s.head(), std::logic_error);
}

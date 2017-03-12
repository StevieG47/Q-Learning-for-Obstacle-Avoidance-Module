#include <gtest/gtest.h>
#include "../include/QLearn.h"

/*
TEST(dummy, should_pass) {
  EXPECT_EQ(1, 1);
}
 */

TEST(QTest,findState) {
  robot Test;
  EXPECT_EQ(Test.findState(0, 0), 0);  //check if finding state correctly
}

TEST(QTest,decideAction) {
  robot Test;
  EXPECT_LT(Test.decideAction(1), 3);
  EXPECT_GT(Test.decideAction(1), -1);  //check if deciding relevant action
}

TEST(QTest,assignReward) {
  robot Test;
  EXPECT_EQ(Test.assignReward(0, false), 10);  //check if assigning reward correctly
}

TEST(QTest,maxFuture) {
  robot Test;
  Test.Q[1][1] = 55;
  EXPECT_EQ(Test.maxFuture(1), 55);  //check if computing max Future value correctly
}

TEST(QTest,updateTable) {
  robot Test;
  Test.Q;
  Test.updateTable(0, 0, false, 0);
  EXPECT_EQ(Q[0][0], 5);  //check if computing max Future value correctly
}


/* MIT License
 Copyright (c) 2017 Steven Gambino
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 * @copyright Copyright 2017 Steven Gambino
 * @file Qclass.h
 * @author Steven Gambino
 * @brief Header file for Q Learning class
 *
 * For ACME robotics robot with two sensors, three possible actions,
 * this is the header file for the Q Learning class. Functions are defined
 * in Qclass.cpp
 */

#ifndef QCLASS_H_ // NOLINT
#define QCLASS_H_

// Q TABLE
// Q[row][column]
// rows are states, columns are actions
// States: 0 detect nothing, 1 detect right, 2 detect left, 3 detect both (front)
// Actions: 0 move forward, 1 turn left in place, 2 turn right in place


/* @brief
 * Define Q Learning class
 *
 * Class contains everything needed to train a Q table and use it
 * to explore an environment. Actual table given by variable Q.
 */
class Qtable {  // define class
 public:
  int state;
  int action;
  int reward;
  int Q[4][3] = { };
  double alpha;  // equal to .5;
  double gamma;  // equal to .8;

  int findState(int left, int right);  // determine state based on sensors
  int decideAction(int state);  // determine action based on state
  int assignReward(int prevAction, bool crash);  // assign rewards based on what action was taken
  int maxFuture(int state);
  void updateTable(int prevAction, int prevState, bool crash, int state);
  void Train();
  void Perform();
};



#endif /* QCLASS_H_ */ // NOLINT

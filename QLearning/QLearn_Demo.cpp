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
 * @file Qclass.cpp
 * @author Steven Gambino
 * @brief Defines all functions needed to train/use a Q table for robot
 *
 * For ACME robotics robot with two sensors, three possible actions,
 * the functions necessary for the robot to learn to explore while avoiding
 * obstacles are present here. This class' header file in Qclass.h.
 */

#include "QLearn_Demo.h"
#include "HallwayExample.h"
#include <stdlib.h>// NOLINT
#include <iostream>

using std::cout;
using std::endl;



// DETERMINE STATE
/**
 * @brief Determines current state given sensor readings
 * @param int left and right, either 0 or 1 representing 0 for detect nothing and 1 for detect something
 * @return Current state. Either 0,1,2 or 3 depending on sensor combination.
 */
int QDemo::findState(int left, int right) {  // based on sensor value combination find state
  int state = 0;
  if (left == 0 && right == 0) {
    state = 0;
  }
  if (left == 0 && right == 1) {
    state = 1;
  }
  if (left == 1 && right == 0) {
    state = 2;
  }
  if (left == 1 && right == 1) {
    state = 3;
  }
  return state;
}

// DECIDE ACTION
/**
 * @brief Decides an action for the robot to do. Either randomly chosen or chosen with Q table.
 * @param int state. Current state of the robot.
 * @return Action that has been decided. Either 0,1 or 2 since robot only has 3 possible actions.
 */
int QDemo::decideAction(int state) {
  int action;
  int Rand = rand() % 100;

  // 35 percent chance of choosing a random action. Want random action sometimes to explore new possibilities/possible better action
  if (Rand > 65) {
    int randAction = rand() % 3;  // random number between 0 and 2

    action = randAction;
    // cout << "Random action " << action << " was chosen" << endl;  //print we did a random action
    // Use Q table to choose highest rated action for current state, do this most of the time
  } else {
    int bestAction;  // initiate best action var
    int bestQ = -100000;  // initiate best Q value, this corresponds to a state action pair value
    // cout << "Best Q: " << bestQ << endl;
    for (int i = 0; i < 3; i++) {  // cycle through every action for current state
      if (Q[state][i] > bestQ) {  // if state action pair Q value is greater than current best value
        bestQ = Q[state][i];  // set new highest Q value
        bestAction = i;  // set new best action
      }
    }
    // print we used Q table, what we did
    // cout << "Q table used to decide action:" << endl;
    // cout << "For state " << state << ", action " << bestAction << " was chosen."
    //   << endl << endl;
    action = bestAction;
  }
  return action;  // return chosen action
}

// ASSIGN REWARD
/**
 * @brief Assigns a reward for updating the table depending on previous action and if crashed
 * @param int previous action, bool crash. crash = true means previous action caused a crash
 * @return appropriate reward depending on what happened
 */
int QDemo::assignReward(int prevAction, bool crash) {
  int reward;
  if (prevAction == 0) {  // if moved forward reward since we want to explore
    reward = 10;
  }
  if (prevAction == 1 || prevAction == 2) {  // if turn thats neutral, not bad but not exploring
    reward = 0;
  }
  if (crash)  // if crashed give big negative reward
    reward = -100;
  // cout << "Reward " << reward << endl;
  return reward;
}

// FIND MAX FUTURE VALUE
// Need the max future value to update the Q table
/**
 * @brief Finds the max Q value for a given state, used in update equation.
 * @param int state. Current state of the robot.
 * @return Max Q value for the current state (max value of row).
 */
int QDemo::maxFuture(int state) {
  int currentMax = -100000;  // initiate var to keep track of max

  for (int i = 0; i != 3; i++) {  // cycle through every action
    if (Q[state][i] > currentMax)  // if state action pair Q value greater than current Q value
      currentMax = Q[state][i];  // set new max Q value
  }
  return currentMax;
}

// UPDATE Q TABLE
/**
 * @brief Updates the Q table after an action has been taken for a given state
 * Want to update the table based on where robot was, what it did, and where it is now
 * @param int previous state, previous action, state, bool crash, true if crashed
 * @return none
 */
void QDemo::updateTable(int prevAction, int prevState, bool crash, int state) {
  alpha = .5;
  gamma = .8;
  double reward = assignReward(prevAction, crash);  // get the reward based on previous action and if crash
//  cout << "For Q value " << Q[prevState][prevAction] << endl;

  // Update Q value using equation. Based on old Q value, reward, max Q value of new state, and constants alpha, gamma
  if (crash == true) {  // if crash, the new state doesn't count, it crashed
    Q[prevState][prevAction] = Q[prevState][prevAction] + alpha * (reward)
        - Q[prevState][prevAction];
  } else {
  Q[prevState][prevAction] =
      Q[prevState][prevAction]
          + alpha
          * (reward + (gamma * maxFuture(state))
                  - Q[prevState][prevAction]);
    // cout << "Reward  " << reward << endl;
  }
}

// FUNCTION TO TRAIN ROBOT
/**
 * @brief Training the Q table for a given number of iterations
 * @param none
 * @return none
 */
void QDemo::Train() {
  int firstRun = 0;  // Can't update Q table on first run, no previous data to go off of
  int prevState;
  int prevAction;

  // initiate sensors
  int left = 0;
  int right = 0;
  bool crash = false;  // initiate not crashing

  for (int a = 0; a < 1000; a++) {  // number of iterations to train for
    // If the first run has finished use getLeft and getRight to get sensor values
    // Can't use these on first run since they require a previous state and previous action
    if (firstRun > 0) {
      // Get new sensor values based on what previous state and previous action was
      // This is for hallway example, see getSensorValues for details
      left = getLeft(prevState, prevAction);
      right = getRight(prevState, prevAction);
    }
    // print the sensor values
    // cout << "sensorLeft: " << left << endl;
    // cout << "sensorRight: " << right << endl;

    // Determine state based on left and right sensors
    int state = findState(left, right);
    // cout << "state: " << state << endl;

    // CANT UPDATE ON FIRST RUN. IF AFTER THAT UPDATE
    if (firstRun > 0) {
      if ((prevState == 3 && prevAction == 0)
          || (prevState == 1 && prevAction == 0)
          || (prevState == 2 && prevAction == 0)) {  // if something detected and move forward, crash
        crash = true;
      }

      // Update the Q Table based on prevstate, prevaction , and current state
      // cout << endl;
      // cout << "Previous Action: " << prevAction << endl;
      // cout << "Previous state: " << prevState << endl;
      // cout << "Current state: " << state << endl;
      updateTable(prevAction, prevState, crash, state);
    }

    // Decide action based on current state. Picks either random action or uses table to decide
    int action = decideAction(state);

    prevState = state;    // set prevstate = state before next iteration
    prevAction = action;    // same

    firstRun = 1;  // Now that first run complete there are previous values, so we can update the table

    // if crash reset  robot to first position, keep Q table though
    if (crash == true) {
      // cout << "CRASH took place previous stage" << endl;
      crash = false;
      firstRun = 0;    // basically start over if there is a crash
      left = 0;    // give initial sensor values again
      right = 0;
    }
  }
  // PRINT Q TABLE
  cout
      << "Demo for a robot with left/right sensors in a narrow hallway. The available actions of the"

      " robot are move forward, turn 45 deg right in place, and turn 45 deg left in place. Turning"

      " once to the right  will lead to the robot sensing something on the right and nothing on the left."

      " Turning to the right again will lead to the both sensors detecting, since a wall is right in front."
      " The robot will crash if it moves forward while detecting anything, meaning it will only be able to move forward"

      " without crashing by turning until it is parallel with the walls (detecting nothing)."
      << endl;

  cout << endl << "Final Q Table: " << endl;
  cout << " " << Q[0][0] << " " << Q[0][1] << " " << Q[0][2] << endl;
  cout << Q[1][0] << " " << Q[1][1] << " " << Q[1][2] << endl;
  cout << Q[2][0] << " " << Q[2][1] << " " << Q[2][2] << endl;
  cout << Q[3][0] << " " << Q[3][1] << " " << Q[3][2] << endl;
  cout
      << "States: 0. detect nothing, 1, detect right, 2. detect left, 3. detect both."
      << endl;

  cout
      << "Actions: 0. Move forward, 1. turn right in place, 2. turn left in place."
      << endl;

  cout << endl;
  cout
      <<
      "After training, the robot has a best action for each state. For state"
      " 0, detect nothing, the best action is to move forward. For state 1, detect right,"

      " the best action is to turn left. For state 2, detect left, the best action is"
      " to turn right. And for state 3, detect both, the best action is to turn right.";
  cout << endl;
}
// USE Q TABLE TO PERFORM
/**
 * @brief Uses trained Q table to explore environment. Each state always has one corresponding action.
 * @param none
 * @return none
 */
void QDemo::Perform() {
  // initiate sensor values
  int left = 1;
  int right = 1;
  // no previous action/previous state on first run
  int firstRun = 0;
  // initiate prevState, prevAction
  int prevState = 0;
  int prevAction = 0;
  cout << endl << endl << "Performance using Q Table:" << endl;

  for (int a = 0; a < 5; a++) {    // iterate 5 times
    // Get new sensor values based on what previous state and previous action was
    // This is for hallway example, see HallwayExample.h for details
  if (firstRun > 0) {
    left = getLeft(prevState, prevAction);
    right = getRight(prevState, prevAction);
  }

    // Determine state based on left and right sensors
    int state2 = findState(left, right);  // set state with sensor vals

    // Decide action using highest Q table value.
  int bestAction;
  int bestQ = -1000;
    for (int i = 0; i < 3; i++) {  // cycle through every action for current state
      if (Q[state2][i] > bestQ) {  // if state action pair Q value is greater than current best value
        bestQ = Q[state2][i];  // set new highest Q value
        bestAction = i;  // set new best action
    }
  }
    cout << "For state " << state2 << ", action " << bestAction
         << " was taken"
         << endl;
    prevState = state2;  // For next loop
    prevAction = bestAction;
    firstRun = 1;  // done with first run
  }
  cout
      << endl;
  cout
      << "Using the Q table, the robot turns away until it is parallel with the walls"

      " (or detects nothing). It then goes straight."
      << endl;
}






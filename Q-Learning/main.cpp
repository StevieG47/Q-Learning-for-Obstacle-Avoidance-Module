#include "HallwayExample.h"
#include <iostream>
#include <stdlib.h>
#include "QLearn.h"

using std::cout;
using std::endl;

int main() {
  robot Test;      //initiate test var
  int firstRun = 0;  //Can't update Q table on first run, no previous data to go off of
  int prevState;
  int prevAction;

  //initiate sensors
  int left = 0;
  int right = 0;
  bool crash = false;  //initiate not crashing

  for (int a = 0; a < 1000; a++) {  //number of iterations to train for

    //If the first run has finished use getLeft and getRight to get sensor values
    //Can't use these on first run since they require a previous state and previous action
    if (firstRun > 0) {
      //Get new sensor values based on what previous state and previous action was
      //This is for hallway example, see getSensorValues for details
      left = getLeft(prevState, prevAction);
      right = getRight(prevState, prevAction);
    }

    //print the sensor values
    //cout << "sensorLeft: " << left << endl;
    //cout << "sensorRight: " << right << endl;

    //Determine state based on left and right sensors
    int state = Test.findState(left, right);  //set state with sensor vals
    //cout << "state: " << state << endl;

    //CANT UPDATE ON FIRST RUN. IF AFTER THAT UPDATE
    if (firstRun > 0) {
      if ((prevState == 3 && prevAction == 0)
          || (prevState == 1 && prevAction == 0)
          || (prevState == 2 && prevAction == 0)) {  //if something detected and move forward, crash
        crash = true;
      }

      //Update the Q Table based on prevstate, prevaction , and current state
      // cout << endl;
      // cout << "Previous Action: " << prevAction << endl;
      //cout << "Previous state: " << prevState << endl;
      //cout << "Current state: " << state << endl;
      Test.updateTable(prevAction, prevState, crash, state);  //update the Q table

    }

    //Decide action based on current state. Picks either random action or uses table to decide
    int action = Test.decideAction(state);    //decide action based on state

    prevState = state;    //set prevstate = state before next iteration
    prevAction = action;    //same

    firstRun = 1;  //Now that first run complete there are previous values, so we can update the table

    //if crash reset  robot to first position, keep Q table though
    if (crash == true) {
      //cout << "CRASH took place previous stage" << endl;
      crash = false;
      firstRun = 0;    //basically start over if there is a crash
      left = 0;    //give initial sensor values again
      right = 0;
    }



  }
  //PRINT Q TABLE
  cout << "Final Q Table: " << endl;
  cout << Test.Q[0][0] << " " << Test.Q[0][1] << " " << Test.Q[0][2] << endl;
  cout << Test.Q[1][0] << " " << Test.Q[1][1] << " " << Test.Q[1][2] << endl;
  cout << Test.Q[2][0] << " " << Test.Q[2][1] << " " << Test.Q[2][2] << endl;
  cout << Test.Q[3][0] << " " << Test.Q[3][1] << " " << Test.Q[3][2] << endl;
  cout << endl;
  return 0;
}

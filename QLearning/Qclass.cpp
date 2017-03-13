#include "Qclass.h"
//***********************************************************************
//INCLUDE FILES NEEDED FOR READING DATA FROM SENSORS
//INCLUDE FILES NEEDED FOR PERFORMING ACTIONS/ACCESSING ACTUATORS
//***********************************************************************
#include <iostream>
#include <stdlib.h>
using std::cout;
using std::endl;



//DETERMINE STATE
int Qtable::findState(int left, int right) {  //based on sensor value combination find state
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

//DECIDE ACTION
int Qtable::decideAction(int state) {
  int action;
  int Rand = rand() % 100;

  //35 percent chance of choosing a random action. Want random action sometimes to explore new possibilities/possible better action
  if (Rand > 65) {
    int randAction = rand() % 3;  //random number between 0 and 2

    action = randAction;

  }
  //Use Q table to choose highest rated action for current state, do this most of the time
  else {
    int bestAction;  //initiate best action var
    int bestQ = -100000;  //initiate best Q value, this corresponds to a state action pair value

    for (int i = 0; i < 3; i++) {  //cycle through every action for current state
      if (Q[state][i] > bestQ) {  //if state action pair Q value is greater than current best value
        bestQ = Q[state][i];  //set new highest Q value
        bestAction = i;  //set new best action

      }
    }

    action = bestAction;
  }
  return action;  //return chosen action
}

//ASSIGN REWARD
int Qtable::assignReward(int prevAction, bool crash) {
  int reward;
  if (prevAction == 0) {  //if moved forward reward since we want to explore
    reward = 10;
  }
  if (prevAction == 1 || prevAction == 2) {  //if turn thats neutral, not bad but not exploring
    reward = 0;
  }
  if (crash)  //if crashed give big negative reward
    reward = -100;

  return reward;
}

//FIND MAX FUTURE VALUE
//Need the max future value to update the Q table
int Qtable::maxFuture(int state) {
  int currentMax = -100000;  //initiate var to keep track of max

  for (int i = 0; i != 3; i++) {  //cycle through every action
    if (Q[state][i] > currentMax)  //if state action pair Q value greater than current Q value
      currentMax = Q[state][i];  //set new max Q value
  }

  return currentMax;
}

//UPDATE Q TABLE
void Qtable::updateTable(int prevAction, int prevState, bool crash, int state) {
  alpha = .5;  //variables for update equation
  gamma = .8;
  double reward = assignReward(prevAction, crash);  //get the reward based on previous action and if crash


  //Update Q value using equation. Based on old Q value, reward, max Q value of new state, and constants alpha, gamma
  if (crash == true) {  //if crash, the new state doesn't count, it crashed
    Q[prevState][prevAction] = Q[prevState][prevAction] + alpha * (reward)
        - Q[prevState][prevAction];
  }

  else {
  Q[prevState][prevAction] =
      Q[prevState][prevAction]
          + alpha
          * (reward + (gamma * maxFuture(state))
                  - Q[prevState][prevAction]);


  }
}

//FUNCTION TO TRAIN ROBOT
void Qtable::Train() {

  int firstRun = 0;  //Can't update Q table on first run, no previous data to go off of
  int prevState;
  int prevAction;

  //initiate sensors
  //**********************************
  //SENSORS INITIALIZED ASSUMING NOTHING IN THE WAY
  int left = 0;
  int right = 0;
  //**********************************
  bool crash = false;  //initiate not crashing

  for (int a = 0; a < 1000; a++) {  //number of iterations to train for

    
//************************************************************************************
//HERE IS WHERE YOUR SENSOR FUNCTIONS WILL GO TO READ VALUE FROM SENSORS EITHER 1 OR 0
    if (firstRun > 0) {
      //Get new sensor values based on what previous state and previous action was
      //left = getLeftSensorValue();//representative function
      //right = getRightSensorValue();//representative function
    }
//************************************************************************************

    //Determine state based on left and right sensors
    int state = findState(left, right);//set state with sensor vals


    //Will update after first run is complete
    if (firstRun > 0) {
      if ((prevState == 3 && prevAction == 0)
          || (prevState == 1 && prevAction == 0)
          || (prevState == 2 && prevAction == 0)) {  //if something detected and move forward, crash
        crash = true;
      }

      //Update the Q Table based on prevstate, prevaction , and current state
      updateTable(prevAction, prevState, crash, state);
    }

    //Decide action based on current state. Picks either random action or uses table to decide
     int action = decideAction(state);//decide action based on state
//*************************************************************************
//HERE IS WHERE ACTION IS SENT TO ACTUATORS SO APPROPRIATE ACTION IS TAKEN
//performAction(action);//representative function
//*************************************************************************

    prevState = state;    //set prevstate = state before next iteration
    prevAction = action;    //same

    firstRun = 1;  //Now that first run complete there are previous values, so we can update the table

    //if crash reset  robot to first position, keep Q table though
    if (crash == true) {
      crash = false;   //resetting so back to false
      firstRun = 0;    //basically start over if there is a crash
//**************************************************************
//ROBOT RESETS TO DETECTING NOTHING AFTER A CRASH
//performAction(reset)//representative function
//**************************************************************
      left = 0;    //give initial sensor values again
      right = 0;
    }

  }
  //PRINT Q TABLE
  cout << "Final Q Table: " << endl;
  cout << Q[0][0] << " " << Q[0][1] << " " << Q[0][2];
  cout << endl;
  cout << Q[1][0] << " " << Q[1][1] << " " << Q[1][2];
  cout << endl;
  cout << Q[2][0] << " " << Q[2][1] << " " << Q[2][2];
  cout << endl;
  cout << Q[3][0] << " " << Q[3][1] << " " << Q[3][2];
  cout << endl;
  cout
      << "States: 0. detect nothing, 1, detect right, 2. detect left, 3. detect both."
       << endl;
  cout
      << "Actions: 0. Move forward, 1. turn right in place, 2. turn left in place.";
}

//USE Q TABLE TO PERFORM
void Qtable::Perform() {
  //initiate sensor values
  int left = 1;
  int right = 1;
  //no previous action/previous state on first run
  int firstRun = 0;

  cout << endl << endl << "Performance using Q Table:" << endl;

//*****************************************************************************
//DEPENDING ON WHAT PERFORMANCE IS WANTED, ITERATION CAN BE ADJUSTED
  for (int a = 0; a < 5; a++) {    //iterate 5 times, do 5 actions
//*****************************************************************************


//************************************************************************************
//HERE IS WHERE YOUR SENSOR FUNCTIONS WILL GO TO READ VALUE FROM SENSORS EITHER 1 OR 0
//Get new sensor values  
  if (firstRun > 0) {
      // left = getSensorLeft;//representative function
      //right = getSensorRight;//representative function
  }
//***********************************************************************************

  //Determine state based on left and right sensors
    int state2 = findState(left, right);  //set state with sensor vals

  //Decide action using highest Q table value.
  int bestAction;
  int bestQ = -1000;
  for (int i = 0; i < 3; i++) {  //cycle through every action for current state
    if (Q[state2][i] > bestQ) {  //if state action pair Q value is greater than current best value
      bestQ = Q[state2][i];  //set new highest Q value
      bestAction = i;  //set new best action

    }
  }
  
//*************************************************************************
//HERE IS WHERE ACTION IS SENT TO ACTUATORS SO APPROPRIATE ACTION IS TAKEN
//performAction(bestAction);//representative function
//*************************************************************************
  
    cout << "For state " << state2 << ", action " << bestAction
         << " was taken"
         << endl;

    firstRun = 1;  //done with first run
  }
  
}






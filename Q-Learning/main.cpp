#include <iostream>
#include <stdlib.h>
using std::cout;
using std::endl;

//READ DATA FROM SENSORS, DECIDE CURRENT STATE
class robot {
 public:
  int state;
  int prevState;
  int action;
  int prevAction;
  int reward;
  int Q[4][3] = { };

  double alpha = .5;
  double gamma = .8;

  int findState(int senseOne, int senseTwo);  //determine state based on sensors
  int decideAction(int state);  //determine action based on state
  int assignReward(int prevAction, bool crash);  //assign rewards based on what action was taken
  int maxFuture(int state);
  void updateTable(int prevAction, int prevState, bool crash);
};


/* Q TABLE
//Q[row][column]
//rows are states, columns are actions
//States: 0 detect nothin, 1 detect right, 2 detect left, 3 detect both (front)
//Actions: 0 move forward, 1 turn left in place, 2 turn right in place
 */
//int Q[4][3] = { };  //initial values are all zero


//DETERMINE STATE
int robot::findState(int senseOne, int senseTwo) {
  int state = 0;
  if (senseOne == 0 && senseTwo == 0) {
    state = 0;
  }
  if (senseOne == 1 && senseTwo == 0) {
    state = 1;
  }
  if (senseOne == 0 && senseTwo == 1) {
    state = 2;
  }
  if (senseOne == 1 && senseTwo == 1) {
    state = 3;
  }
  return state;
}

//DECIDE ACTION
int robot::decideAction(int state) {
  int action;
  int Rand = rand() % 100;

  //15 percent chance of choosing a random action. Want random action sometimes to explore new possibilities/possible better action
  if (Rand > 103) {
    int randAction = rand() % 3 + 1;  //random number between 1 and 3
    action = randAction;
    cout << "Random action " << action << " was chosen" << endl;  //print we did a random action
  }
  //Use Q table to choose highest rated action for current state, do this most of the time
  else {
    int bestAction = -100000;  //initiate best action var
    for (int i = 0; i < 3; i++) {  //cycle through every action for current state
      if (Q[state][i] > bestAction) {  //if state action pair Q value is greater than current value
        bestAction = i;  //set new best action
      }
    }
    //print we used Q table, what we did
    cout << "Q table used to decide action:" << endl;
    cout << "For state " << state << ", action " << bestAction
         << " was chosen." << endl << endl;
    action = bestAction;
  }
  return action;  //return chosen action
}

//ASSIGN REWARD
int robot::assignReward(int prevAction, bool crash) {
  int reward;
  if (prevAction == 0) {  //if moved forward reward since we want to explore
    reward = 10;
  }
  if (prevAction == 1 || prevAction == 2) {  //if turn neutral, not bad but not exploring
    reward = 0;
  }
  if (crash)  //if crashed give big negative reward
    reward = -100;
  cout << "Reward " << reward << endl;
  return reward;
}

//FIND MAX FUTURE VALUE
//Need the max future value to update the Q table
int robot::maxFuture(int state) {
  int currentMax = -100000;  //initiate var to keep track of max

  for (int i = 0; i != 3; i++) {
    if (Q[state][i] > currentMax)
      currentMax = Q[state][i];
  }

  return currentMax;
}

//UPDATE Q TABLE

void robot::updateTable(int prevAction, int prevState, bool crash) {
  double reward = assignReward(prevAction, crash);
//  cout << "For Q value " << Q[prevState][prevAction] << endl;
  Q[prevState][prevAction] =
      Q[prevState][prevAction]
          + alpha
              * (reward + (gamma * maxFuture(prevState))
                  - Q[prevState][prevAction]);
  //cout << " New Value " << Q[prevState][prevAction] << endl;

}

int main() {
  robot Test;

  for (int a = 0; a < 1; a++) {
    int in = rand() % 100 + 1;  //generate random input values for sensor
    int one = 0;
    if (in > 50)
      one = 1;

    cout << endl;
    //cout << "Chosen " << in << endl;
    //cout << "input " << one << endl;
    Test.Q[3][0] = -50;
    int state = Test.findState(1, 1);  //set state with sensor1 = 1, sensor2 = 1
    int action = Test.decideAction(state);    //decide action based on state
    int prevState = state;    //set prevstate = state before next iteration
    int prevAction = action;    //same
  //Test.decideAction(1);

  bool crash = false;
    if (state == 3 && action == 0) {  //if something right in front and move forward, crash
      crash = true;
    }



  Test.updateTable(prevAction, prevState, crash);  //update the Q table
   



//PRINT Q TABLE
  cout << Test.Q[0][0] << " " << Test.Q[0][1] << " " << Test.Q[0][2] << endl;
  cout << Test.Q[1][0] << " " << Test.Q[1][1] << " " << Test.Q[1][2] << endl;
  cout << Test.Q[2][0] << " " << Test.Q[2][1] << " " << Test.Q[2][2] << endl;
  cout << Test.Q[3][0] << " " << Test.Q[2][1] << " " << Test.Q[3][2] << endl;

  }
  return 0;
}

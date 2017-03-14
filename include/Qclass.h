// Copyright [2017] <Steven Gambino>

#ifndef QCLASS_H_ // NOLINT
#define QCLASS_H_

/* Q TABLE
 // Q[row][column]
 // rows are states, columns are actions
 // States: 0 detect nothin, 1 detect right, 2 detect left, 3 detect both (front)
 // Actions: 0 move forward, 1 turn left in place, 2 turn right in place
 */

// define class
class Qtable {
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

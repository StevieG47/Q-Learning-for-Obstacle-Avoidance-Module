#ifndef QLEARN_DEMO_H_
#define QLEARN_DEMO_H_

/* Q TABLE
 //Q[row][column]
 //rows are states, columns are actions
 //States: 0 detect nothin, 1 detect right, 2 detect left, 3 detect both (front)
 //Actions: 0 move forward, 1 turn left in place, 2 turn right in place
 */
//define class
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

  int findState(int left, int right);  //determine state based on sensors
  int decideAction(int state);  //determine action based on state
  int assignReward(int prevAction, bool crash);  //assign rewards based on what action was taken
  int maxFuture(int state);
  void updateTable(int prevAction, int prevState, bool crash, int state);
  void Train();
  void Perform();
};


#endif /* QLEARN_DEMO_H_ */

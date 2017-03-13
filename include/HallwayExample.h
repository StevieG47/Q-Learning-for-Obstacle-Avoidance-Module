#ifndef HALLWAYEXAMPLE_H_
#define HALLWAYEXAMPLE_H_

//FOR HALLWAY EXAMPLE
//Walls on either side so if detect nothing and move forward, detect nothing
//detect nothing and turn left once, detect something on left
//detect nothing and turn right once and detect something on right
//detect left and go forward, crash
//detect left and turn left, detect both
//detect left and turn right, detect nothing
//detect right and go forward, crash
//detect right and turn left, detect nothing
//detect right and turn right, detect both
//detect both and go forward, crash
//detect both and turn left, something on right
//detect both and turn right, something on left


int getLeft(int prevState, int prevAction) {
  int senseLeft = 999;
  int senseRight = 999;
//  bool crash;
  //DETECT NOTHING
  if (prevState == 0 && prevAction == 0) {  //detect nothing go forward leads to detect nothing
    senseLeft = 0;
    senseRight = 0;
  }
  if (prevState == 0 && prevAction == 1) {  //detect nothing turn right, something on the right
    senseLeft = 0;
    senseRight = 1;
  }
  if (prevState == 0 && prevAction == 2) {  //detect nothing turn left, something on the left
    senseLeft = 1;
    senseRight = 0;
  }

  //DETECT RIGHT
  if (prevState == 1 && prevAction == 0) {  //detect right and go forward, crash
  //  crash = true;
  }
  if (prevState == 1 && prevAction == 1) {  //detect right and turn right, detect both
    senseLeft = 1;
    senseRight = 1;
  }
  if (prevState == 1 && prevAction == 2) {  //detect right and turn left, detect nothing
    senseLeft = 0;
    senseRight = 0;
  }

  //DETECT LEFT
  if (prevState == 2 && prevAction == 0) {  //detect left and go forward, crash
  //crash = true;
  }
  if (prevState == 2 && prevAction == 1) {  //detect left and turn right, detect nothing
    senseLeft = 0;
    senseRight = 0;
  }
  if (prevState == 2 && prevAction == 2) {  //detect left and turn left, detect both
    senseLeft = 1;
    senseRight = 1;
  }

  //DETECT BOTH
  if (prevState == 3 && prevAction == 0) {  //detect both and go forward, crash
  //crash = true;
  }
  if (prevState == 3 && prevAction == 1) {  //detect both and turn right. something on left
    senseLeft = 1;
    senseRight = 0;
  }
  if (prevState == 3 && prevAction == 2) {  //detect  both and turn left, something on right
    senseLeft = 0;
    senseRight = 1;
  }
  return senseLeft;
}

int getRight(int prevState, int prevAction) {
  int senseLeft;
  int senseRight;
  //bool crash;
  //DETECT NOTHING
  if (prevState == 0 && prevAction == 0) {  //detect nothing go forward leads to detect nothing
    senseLeft = 0;
    senseRight = 0;
  }
  if (prevState == 0 && prevAction == 1) {  //detect nothing turn right, something on the right
    senseLeft = 0;
    senseRight = 1;
  }
  if (prevState == 0 && prevAction == 2) {  //detect nothing turn left, something on the left
    senseLeft = 1;
    senseRight = 0;
  }

  //DETECT RIGHT
  if (prevState == 1 && prevAction == 0) {  //detect right and go forward, crash
  //crash = true;
  }
  if (prevState == 1 && prevAction == 1) {  //detect right and turn right, detect both
    senseLeft = 1;
    senseRight = 1;
  }
  if (prevState == 1 && prevAction == 2) {  //detect right and turn left, detect nothing
    senseLeft = 0;
    senseRight = 0;
  }

  //DETECT LEFT
  if (prevState == 2 && prevAction == 0) {  //detect left and go forward, crash
  //crash = true;
  }
  if (prevState == 2 && prevAction == 1) {  //detect left and turn right, detect nothing
    senseLeft = 0;
    senseRight = 0;
  }
  if (prevState == 2 && prevAction == 2) {  //detect left and turn left, detect both
    senseLeft = 1;
    senseRight = 1;
  }

  //DETECT BOTH
  if (prevState == 3 && prevAction == 0) {  //detect both and go forward, crash
  //crash = true;
  }
  if (prevState == 3 && prevAction == 1) {  //detect both and turn right. something on left
    senseLeft = 1;
    senseRight = 0;
  }
  if (prevState == 3 && prevAction == 2) {  //detect  both and turn left, something on right
    senseLeft = 0;
    senseRight = 1;
  }
  return senseRight;
}

//GET CRASH
/*
bool getCrash(int prevState, int prevAction) {
  int senseLeft;
  int senseRight;
  bool crash;
  //DETECT NOTHING
  if (prevState == 0 && prevAction == 0) {  //detect nothing go forward leads to detect nothing
    senseLeft = 0;
    senseRight = 0;
  }
  if (prevState == 0 && prevAction == 1) {  //detect nothing turn right, something on the right
    senseLeft = 0;
    senseRight = 1;
  }
  if (prevState == 0 && prevAction == 2) {  //detect nothing turn left, something on the left
    senseLeft = 1;
    senseRight = 0;
  }

  //DETECT RIGHT
  if (prevState == 1 && prevAction == 0) {  //detect right and go forward, crash
    crash = true;
  }
  if (prevState == 1 && prevAction == 1) {  //detect right and turn right, detect both
    senseLeft = 1;
    senseRight = 1;
  }
  if (prevState == 1 && prevAction == 2) {  //detect right and turn left, detect nothing
    senseLeft = 0;
    senseRight = 0;
  }

  //DETECT LEFT
  if (prevState == 2 && prevAction == 0) {  //detect left and go forward, crash
    crash = true;
  }
  if (prevState == 2 && prevAction == 1) {  //detect left and turn right, detect nothing
    senseLeft = 0;
    senseRight = 0;
  }
  if (prevState == 2 && prevAction == 2) {  //detect left and turn left, detect both
    senseLeft = 1;
    senseRight = 1;
  }

  //DETECT BOTH
  if (prevState == 3 && prevAction == 0) {  //detect both and go forward, crash
    crash = true;
  }
  if (prevState == 3 && prevAction == 1) {  //detect both and turn right. something on left
    senseLeft = 1;
    senseRight = 0;
  }
  if (prevState == 3 && prevAction == 2) {  //detect  both and turn left, something on right
    senseLeft = 0;
    senseRight = 1;
  }
  return crash;
}
 */


#endif /* HALLWAYEXAMPLE_H_ */
/* Q TABLE
 //Q[row][column]
 //rows are states, columns are actions
 //States: 0 detect nothing, 1 detect right, 2 detect left, 3 detect both (front)
 //Actions: 0 move forward, 1 turn right in place, 2 turn left in place
 */

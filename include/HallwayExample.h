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
 * @file HalwayExample.h
 * @author Steven Gambino
 * @brief Hallway example file
 *
 * Hallway Example
 */
#ifndef HALLWAYEXAMPLE_H_ //NOLINT
#define HALLWAYEXAMPLE_H_

// FOR HALLWAY EXAMPLE
// Walls on either side so if detect nothing and move forward, detect nothing
// detect nothing and turn left once, detect something on left
// detect nothing and turn right once and detect something on right
// detect left and go forward, crash
// detect left and turn left, detect both
// detect left and turn right, detect nothing
// detect right and go forward, crash
// detect right and turn left, detect nothing
// detect right and turn right, detect both
// detect both and go forward, crash
// detect both and turn left, something on right
// detect both and turn right, something on left

/**
 * @brief gets left sensor value based on previous state and previous action
 * @param int previous state and int previous action
 * @return sensor value of left sensor, either 0 detect nothing or 1 detect something
 */
int getLeft(int prevState, int prevAction) {
  int senseLeft = 999;
  // int senseRight = 999;
//  bool crash;
  // DETECT NOTHING
  if (prevState == 0 && prevAction == 0) {  // detect nothing go forward leads to detect nothing
    senseLeft = 0;
    // senseRight = 0;
  }
  if (prevState == 0 && prevAction == 1) {  // detect nothing turn right, something on the right
    senseLeft = 0;
    //  senseRight = 1;
  }
  if (prevState == 0 && prevAction == 2) {  // detect nothing turn left, something on the left
    senseLeft = 1;
    // senseRight = 0;
  }

  // DETECT RIGHT
  if (prevState == 1 && prevAction == 0) {  // detect right and go forward, crash
  //  crash = true;
  }
  if (prevState == 1 && prevAction == 1) {  // detect right and turn right, detect both
    senseLeft = 1;
    //  senseRight = 1;
  }
  if (prevState == 1 && prevAction == 2) {  // detect right and turn left, detect nothing
    senseLeft = 0;
    // senseRight = 0;
  }

  // DETECT LEFT
  if (prevState == 2 && prevAction == 0) {  // detect left and go forward, crash
  // crash = true;
  }
  if (prevState == 2 && prevAction == 1) {  // detect left and turn right, detect nothing
    senseLeft = 0;
    // senseRight = 0;
  }
  if (prevState == 2 && prevAction == 2) {  // detect left and turn left, detect both
    senseLeft = 1;
    // senseRight = 1;
  }

  // DETECT BOTH
  if (prevState == 3 && prevAction == 0) {  // detect both and go forward, crash
  // crash = true;
  }
  if (prevState == 3 && prevAction == 1) {  // detect both and turn right. something on left
    senseLeft = 1;
    //  senseRight = 0;
  }
  if (prevState == 3 && prevAction == 2) {  // detect  both and turn left, something on right
    senseLeft = 0;
    // senseRight = 1;
  }
  return senseLeft;
}
/**
 * @brief gets right sensor value based on previous state and previous action
 * @param int previous state and int previous action
 * @return sensor value of right sensor, either 0 detect nothing or 1 detect something
 */
int getRight(int prevState, int prevAction) {
  // int senseLeft;
  int senseRight;
  // bool crash;
  // DETECT NOTHING
  if (prevState == 0 && prevAction == 0) {  // detect nothing go forward leads to detect nothing
  //  senseLeft = 0;
    senseRight = 0;
  }
  if (prevState == 0 && prevAction == 1) {  // detect nothing turn right, something on the right
  //  senseLeft = 0;
    senseRight = 1;
  }
  if (prevState == 0 && prevAction == 2) {  // detect nothing turn left, something on the left
  //   senseLeft = 1;
    senseRight = 0;
  }

  // DETECT RIGHT
  if (prevState == 1 && prevAction == 0) {  // detect right and go forward, crash
  // crash = true;
  }
  if (prevState == 1 && prevAction == 1) {  // detect right and turn right, detect both
  //  senseLeft = 1;
    senseRight = 1;
  }
  if (prevState == 1 && prevAction == 2) {  // detect right and turn left, detect nothing
  // senseLeft = 0;
    senseRight = 0;
  }

  // DETECT LEFT
  if (prevState == 2 && prevAction == 0) {  // detect left and go forward, crash
  // crash = true;
  }
  if (prevState == 2 && prevAction == 1) {  // detect left and turn right, detect nothing
  //  senseLeft = 0;
    senseRight = 0;
  }
  if (prevState == 2 && prevAction == 2) {  // detect left and turn left, detect both
  // senseLeft = 1;
    senseRight = 1;
  }

  // DETECT BOTH
  if (prevState == 3 && prevAction == 0) {  // detect both and go forward, crash
  // crash = true;
  }
  if (prevState == 3 && prevAction == 1) {  // detect both and turn right. something on left
  // senseLeft = 1;
    senseRight = 0;
  }
  if (prevState == 3 && prevAction == 2) {  // detect  both and turn left, something on right
  // senseLeft = 0;
    senseRight = 1;
  }
  return senseRight;
}



#endif /* HALLWAYEXAMPLE_H_ */ // NOLINT


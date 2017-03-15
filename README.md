# Q Learning for Obstacle Avoidance
[![Build Status](https://travis-ci.org/StevieG47/Q-Learning-for-Obstacle-Avoidance-Module.svg?branch=master)](https://travis-ci.org/StevieG47/Q-Learning-for-Obstacle-Avoidance-Module)
[![Coverage Status](https://coveralls.io/repos/github/StevieG47/Q-Learning-for-Obstacle-Avoidance-Module/badge.svg?branch=master)](https://coveralls.io/github/StevieG47/Q-Learning-for-Obstacle-Avoidance-Module?branch=master)
---

## Overview
The method of allowing a robot to learn its own enviornment can be beneficial for robots that will be constantly operating in new environments. In these situations, it might be more challenging to manually code the robot to explore and avoid obstacles without prior knowledge of the environment. The problem becomes even more difficuly as more sensors are added and the environments become more complex. Using reinforcement learning, robots can train themselves to explore a previously unknown environment.

Q Learning is one such reinforcement technique, and uses the idea of state-action pairs. States of the robot are determined by the readings from sensors and are defined by the user. In the design presented here, two sensors are used, leading to four states: 1. Detect nothing, 2. Detect Left, 3. Detect Right, and 4. Detect both. Possible actions are also defined be the user. In this design, there are three possible actions: 1. Move Forward, 2. Turn left in place, 3. Turn right in place.

The Q Learning method uses a Q table, which consists of a Q value for every state-action pair. The rows of the table are the states and the columns are the actions. The table is updated during training depending on what action was done for specific states. Rewards are assigned to update the Q table, the reward assignments in this design are: +10 for moving forward, 0 for turning in place, and -100 for crashing. This promotes exploration of the robot (as opposed to just turning in place forever) but also punishes actions that will lead to crashing for a given state. After many iterations of performing actions, recieving rewards, and updating the table, the result will be a best action for every state. The robot uses the final Q table to pick the best action and explore its environment.

During training, the Q table is updated after an action is taken. The update is done using the equation shown below:
![qequation](https://cloud.githubusercontent.com/assets/25371934/23921439/03ba6de0-08d5-11e7-9a23-0e313e43fa0f.png)

The values for learning rate and discount factor are constant. For this design, alpha=.5 and gamma=.8. After training, the Q table is not updated, just used to pick the best action. A more in depth example of using reinforcement learning to have a robot avoid obstacles can be seen [here](http://www.ice.ci.ritsumei.ac.jp/~ruck/CLASSES/INTELISYS/NN-Q.pdf).

## Features
This project provides a  Q Learning implementation for the simple two sensor robot with three actions: move forward, turn left, and turn right. This module is designed to work with the sensor/getting information module and the performing actions/actuator module. Qclass.cpp with Qclass.h provides a class that can train the robot, and use the trained Q table to explore. This includes determining the state, deciding an action, and updating the Q table. By working with the other modules mentioned, the robot will learn the enviornemnt and successfully explore it while avoiding obstacles. The Q table is 4x3, an empty table is shown below:

![qtable](https://cloud.githubusercontent.com/assets/25371934/23924075/ab1906a0-08df-11e7-9b8c-eeb2828760bd.JPG)

The integration of the sensor module and actuator module can be easily done, the necessary steps are clearly shown in Qclass.cpp. The number of iterations can be adjusted depending on how many training iterations want to be done. For the demo provided here, the sensor and actuation modules are simulated, so there are separate files labeled with the word *Demo* in them. 

## Demo
The Demo is for the robot in a simulated narrow hallway environment. The file *HallwayExample.h* found in the *include* directory is used to simulate recieving sensor information. In this example the robot is in a very narrow hallway with walls of infinite length. When parallel to the walls, facing down the hallway, the robot detects nothing. Turning right once will lead to detecting something on the right, but nothing on the left. Turning right once more from this position will lead to detecting both, being perpendicular to the wall. Turning right yet again will lead to detecting something on the left and nothing on the right. Another right turn will have the robot facing the hallway again, turned 180 degrees from its initial position. This is the same for turning left, where each turn will be 45 degrees. Moving forward at any oreintation besides 0 or 180 degrees will result in a crash, so if the robot is not turned down the hallway and moves forward, it will hit the wall.
The demo first trains the Q table in this environment, then explores using the trained Q table. The Q table is the same as the one shown above. The states, actions, alpha,and gamma are also the same. The reward assignements remain +10 for moving forward, 0 for turning, and -100 for crashing. 
A top view of the demo environment is shown below:

![example](https://cloud.githubusercontent.com/assets/25371934/23925451/a7cf087c-08e5-11e7-8190-fad0528cd6e7.JPG)

After running the demo, the final Q table is displayed:

![qdemotable](https://cloud.githubusercontent.com/assets/25371934/23925614/72e3ac98-08e6-11e7-98d5-9b83a4c45330.JPG)

We see that for the first state, detect nothing, the best action is move forward with a score of 41. This makes sense since this is the only state when we want the robot to move forward. For the next state, detect right, the best action is to turn left with a score of 31.  This also since makes sense since we want to turn away from obstacles. The next state, detect left has a best action of turn right, and the last state, detect both , has a best action of turn right. 

The Q table is used for 5 actions, the results are shown below: 

![qperformancedemo](https://cloud.githubusercontent.com/assets/25371934/23925748/10fe563a-08e7-11e7-998f-562dcd094990.JPG)

With state 0 = detect nothing, state 1 = detect right, state 2 = detect left, and state 3 = detect both, and action 0 = move forward, action 1 = turn right, and action 2 = turn left, we can see the robot turns away when sensing the wall until it is facing down the hallway. It then moves straight down the hallway. 

While simple, this example shows how the robot learned to avoid crashing while exploring its environment. 


## License
- Project uses the MIT License
```
MIT License

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
```

## Dependencies
- No Dependencies

## How to Build
```
$ git clone --recursive https://github.com/StevieG47/Q-Learning-for-Obstacle-Avoidance-Module.git
cd Q-Learning-for-Obstacle-Avoidance-Module
mkdir build
cd build
cmake ..
make
```

## Running the Demo
- To run the demo: 
```
cd build
./QLearning/QLearning-Demo
```

## Running Tests
- Google test framework was used for unit tests.
- To run tests:
```
cd build
./test/cpp-test
```

## Doxygen Documentaion
- To generate documentation from Q-Learning-for-Obstacle-Avoidance-Module:
```
cd docs
doxygen configQ
```
HTML and Latex output are created in the docs directory. To easily view documentation page, open *annotated.html* in the *html* directory.

## SIP Process
- Design and Development done using the SIP process. Tasks were split up and ordered. Time to complete tasks and defects were logged. Product backlog, iteration backlog, and worklog can be viewed using the google spreadsheet link below:

https://docs.google.com/spreadsheets/d/1hfvxqkjzauMg8wfQMJMttqfL_XiQ8ah67WwOyFDjMoY/edit?usp=sharing

Iteration 1 --> Released functional Q-Learning program, successfully trains and uses table.

Iteration 2 --> Released Demo, tests, and documentation, program finalized. 

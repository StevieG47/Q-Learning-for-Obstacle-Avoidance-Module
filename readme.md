# Q Learning for Obstacle Avoidance
[![Build Status](https://travis-ci.org/StevieG47/Q-Learning-for-Obstacle-Avoidance-Module.svg?branch=master)](https://travis-ci.org/StevieG47/Q-Learning-for-Obstacle-Avoidance-Module)
[![Coverage Status](https://coveralls.io/repos/github/StevieG47/Q-Learning-for-Obstacle-Avoidance-Module/badge.svg?branch=master)](https://coveralls.io/github/StevieG47/Q-Learning-for-Obstacle-Avoidance-Module?branch=master)
---

## Overview
The method of allowing a robot to learn its own enviornment can be beneficial for robots that will be constantly operating in new environments. In these situations, it might be more challenging to manually code the robot to explore and avoid obstacles without prior knowledge of the environment. The problem becomes even more difficuly as more sensors are added and the environments become more complex. Using reinforcement learning, robots can train themselves to explore a previously unknown environment.

Q Learning is one such reinforcement technique, and uses the idea of state-action pairs. States of the robot are determined by the readings from sensors and are defined by the user. In the demo presented here, two sensors are used, leading to four states: 1. Detect nothing, 2. Detect Left, 3. Detect Right, and 4. Detect both. Possible actions are also defined be the user. In the demo, there are three possible actions: 1. Move Forward, 2. Turn left in place, 3. Turn right in place. The Q Learning method uses a Q table, which consists of a Q value every state-action pair. The rows of the table are the states and the columns are the actions. The table is updated during training depending on what action was done for specific states. Rewards are assigned to update the Q table, the reward assignments in this demo are: +10 for moving forward, 0 for turning in place, and -100 for crashing. This promotes exploration of the robot (as opposed to just turning in place forever) but also punishes actions that will lead to crashing for a given state. After many iterations of performing actions, recieving rewards, and updating the table, the result will be a best action for every state. The robot uses the final Q table to pick the best action and explore its environment.

During training, the Q table is updated after an action is taken. The update is done using the equation shown below:
![qequation](https://cloud.githubusercontent.com/assets/25371934/23921439/03ba6de0-08d5-11e7-9a23-0e313e43fa0f.png)

The values for learning rate and discount factor are constant. In the demo, alpha=.5 and gamma=.8.

## Features

## Demo

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
- Google test framework was used to write tests.
- To run tests:
```
cd build
./test/cpp-test
```

## Doxygen Documentaion
- To generate documentation:
```
cd docs
doxygen configQ
```
HTML and Latex output are created. To view documentation page, load *annotaed.html* in the *html* directory.

## SIP Process
- Design and Development done using the SIP process. Product backlog, iteration backlog, and worklog can be viewed using the google spreadsheet link below:

https://docs.google.com/spreadsheets/d/1hfvxqkjzauMg8wfQMJMttqfL_XiQ8ah67WwOyFDjMoY/edit?usp=sharing

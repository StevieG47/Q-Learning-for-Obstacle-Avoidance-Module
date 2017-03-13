#include <iostream>
#include <stdlib.h>

#include "QLearn_Demo.h"
#include "Qclass.h"

using std::cout;
using std::endl;

int main() {
  QDemo Demo;
  Demo.Train();  //Trains robot using Hallway Example in HallwayExample.h, builds Q table
  Demo.Perform();  //Uses Q table to decide actions.

  return 0;
}

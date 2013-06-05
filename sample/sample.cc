#include "easyode.h"

int main (int argc, char **argv)
{
  Simulator& sim = Simulator::getInstance();
  sim.regist("Sphere", Sphere::create(0.0, 0.0, 1.0, 1.0, 0.2));
  sim.regist("Box", Box::create(1.0, 0.0, 1.0, 1.0, 5.0, 0.1, 0.2, 0.3));
  sim.regist("Capsule", Capsule::create(2.0, 0.0, 1.0, 1.0, 0.1, 0.5));
  sim.regist("HingeJoint", HingeJoint::create("Sphere", "Box", 1.0, 0.0, 1.0, 1, 0, 0));
  
  sim.simulate(argc, argv, 400, 300);

  return 0;
}

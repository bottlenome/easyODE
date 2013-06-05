#include "easyode.h"

void command(int cmd);

class MyControl : public BaseController
{
public:
  dReal getVector(dReal tmpAngle, dReal theta)
  {
    dReal z = theta - tmpAngle;
    return 10.0 * z;
  }
};

int main (int argc, char **argv)
{
  Simulator& sim = Simulator::getInstance();
  sim.regist("Root", Capsule::create(0.0, 0.0, 0.05, 10.0, 0.2, 0.1));
  sim.regist("L1", Capsule::create(0.0, 0.0, 0.50, 2.0, 0.04, 0.9));
  sim.regist("L2", Capsule::create(0.0, 0.0, 1.50, 2.0, 0.04, 1.0));
  sim.regist("L3", Capsule::create(0.0, 0.0, 2.55, 2.0, 0.04, 1.0));
  
  sim.regist("fixedJoint", FixedJoint::create("Root"));
  sim.regist("J1", HingeJoint::create("Root", "L1", 0.0, 0.0, 0.1, 0.0, 0.0, 1.0));
  sim.regist("J2", HingeJoint::create("L2",   "L1", 0.0, 0.0, 1.0, 0.0, 1.0, 0.0));
  sim.regist("J3", HingeJoint::create("L3",   "L2", 0.0, 0.0, 2.0, 0.0, 1.0, 0.0));

  sim.setCommand(command);
	MyControl cont;
  sim.regist("J1", cont);
  sim.regist("J2", cont);
  sim.regist("J3", cont);

  sim.simulate(argc, argv, 640, 570);

  return 0;
}

void command(int cmd) {
  Simulator& sim = Simulator::getInstance();
  switch (cmd) {
  case 'j':
    sim.getJoint("J1")->addTheta(0.05);
    break;
  case 'f':
    sim.getJoint("J1")->subTheta(0.05);
    break;
  case 'k': 
    sim.getJoint("J2")->addTheta(0.05);
    break;
  case 'd': 
    sim.getJoint("J2")->subTheta(0.05);
    break;
  case 'l': 
    sim.getJoint("J3")->addTheta(0.05);
    break;
  case 's': 
    sim.getJoint("J3")->subTheta(0.05);
    break;
  }

  // 目標角度が関節可動域を越えないように制限する
  if (sim.getJoint("J1")->getTheta() <  - M_PI)
    sim.getJoint("J1")->setTheta(-M_PI); // M_PI：円周率
  if (sim.getJoint("J1")->getTheta() >    M_PI)
    sim.getJoint("J1")->setTheta(M_PI);
  if (sim.getJoint("J2")->getTheta() < -2*M_PI/3)
    sim.getJoint("J2")->setTheta(-2*M_PI/3);
  if (sim.getJoint("J2")->getTheta() >  2*M_PI/3)
    sim.getJoint("J2")->setTheta(2*M_PI/3);
  if (sim.getJoint("J3")->getTheta() < -2*M_PI/3)
    sim.getJoint("J3")->setTheta(- 2*M_PI/3);
  if (sim.getJoint("J3")->getTheta() >  2*M_PI/3)
    sim.getJoint("J3")->setTheta(2*M_PI/3);
}


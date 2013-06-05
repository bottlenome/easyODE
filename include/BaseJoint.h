#ifndef __BASE_JOINT_H__
#define __BASE_JOINT_H__

#include <ode/ode.h>
#include "BaseController.h"

class BaseJoint
{
public:
  dReal theta;
public:
  BaseJoint()
  {
    theta = 0.0;
    controller = NULL;
  }
  dReal getTheta()
  {
    return theta;
  }
  void setTheta(dReal theta){
    this->theta = theta;
  }
  void addTheta(dReal num)
  {
    this->theta += num;
  }
  void subTheta(dReal num)
  {
    this->theta -= num;
  }
  virtual void regist(BaseController& controller) = 0;
  virtual void control() = 0;

protected:
  dJointID jointID;
  BaseController *controller;
};

#endif /* __BASE_JOINT_H__ */

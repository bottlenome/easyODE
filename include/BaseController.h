#ifndef __BASE_CONTROLLER_H__
#define __BASE_CONTROLLER_H__

#include <ode/ode.h>

class BaseController
{
  dReal fMax;
public:
  BaseController(){fMax = 100.0;}
  virtual ~BaseController(){}
  virtual dReal getVector(dReal tmpAngle, dReal theta) = 0;
  dReal getFmax(){ return fMax;}
};

#endif /* __BASE_CONTROLLER_H__ */

#ifndef __CAPSULE_H__
#define __CAPSULE_H__

#include <ode/ode.h>
#include "BaseObject.h"

#ifdef dDOUBLE
#define dsDrawCapsule dsDrawCapsuleD
#endif

class CapsuleParams
{
public:
  int direction;
  dReal radius;
  dReal length;
  CapsuleParams(dReal radius, dReal length)
  {
    this->direction = 1;
    this->radius = radius;
    this->length = length;
	}
	CapsuleParams(){}
};

class Capsule : public BaseObject
{
private:
  CapsuleParams params;
public:
  Capsule(dBodyID bodyID);
  static Capsule& create(const dReal x, const dReal y, const dReal z,
              const dReal mass, const dReal radius, const dReal length);
  static Capsule& create(const dReal x, const dReal y, const dReal z,
              const dReal mass, const dReal radius, const dReal length,
              const dReal r, const dReal g, const dReal b);
 
  template<class T, class P> void doMakeInstance(dWorldID world, const dReal& mass, dMass& m, T& instance, const P& params)
  {
    this->params = params;
    dMassSetCapsuleTotal(&m, mass, params.direction, params.radius, params.length);
    instance.BaseObject::setColor(0.0, 0.0, 1.0);
  }

  template<class P> void doCreateGeometory(dSpaceID space, const P& radius)
  {
    this->geomID = dCreateCapsule(space, params.radius, params.length);
  }

	void doDraw(const dReal *pos, const dReal *R);
};

#endif /* __CAPSULE_H__ */

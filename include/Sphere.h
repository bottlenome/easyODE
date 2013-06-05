#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <ode/ode.h>
#include "BaseObject.h"

#ifdef dDOUBLE
#define dsDrawSphere dsDrawSphereD
#endif

class Sphere : public BaseObject
{
private:
  dReal radius;
public:
  Sphere(dBodyID bodyID);
  static Sphere& create(const dReal x, const dReal y, const dReal z,
              const dReal mass, const dReal radius);
  static Sphere& create(const dReal x, const dReal y, const dReal z,
              const dReal mass, const dReal radius,
              const dReal r, const dReal g, const dReal b);
 
  template<class T, class P> void doMakeInstance(dWorldID world, const dReal& mass, dMass& m, T& instance, const P& radius)
  {
    instance.setRadius(radius);
    dMassSetSphereTotal(&m, mass, radius);
    instance.BaseObject::setColor(1.0, 0.0, 0.0);
  }

  template<class P> void doCreateGeometory(dSpaceID space, const P& radius)
  {
    this->geomID = dCreateSphere(space, radius);
  }

  void setRadius(dReal radius);
  dReal getRadius();
	void doDraw(const dReal *pos, const dReal *R);
};

#endif /* __SPHERE_H__ */

#ifndef __BASE_OBJECT_H__
#define __BASE_OBJECT_H__

#include <ode/ode.h>
#include "World.h"

class BaseObject
{
protected:
  dBodyID bodyID;
  dGeomID geomID;
  dReal r,g,b;
public:
  BaseObject(){}
  virtual ~BaseObject(){}
  void setColor(dReal r, dReal g, dReal b);
	void show();
  dBodyID getBodyID();
protected:
  template<class T, class P> 
  static T& create(const dReal x, const dReal y, const dReal z,
                   const dReal mass, const P params)
  {
    dMass m;
    dWorldID world = World::getInstance().getWorldID();
    dSpaceID space = World::getInstance().getSpaceID();
    dMassSetZero(&m);

    //make and set instance
    T* instance = new T(dBodyCreate(world));
    instance->doMakeInstance<T, P>(world, mass, m, *instance, params);

    dBodySetMass(instance->bodyID, &m);
    dBodySetPosition(instance->bodyID, x, y, z);

    instance->doCreateGeometory<P>(space, params);
    dGeomSetBody(instance->geomID, instance->bodyID);

    return *instance;
  }

private:
  template<class T, class P>
  void doMakeInstance(dWorldID world, const dReal mass, dMass& m, T& instance, const P params);
  template<class P>
  void doCreateGeometory(dSpaceID space, const P params);
  virtual void doDraw(const dReal *pos, const dReal *R) = 0;
  BaseObject(BaseObject&){}
  void operator =(BaseObject&){}
};

#endif /* __OBJECT_H__ */

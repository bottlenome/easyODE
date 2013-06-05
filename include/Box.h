#ifndef __Box_H__
#define __Box_H__

#include <ode/ode.h>
#include "BaseObject.h";

#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#endif

class BoxParams
{
public:
  dReal sides[3];
  dReal density;
  BoxParams(const dReal width, const dReal height, const dReal depth,
            const dReal density)
  {
    sides[0] = width;
    sides[1] = height;
    sides[2] = depth;
    this->density = density;
  }
  BoxParams(){};
};

class Box : public BaseObject
{
private:
  BoxParams params;
public:
  Box(dBodyID bodyID);
  
  static Box& create(const dReal x, const dReal y, const dReal z,
                     const dReal mass, const dReal density,
                     const dReal width, const dReal height, const dReal depth);
  
  static Box& create(const dReal x, const dReal y, const dReal z,
                     const dReal mass, const dReal density,
                     const dReal width, const dReal height, const dReal depth,
                     const dReal r, const dReal g, const dReal b);

  template<class T, class P>
  void doMakeInstance(dWorldID world, const dReal& mass, dMass& m, T& instance, const P& params)
  {
    instance.params = params;
    dMassSetBox(&m, params.density, params.sides[0], params.sides[1], params.sides[2]);
    instance.BaseObject::setColor(0.0, 1.0, 0.0);
  }

  template<class P>
  void doCreateGeometory(dSpaceID space, const P& params)
  {
    this->geomID = dCreateBox(space, params.sides[0], params.sides[1], params.sides[2]);
  }

  void setSides(const dReal width, const dReal height, const dReal depth);
  dReal* getSides();
  void doDraw(const dReal *pos, const dReal *R);
};

#endif /* __BOX_H__ */

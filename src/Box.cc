#include "Box.h"

Box::Box(dBodyID bodyID)
{
  this->bodyID = bodyID;
}

Box& Box::create(const dReal x, const dReal y, const dReal z,
    const dReal mass, const dReal density,
    const dReal width, const dReal height, const dReal depth)
{
  BoxParams params(width, height, depth, density);
  return BaseObject::create<Box, BoxParams>(x, y, z, mass, params);
}

Box& Box::create(const dReal x, const dReal y, const dReal z,
    const dReal mass, const dReal density,
    const dReal width, const dReal height, const dReal depth,
    const dReal r, const dReal g, const dReal b)
{
  Box& box = Box::create(x, y, z, mass, density, width, height, depth);
  box.BaseObject::setColor(r, g, b);

  return box;
}

void Box::setSides(const dReal width, const dReal height, const dReal depth)
{
  this->params.sides[0] = width;
  this->params.sides[1] = height;
  this->params.sides[2] = depth;
}

dReal* Box::getSides()
{
  return this->params.sides;
}

void Box::doDraw(const dReal *pos, const dReal *R)
{
	dsDrawBox(pos, R, this->getSides());
}


#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include "BaseObject.h"

void BaseObject::setColor(dReal r, dReal g, dReal b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

void BaseObject::show()
{
  const dReal *pos, *R;
  dsSetColor(this->r, this->g, this->b);
  pos = dBodyGetPosition(this->bodyID);
  R = dBodyGetRotation(this->bodyID);
	doDraw(pos, R);
}

dBodyID BaseObject::getBodyID()
{
  return this->bodyID;
}

#include "Capsule.h"

Capsule::Capsule(dBodyID bodyID)
{
  this->bodyID = bodyID;
}

Capsule& Capsule::create(const dReal x, const dReal y, const dReal z,
                         const dReal mass,
                         const dReal radius, const dReal length)
{
  CapsuleParams params(radius, length);
  return BaseObject::create<Capsule, CapsuleParams>(x, y, z, mass, params);
}

Capsule& Capsule::create(const dReal x, const dReal y, const dReal z,
    const dReal mass,
    const dReal radius, const dReal length,
    const dReal r, const dReal g, const dReal b)
{
  Capsule& capsule = Capsule::create(x, y, z, mass, radius, length);
  capsule.BaseObject::setColor(r, g, b);

  return capsule;
}

void Capsule::doDraw(const dReal *pos, const dReal *R)
{
	dReal radius, length;
	dGeomCapsuleGetParams(this->geomID, &radius, &length);
  dsDrawCapsule(pos, R, length, radius);
}


#include "Sphere.h"

Sphere::Sphere(dBodyID bodyID)
{
  this->bodyID = bodyID;
}

Sphere& Sphere::create(const dReal x, const dReal y, const dReal z,
                       const dReal mass, const dReal radius)
{
  return BaseObject::create<Sphere, dReal>(x, y, z, mass, radius);
}

Sphere& Sphere::create(const dReal x, const dReal y, const dReal z,
    const dReal mass, const dReal radius,
    const dReal r, const dReal g, const dReal b)
{
  Sphere& sphere = Sphere::create(x, y, z, mass, radius);
  sphere.BaseObject::setColor(r, g, b);

  return sphere;
}

void Sphere::setRadius(dReal radius)
{
  this->radius = radius;
}

dReal Sphere::getRadius()
{
  return this->radius;
}

void Sphere::doDraw(const dReal *pos, const dReal *R)
{
  dsDrawSphere(pos, R, this->getRadius());
}


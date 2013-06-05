#include <vector>
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include "World.h"

World& World::getInstance()
{
  static World instance;
  if(instance.getWorldID() == NULL){
    dInitODE();
    instance.setWorldID(dWorldCreate());
    instance.setSpaceID(dHashSpaceCreate(0));
    instance.setJointGroupID(dJointGroupCreate(0));
    instance.setGroundID(dCreatePlane(instance.getSpaceID(), 0, 0, 1, 0));
    dWorldSetGravity(instance.getWorldID(), 0, 0, -0.5);
  }
  return instance;
}

void World::setGravity(dReal x, dReal y, dReal z)
{
  dWorldSetGravity(World::getInstance().getWorldID(), x, y, z);
}

void World::setWorldID(dWorldID id)
{
  this->worldID = id;
}

dWorldID World::getWorldID()
{
  return this->worldID;
}

void World::setSpaceID(dSpaceID id)
{
  this->spaceID = id;
}

dSpaceID World::getSpaceID()
{
  return this->spaceID;
}

void World::setJointGroupID(dJointGroupID id)
{
  this->jointGroupID = id;
}

dJointGroupID World::getJointGroupID()
{
  return this->jointGroupID;
}

void World::setGroundID(dGeomID id)
{
  this->groundID = id;
}

dGeomID World::getGroundID()
{
  return this->groundID;
}

World::World()
{
  worldID = NULL;
  spaceID = NULL;
  groundID = NULL;
  jointGroupID = NULL;
}

World::~World()
{
  if(worldID != NULL){
    dWorldDestroy(this->getWorldID());
    dCloseODE();
  }
}



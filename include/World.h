#ifndef __WORLD_H__
#define __WORLD_H__

#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

class World
{
private:
  dWorldID worldID;
  dSpaceID spaceID;
  dGeomID groundID;
  dJointGroupID jointGroupID;

public:
  static World& getInstance();
  static void setGravity(dReal x, dReal y, dReal z);
  void setWorldID(dWorldID id);
  dWorldID getWorldID();
  void setSpaceID(dSpaceID id);
  dSpaceID getSpaceID();
  void setJointGroupID(dJointGroupID id);
  dJointGroupID getJointGroupID();
  void setGroundID(dGeomID id);
  dGeomID getGroundID();

private:
  World();
  ~World();
	World(World&);
	void operator = (World&);
};

#endif /* __WORLD_H__ */

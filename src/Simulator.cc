#include <iostream>
#include <stdlib.h>
#include "Simulator.h"

Simulator& Simulator::getInstance()
{
  static Simulator instance;
  return instance;
}

Simulator::Simulator()
{
  fn.version = DS_VERSION;
  fn.start   = &start;
  fn.step    = &simLoop;
  fn.command = NULL;
  fn.stop    = NULL;
  fn.path_to_textures = TEXTURE_PATH;
}

void Simulator::regist(std::string name, BaseObject& obj)
{
  objectMap.insert(std::map<std::string, BaseObject*>::value_type(name, &obj));
}

void Simulator::regist(std::string name, BaseJoint& joint)
{
  jointMap.insert(std::map<std::string, BaseJoint*>::value_type(name, &joint));
}

void Simulator::regist(std::string name, BaseController& controller)
{
  std::map<std::string, BaseJoint*>::const_iterator it = jointMap.find(name);
  if(it != jointMap.end())
    it->second->regist(controller);
}

dBodyID Simulator::getBodyID(std::string name)
{
  std::map<std::string, BaseObject*>::const_iterator it = objectMap.find(name);
  if(it != objectMap.end())
    return it->second->getBodyID();
  std::cerr << "err: can't find body name " + name << std::endl;
  exit(-1);
  return NULL;
}

BaseJoint* Simulator::getJoint(std::string name)
{
  std::map<std::string, BaseJoint*>::const_iterator it = jointMap.find(name);
  if(it != jointMap.end())
    return it->second;
  std::cerr << "err: can't find joint name " + name << std::endl;
  exit(-1);
  return NULL;
}

void Simulator::setCommand(void func(int))
{
  fn.command = func;
}

void Simulator::simulate(int argc,char** argv, int width, int height)
{
  dsSimulationLoop (argc, argv, width, height, &(this->fn));
}

void Simulator::show()
{
  Simulator& sim = Simulator::getInstance();
  std::map<std::string, BaseObject*>::const_iterator it = sim.objectMap.begin();
  for(; it != sim.objectMap.end(); it++)
  {
    it->second->show();
  }
}

void Simulator::control()
{
  Simulator &sim = Simulator::getInstance();
  std::map<std::string, BaseJoint*>::const_iterator it = sim.jointMap.begin();
  
  for(; it != sim.jointMap.end(); it++)
  {
    it->second->control();
  }
}

void Simulator::start()
{
  static float xyz[3] = {0.0,-3.0,1.0};
  static float hpr[3] = {90.0,0.0,0.0};
  dsSetViewpoint (xyz, hpr);
}

void Simulator::simLoop (int pause)
{
  World& world = World::getInstance();

  control();
  dSpaceCollide(world.getSpaceID(), 0, &nearCallBack);
	dWorldStep(world.getWorldID(), 0.01);
  dJointGroupEmpty(world.getJointGroupID());
  
  Simulator::getInstance().show();
}

void Simulator::nearCallBack(void *data, dGeomID object1, dGeomID object2)
{
  const int N = 10;
  dContact contact[N];
  World& world = World::getInstance();
  dGeomID groundID = world.getGroundID();
  dWorldID worldID = world.getWorldID();
  dJointGroupID jointGroupID = world.getJointGroupID();

  int isGround = ((groundID == object1) || (groundID == object2));

  int n =  dCollide(object1, object2, N, &contact[0].geom, sizeof(dContact));
  
  if (isGround)  {
    for (int i = 0; i < n; i++) {
      contact[i].surface.mode = dContactBounce;
      contact[i].surface.mu   = dInfinity;
      contact[i].surface.bounce     = 0.0; // (0.0~1.0) restitution parameter
      contact[i].surface.bounce_vel = 0.0; // minimum incoming velocity for bounce
      dJointID c = dJointCreateContact(worldID , jointGroupID, &contact[i]);
      dJointAttach(c, dGeomGetBody(contact[i].geom.g1), dGeomGetBody(contact[i].geom.g2));
    }
  }
}


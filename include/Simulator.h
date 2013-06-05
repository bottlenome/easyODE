#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <string>
#include <vector>
#include <map>
#include "World.h"
#include "BaseObject.h"
#include "BaseJoint.h"

#ifndef TEXTURE_PATH
#define TEXTURE_PATH NULL
#endif

class Simulator
{
private:
  dsFunctions fn;
  std::map<std::string, BaseObject*> objectMap;
  std::map<std::string, BaseJoint*> jointMap;

public:
  static Simulator& getInstance();
  void regist(std::string name, BaseObject& obj);
  void regist(std::string name, BaseJoint& joint);
  void regist(std::string name, BaseController& controller);
  void simulate(int argc,char** argv, int width, int height);
  void show();
  dBodyID getBodyID(std::string name);
  BaseJoint* getJoint(std::string name);
  void setCommand(void func(int));

private:
  static void start();
  static void simLoop (int pause);
  static void nearCallBack(void *data, dGeomID object1, dGeomID object2);
  static void control();
  Simulator();
  ~Simulator(){}
  Simulator(Simulator&);
  void operator = (Simulator&);
};

#endif /* __SIMULATOR_H__ */

#ifndef __FIXED_JOINT_H__
#define __FIXED_JOINT_H__

#include <string>
#include "BaseJoint.h"
#include "World.h"

class FixedJoint : public BaseJoint
{
public:
	static FixedJoint& create(std::string object1)
	{
		FixedJoint* instance = new FixedJoint();
		Simulator& sim = Simulator::getInstance();
		instance->jointID = dJointCreateFixed(World::getInstance().getWorldID(), 0);
		dJointAttach(instance->jointID, sim.getBodyID(object1), 0);
		dJointSetFixed(instance->jointID);

		return *instance;
	}

  void regist(BaseController& controller)
  {
    this->controller = &controller;
    /* DO nothing */
  }

  void control()
  {
    /* Do nothing */
  }

};
#endif /* __FIXED_JOINT_H__ */

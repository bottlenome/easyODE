#ifndef __HINGE_JOINT_H__
#define __HINGE_JOINT_H__

#include <string>
#include "BaseJoint.h"
#include "BaseController.h"
#include "World.h"

class HingeJoint : public BaseJoint
{
public:
  HingeJoint(){theta = 0;};
  static HingeJoint& create(std::string object1, std::string object2,
                     dReal x, dReal y, dReal z,
                     dReal vx, dReal vy, dReal vz)
  {
    HingeJoint* instance = new HingeJoint();
    Simulator& sim = Simulator::getInstance();
    instance->jointID = dJointCreateHinge(World::getInstance().getWorldID(), 0);
    dJointAttach(instance->jointID, sim.getBodyID(object1), sim.getBodyID(object2));
    dJointSetHingeAnchor(instance->jointID, x, y, z);
    dJointSetHingeAxis(instance->jointID, vx, vy, vz);
    return *instance;
  }

	void regist(BaseController& controller)
	{
		this->controller = &controller;
		dJointSetHingeParam(this->jointID, dParamFMax, controller.getFmax());
	}

	void control()
	{
    if(this->controller != NULL){
		  dReal tmpAngle = dJointGetHingeAngle(this->jointID);
		  dJointSetHingeParam(this->jointID, dParamVel, this->controller->getVector(tmpAngle, theta));
    }
	}
};

#endif /* __HINGE_JOINT_H__ */

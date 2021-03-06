//
// Created by jhwangbo on 17. 4. 28.
//

#include <raiGraphics/obj/Capsule.hpp>
#include "raiGraphics/RAI_graphics.hpp"
#include "raiGraphics/obj/CoordinateFrame.hpp"
//#include <raiGraphics/obj/Mesh.hpp>
#include "raiGraphics/obj/Sphere.hpp"
#include "raiGraphics/obj/Cone.hpp"
#include "raiGraphics/obj/Box.hpp"
#include "raiGraphics/obj/Cylinder.hpp"

using namespace rai_graphics;

int main() {

  // TODO: RAI_ROOT in every file should be changed (now only task module left)
  RAI_graphics graphics(800,600);

  // graphical primitives
  object::Sphere whiteSphere(1, true);
  object::Cone redCone(1, 2, true);
  object::Box greenBox(2, 2, 2, true);
  object::Cylinder blueCylinder(1, 2, true);
  object::Capsule yellowCapsule(1, 2, true);
  object::Background background("sky");
  object::CheckerBoard grnd(5, 100, 100, 0.05, {0,0,0}, {1,1,1});
  Eigen::Vector3d bodyFrameOrigin(0.0, 0.0, 3.0);
  Eigen::Quaterniond bodyFrameQuat(1, 0, 0, 0);
  object::CoordinateFrame inertiaFrame(bodyFrameOrigin, bodyFrameQuat);

  Eigen::Vector3d bodyFrameOrigin1(10.0, 0.0, 3.0);
  Eigen::Quaterniond bodyFrameQuat1(0.9239, 0.3827, 0, 0);
  object::CoordinateFrame bodyFrame1(bodyFrameOrigin1, bodyFrameQuat1);
  Eigen::Vector3d bodyFrameOrigin2(0.0, 10.0, 3.0);
  Eigen::Quaterniond bodyFrameQuat2(0.9239, 0, 0.3827, 0);
  object::CoordinateFrame bodyFrame2(bodyFrameOrigin2, bodyFrameQuat2);
  Eigen::Vector3d bodyFrameOrigin3(0.0, 0.0, 10.0);
  Eigen::Quaterniond bodyFrameQuat3(0.9239, 0, 0, 0.3827);
  object::CoordinateFrame bodyFrame3(bodyFrameOrigin3, bodyFrameQuat3);
  Eigen::Vector3d bodyFrameOrigin4(0.0, -10.0, 3.0);
  Eigen::Quaterniond bodyFrameQuat4(0, 1.0, 0, 0);
  object::CoordinateFrame bodyFrame4(bodyFrameOrigin4, bodyFrameQuat4);


  whiteSphere.setColor({1.0, 1.0, 1.0});
  redCone.setColor({1.0, 0.0, 0.0});
  greenBox.setColor({0.0, 1.0, 0.0});
  blueCylinder.setColor({0.0, 0.0, 1.0});
  yellowCapsule.setColor({1.0, 1.0, 0.0});

  Eigen::Vector3d redConePosition; redConePosition << 10, 0, 3;
  Eigen::Quaterniond redConeQuaternion(0.9239, 0.3827, 0, 0);
  Eigen::Vector3d greenBoxPosition; greenBoxPosition << 0, 10, 3;
  Eigen::Quaterniond greenBoxQuaternion(0.9239, 0, 0.3827, 0);
  Eigen::Vector3d blueCylinderPosition; blueCylinderPosition << 0, 0, 10;
  Eigen::Quaterniond blueCylinderQuaternion(0.9239, 0, 0, 0.3827);
  Eigen::Vector3d yellowCapsulePostion; yellowCapsulePostion << 0, -10, 3;

  whiteSphere.setPos(0,0,3);
  redCone.setPose(redConePosition, redConeQuaternion);
  greenBox.setPose(greenBoxPosition, greenBoxQuaternion);
  blueCylinder.setPose(blueCylinderPosition, blueCylinderQuaternion);
  yellowCapsule.setPos(yellowCapsulePostion);

  object::Arrow directionArrow(0.1, 0.2, 4, 0.2);
  directionArrow.setColor({1.0, 1.0, 0.0});
  Eigen::Vector3d directionVector(0.0, 0.0, 1.0);
  directionArrow.representVector(directionVector);

//  graphics.addBackground(&background);
  graphics.addCheckerBoard(&grnd);
  graphics.addObject(&whiteSphere);
  graphics.addObject(&redCone);
  graphics.addObject(&greenBox);
  graphics.addObject(&blueCylinder);
  graphics.addObject(&yellowCapsule);
  graphics.addObject(&directionArrow);
  graphics.addSuperObject(&inertiaFrame);
  graphics.addSuperObject(&bodyFrame1);
  graphics.addSuperObject(&bodyFrame2);
  graphics.addSuperObject(&bodyFrame3);
  graphics.addSuperObject(&bodyFrame4);
  grnd.gridMode = true;
  grnd.setColor({0.3,0,0});

  // ghost objects
  Eigen::Vector3d ghostVector1; ghostVector1 << 10, 0, 3;
  Eigen::Quaterniond ghostQuaternion1(1.0, 0, 0, 0);
  directionArrow.addGhost(ghostVector1, ghostQuaternion1);

  Eigen::Vector3d ghostVector2; ghostVector2 << 0, 10, 3;
  Eigen::Quaterniond ghostQuaternion2(0.7071, 0, 0, 0.7071);
  directionArrow.addGhost(ghostVector2, ghostQuaternion1);

  LightProp lprop;
  lprop.pos_light = {10.0, 0.0, 10.0};
  CameraProp cprop;
  cprop.toFollow = &whiteSphere;
  Eigen::Vector3d relPos; relPos << 15, 15, 15;
  cprop.relativeDist = relPos;

  graphics.setCameraProp(cprop);
  graphics.setLightProp(lprop);
  graphics.start();

  // exit test app when keyboard 'Q' key pressed
  while(!graphics.isQuitting())
    usleep(1);

  graphics.end();

  return 0;
}
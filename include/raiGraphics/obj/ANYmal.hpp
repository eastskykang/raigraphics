//
// Created by jhwangbo on 17. 5. 3.
//

#ifndef RAI_ANYMAL_HPP
#define RAI_ANYMAL_HPP

#include <rai/common/TypeDef.hpp>
#include "MultiBodyObject.hpp"
#include "Mesh.hpp"

namespace rai_graphics {
namespace object {

class ANYmal : public MultiBodyObject {

 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  ANYmal();
  ~ANYmal();
  void init();
  void destroy();
  void setPose(std::vector<RAI::HomogeneousTransform> &bodyPose);
  SingleBodyObject* basePtr(){ return &base; }

 private:

  Mesh base;
  Mesh hip_lf;
  Mesh hip_rf;
  Mesh hip_lh;
  Mesh hip_rh;

  Mesh thigh_lf;
  Mesh thigh_rf;
  Mesh thigh_lh;
  Mesh thigh_rh;

  Mesh shank_lf;
  Mesh shank_rf;
  Mesh shank_lh;
  Mesh shank_rh;

  Mesh foot_lf;
  Mesh foot_rf;
  Mesh foot_lh;
  Mesh foot_rh;
  std::vector<RAI::HomogeneousTransform> defaultPose_;
};

} // object
} // rai_graphics

#endif //RAI_ANYMAL_HPP

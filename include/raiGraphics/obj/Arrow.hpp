//
// Created by joonho on 19.05.17.
//

#ifndef RAI_ARROW_HPP
#define RAI_ARROW_HPP

#include "SingleBodyObject.hpp"
#include <vector>

namespace rai_graphics {
namespace object {

class Arrow : public SingleBodyObject {

 public:
  Arrow(float r1, float r2, float l1, float l2);

  void addGhostWithVector(Eigen::Vector3d &position, Eigen::Vector3d &directionVector);
  void representVector(Eigen::Vector3d &directionVector);
  void representVector(Eigen::Vector3d &origin, Eigen::Vector3d &directionVector);

 private:
  Eigen::Quaterniond quaternionForDirectionVector(const Eigen::Vector3d &directionVector) const;
};

} // object
} // rai_graphics


#endif //RAI_ARROW_HPP

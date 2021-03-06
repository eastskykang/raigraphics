//
// Created by joonho on 19.05.17.
//
#include "raiGraphics/obj/Arrow.hpp"

namespace rai_graphics {
namespace object {

Arrow::Arrow(float r1, float r2, float l1, float l2) {
  defaultShader = object::RAI_SHADER_BASIC;
  reflectable = false;

  unsigned slices = 20;
  unsigned position = 0;
//  bottom
  positions.emplace_back(glm::vec3(0, 0, 0));
  normals.emplace_back(glm::vec3(-1, 0, 0));

  for (unsigned i = 0; i < slices; i++) {
    float theta = 2 * M_PI / slices * i;
    float y = r1 * std::cos(theta);
    float z = r1 * std::sin(theta);
    positions.emplace_back(glm::vec3(0, y, z));
    normals.emplace_back(glm::vec3(-1, 0, 0));
  }
  for (unsigned i = 1; i < slices + 1; i++) {
    indices.push_back(0);
    indices.push_back(i % slices + 1);
    indices.push_back(i);
  }
  position = slices;

  //side
  for (unsigned i = 0; i < slices; i++) {
    float theta = 2 * M_PI / slices * i;
    float y = r1 * std::cos(theta);
    float z = r1 * std::sin(theta);
    positions.emplace_back(glm::vec3(0, y, z));
    normals.emplace_back(glm::vec3(0, y, z));
  }

  for (unsigned i = 0; i < slices; i++) {
    float theta = 2 * M_PI / slices * i;
    float y = r1 * std::cos(theta);
    float z = r1 * std::sin(theta);
    positions.emplace_back(glm::vec3(l1, y, z));
    normals.emplace_back(glm::vec3(0, y, z));
  }

  for (unsigned i = 1; i < slices + 1; i++) {
    indices.push_back(position + i);
    indices.push_back(position + i % slices + 1);
    indices.push_back(2*position+ i);

    indices.push_back(2*position + i);
    indices.push_back(position + i % slices + 1);
    indices.push_back(2*position + i % slices + 1);
  }

  position += slices;
//Head bottom
  positions.emplace_back(glm::vec3(l1, 0, 0));
  normals.emplace_back(glm::vec3(1 , 0, 0));

  for (unsigned i = 0; i < slices; i++) {
    float theta = 2 * M_PI / slices * i;
    float y = r2 * std::cos(theta);
    float z = r2 * std::sin(theta);
    positions.emplace_back(glm::vec3(l1, y, z));
    normals.emplace_back(glm::vec3(-1,0,0));
  }

  position += slices + 1;

  for (unsigned i = 1; i < slices + 1; i++) {
    indices.push_back(position);
    indices.push_back(i % slices + 1+ position);
    indices.push_back(i + position);
  }

  for (unsigned i = 0; i < slices; i++) {
    float theta = 2 * M_PI / slices * i;
    float y = r2 * std::cos(theta);
    float z = r2 * std::sin(theta);
    positions.emplace_back(glm::vec3(l1, y, z));
    normals.emplace_back(glm::vec3(0,y,z));
  }

  position += slices;

  //Head
  for (unsigned i = 0; i < slices; i++) {
    float theta = 2 * M_PI / slices * i;
    float y = r2 * std::cos(theta);
    float z = r2 * std::sin(theta);
    positions.emplace_back(glm::vec3(l1 + l2, 0, 0));
    normals.emplace_back(glm::vec3(r2/l2, y, z));
  }

  for (unsigned i = 1; i < slices + 1; i++) {
    indices.push_back(i +position);
    indices.push_back(i % slices + 1 +position);
    indices.push_back(position + slices + i);
  }
}

void Arrow::representVector(Eigen::Vector3d &directionVector) {
  Eigen::Quaterniond rotation = quaternionForDirectionVector(directionVector);
  setOri(rotation);
}
void Arrow::representVector(Eigen::Vector3d &origin, Eigen::Vector3d &directionVector) {
  Eigen::Quaterniond rotation = quaternionForDirectionVector(directionVector);
  setPose(origin, rotation);
}

Eigen::Quaterniond Arrow::quaternionForDirectionVector(const Eigen::Vector3d &directionVector) const {
  double theta = atan2(directionVector(1), directionVector(0));
  double sqrt_x2y2 = sqrt(directionVector(0) * directionVector(0)
                              + directionVector(1) * directionVector(1));
  double phi = atan2(directionVector(2), sqrt_x2y2);

  Eigen::Quaterniond rotationZ(cos(theta/2), 0, 0, sin(theta/2));
  Eigen::Quaterniond rotationY(cos(phi/2), 0, -sin(phi/2), 0);
  Eigen::Quaterniond rotation = rotationZ * rotationY;
  return rotation;
}

void Arrow::addGhostWithVector(Eigen::Vector3d &position, Eigen::Vector3d &directionVector) {
  Eigen::Quaterniond quat = quaternionForDirectionVector(directionVector);
  glm::quat quatglm = glm::quat(quat.w(), quat.x(), quat.y(), quat.z());
  glm::vec3 pos(position(0), position(1), position(2));

  Transform ghostTransform;
  ghostTransform.SetRot(quatglm);
  ghostTransform.SetPos(pos);
  ghosts.push_back(ghostTransform);
  ghostColor.emplace_back(color_[0], color_[1], color_[2]);
  ghostScale.emplace_back(scaleMat_[0][0], scaleMat_[1][1], scaleMat_[2][2]);
}

void Arrow::addGhostWithVector(Eigen::Vector3d position, Eigen::Vector3d directionVector, Eigen::Vector3f color, Eigen::Vector3f scale) {
  Eigen::Quaterniond quat = quaternionForDirectionVector(directionVector);
  glm::quat quatglm = glm::quat(quat.w(), quat.x(), quat.y(), quat.z());
  glm::vec3 pos(position(0), position(1), position(2));

  Transform ghostTransform;
  ghostTransform.SetRot(quatglm);
  ghostTransform.SetPos(pos);
  ghosts.push_back(ghostTransform);
  ghostScale.emplace_back(scale(0), scale(1), scale(2));
  ghostColor.emplace_back(color(0), color(1), color(2));
}

} // object
}
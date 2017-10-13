#ifndef SHADER_BASIC_INCLUDED_H
#define SHADER_BASIC_INCLUDED_H

#include "shader.hpp"

namespace rai_graphics {

class Shader_basic : public Shader {
 public:
  Shader_basic();
  ~Shader_basic();

  virtual std::string shaderFileName();
  void Bind();
  void UnBind();
  void Update(Camera *camera,  Light *light, objects::Object* obj);

 protected:
 private:
  static const unsigned int NUM_SHADERS = 2;
  static const unsigned int NUM_UNIFORMS = 4;

  GLuint m_shaders[NUM_SHADERS];
  GLuint m_uniforms[NUM_UNIFORMS];
};

} // rai_graphics

#endif

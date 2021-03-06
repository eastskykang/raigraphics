//
// Created by jhwangbo on 17. 4. 30.
//
#include "raiGraphics/config.hpp"
#include <raiGraphics/obj/Background.hpp>
#include "raiCommon/rai_utils.hpp"
#include "raiGraphics/imp/shader_background.hpp"

namespace rai_graphics {

Shader_background::Shader_background() {
  m_program = glCreateProgram();
  m_shaders[0] = CreateShader(LoadShader(std::string(RAI_GRAPHICS_ROOT_PATH) + "/res/cubeMapShader.vs"), GL_VERTEX_SHADER);
  m_shaders[1] = CreateShader(LoadShader(std::string(RAI_GRAPHICS_ROOT_PATH) + "/res/cubeMapShader.fs"), GL_FRAGMENT_SHADER);

  for (unsigned int i = 0; i < NUM_SHADERS; i++)
    glAttachShader(m_program, m_shaders[i]);

  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");
}

Shader_background::~Shader_background() {
  for (unsigned int i = 0; i < NUM_SHADERS; i++) {
    glDetachShader(m_program, m_shaders[i]);
    glDeleteShader(m_shaders[i]);
  }
  glDeleteProgram(m_program);
}

void Shader_background::Bind() {
  glUseProgram(m_program);
}

void Shader_background::UnBind() {
  glUseProgramObjectARB(0);
}

void Shader_background::Update(Camera *camera, Light *light, object::SingleBodyObject* obj){
  RAIFATAL("Shader_background only works with a background object");
}

void Shader_background::Update(Camera *camera, Light *light, object::Background* obj) {
  glDisable(GL_CLIP_DISTANCE0);
  glDisable(GL_CLIP_DISTANCE1);
  glDisable(GL_CLIP_DISTANCE2);
  glDisable(GL_CLIP_DISTANCE3);
  glDisable(GL_CLIP_DISTANCE4);
  glCullFace(GL_BACK);
  glm::mat4 MVP;
  camera->GetVP(MVP);
  glm::mat4 Normal;
  glUniformMatrix4fv(glGetUniformLocation(m_program, "MVP"), 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(m_program, "Normal"), 1, GL_FALSE, &Normal[0][0]);
  glUniform1i(glGetUniformLocation(m_program, "skybox"), 0);
}

void Shader_background::UpdateForReflection(Camera *camera, Light *light, object::SingleBodyObject* obj, object::CheckerBoard* chk){
  RAIFATAL("cannot draw reflection for background yet");
}


} // rai_graphics
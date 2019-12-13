#include "water.h"
#include "scene.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

Water::Water() {
  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(texture_vert_glsl, texture_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("waterC.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("quad.obj");
}

bool Water::update(Scene &scene, float dt) {
  // Offset for UV mapping, creates illusion of scrolling
  textureOffset.y -= dt/5;

  generateModelMatrix();
  return true;
}

void Water::render(Scene &scene) {
  // Disable writing to the depth buffer so we render a "background"
  glDepthMask(GL_FALSE);

  // NOTE: this object does not use camera, just renders the entire quad as is
  shader->use();
  shader->setUniform("LightDirection", scene.lightDirection1);
  shader->setUniform("CameraPos",scene.camera->position);
  shader->setUniform("LightColor", scene.lightColor);

  shader->setUniform("LightDirection2", scene.lightDirection2);
  shader->setUniform("LightColor2", scene.lightColor2);

  shader->setUniform("ambientProp",{0.1f,0.1f,0.1f});
  shader->setUniform("diffuseProp",{0.3f,0.3f,0.3f});
  shader->setUniform("specularProp",{0.7f,0.7f,0.7f});
  shader->setUniform("specularPower",64);

  // Pass UV mapping offset to the shader
  shader->setUniform("TextureOffset", textureOffset);

  // Render mesh, not using any projections, we just render in 2D
  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("ViewMatrix", mat4{1.0f});
  shader->setUniform("ProjectionMatrix", mat4{1.0f});
  shader->setUniform("Texture", *texture);
  mesh->render();

  glDepthMask(GL_TRUE);
}

// shared resources
unique_ptr<Mesh> Water::mesh;
unique_ptr<Shader> Water::shader;
unique_ptr<Texture> Water::texture;

#include "mountain.h"
#include "projectile.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> Mountain::mesh;
unique_ptr<Texture> Mountain::texture;
unique_ptr<Shader> Mountain::shader;

Mountain::Mountain() {
  // Set random scale speed and rotation
  scale = {1.4,1.2,1};
  scale *= 3.0f;
  speed = {0,-2.0f,0};
  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("coral.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("m2.obj");
}

bool Mountain::update(Scene &scene, float dt) {

  // Generate modelMatrix from position, rotation and scale
  generateModelMatrix();
  position += speed *dt;

  return true;
}

struct Light {
    glm::vec3 position, color;
    double att_const, att_linear, att_quad;
};

void Mountain::render(Scene &scene) {
  shader->use();
  // Set up light
  shader->setUniform("LightDirection", scene.lightDirection1);
  shader->setUniform("CameraPos",scene.camera->position);
  shader->setUniform("LightColor", scene.lightColor);

  shader->setUniform("LightDirection2", scene.lightDirection2);
  shader->setUniform("LightColor2", scene.lightColor2);

  shader->setUniform("ambientProp",{0.1f,0.1f,0.1f});
  shader->setUniform("diffuseProp",{0.3f,0.3f,0.3f});
  shader->setUniform("specularProp",{0.7f,0.7f,0.7f});
  shader->setUniform("specularPower",64);
  shader->setUniform("Transparency", 0.1f);


    // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

  // render mesh
  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("Texture", *texture);
  mesh->render();
}



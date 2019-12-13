#include <glm/gtc/random.hpp>
#include "fuelBar.h"
#include "projectile.h"
#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> FuelBar::mesh;
unique_ptr<Texture> FuelBar::texture;
unique_ptr<Shader> FuelBar::shader;

FuelBar::FuelBar() {
  // Set random scale speed and rotation
  scale = {4,0.05,1};

  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("black.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("cube.obj");
}

bool FuelBar::update(Scene &scene, float dt) {
  generateModelMatrix();
  return true;
}

void FuelBar::render(Scene &scene) {
  shader->use();

  // Set up light
  shader->setUniform("LightDirection", glm::vec3{10,0,-10});
  shader->setUniform("CameraPos",scene.camera->position);
  shader->setUniform("LightColor", scene.lightColor3);

  shader->setUniform("LightDirection2", glm::vec3{-10,0,-10});
  shader->setUniform("LightColor2", scene.lightColor3);

  shader->setUniform("ambientProp",{0.1f,0.1f,0.1f});
  shader->setUniform("diffuseProp",{0.3f,0.3f,0.3f});
  shader->setUniform("specularProp",{0.7f,0.7f,0.7f});
  shader->setUniform("specularPower",64);

  // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

  // render mesh
  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("Texture", *texture);
  mesh->render();
}



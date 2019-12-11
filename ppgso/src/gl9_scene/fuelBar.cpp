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
  shader->setUniform("LightDirection", scene.lightDirection);

  // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

  // render mesh
  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("Texture", *texture);
  mesh->render();
}



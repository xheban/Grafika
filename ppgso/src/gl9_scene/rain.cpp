#include <glm/gtc/random.hpp>
#include "scene.h"
#include "waterParticle.h"
#include "rain.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// shared resources
unique_ptr<Mesh> Rain::mesh;
unique_ptr<Shader> Rain::shader;
unique_ptr<Texture> Rain::texture;

Rain::Rain() {
  // Set default speed
  speed = {linearRand(-0.3,0.3), linearRand(-3,-2), linearRand(-1,1)};
  scale = {0.05f,0.05f,0.18f};
  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("water.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("sphere.obj");
}

bool Rain::update(Scene &scene, float dt) {
  // Increase age
  age += dt;

  position += speed * dt;

  // Die after 5s
  if (position.z > 0) return false;

  generateModelMatrix();
  return true;
}

void Rain::render(Scene &scene) {
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

void Rain::destroy() {
  // This will destroy the projectile on Update
  age = 100.0f;
}

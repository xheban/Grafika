#include <glm/gtc/random.hpp>
#include "scene.h"
#include "waterParticle.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// shared resources
unique_ptr<Mesh> WaterParticle::mesh;
unique_ptr<Shader> WaterParticle::shader;
unique_ptr<Texture> WaterParticle::texture;

WaterParticle::WaterParticle() {
  // Set default speed
  speed = {linearRand(-0.3,0.3), linearRand(-3,-2), linearRand(-1,1)};
  scale = {0.08f,0.15f,0.15f};
  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("waterC.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("sphere.obj");
}

bool WaterParticle::update(Scene &scene, float dt) {
  // Increase age
  age += dt;

  position += speed * dt;

  // Die after 5s
  if (age > 1.0f) return false;

  generateModelMatrix();
  return true;
}

void WaterParticle::render(Scene &scene) {
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

void WaterParticle::destroy() {
  // This will destroy the projectile on Update
  age = 100.0f;
}

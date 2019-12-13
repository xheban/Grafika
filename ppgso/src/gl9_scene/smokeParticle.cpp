#include <glm/gtc/random.hpp>
#include "scene.h"
#include "smokeParticle.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// shared resources
unique_ptr<Mesh> SmokeParticle::mesh;
unique_ptr<Shader> SmokeParticle::shader;
unique_ptr<Texture> SmokeParticle::texture;

SmokeParticle::SmokeParticle() {
  // Set default speed
  speed = {linearRand(-0.3,0.3), linearRand(-3,-2), linearRand(-1,1)};
  scale *= linearRand(0.05, 0.1);
  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("smoke.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("asteroid.obj");
}

bool SmokeParticle::update(Scene &scene, float dt) {
  // Increase age
  age += dt;

  position += speed * dt;

  // Die after 5s
  if (age > 1.0f) return false;

  generateModelMatrix();
  return true;
}

void SmokeParticle::render(Scene &scene) {
  shader->use();

  // Set up light
  shader->use();
  shader->setUniform("LightDirection", scene.lightDirection1);
  shader->setUniform("CameraPos",scene.camera->position);
  shader->setUniform("LightColor", scene.lightColor);
  shader->setUniform("Transparency", 0.05f);
  shader->setUniform("LightDirection2", scene.lightDirection2);
  shader->setUniform("LightColor2", scene.lightColor2);

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

void SmokeParticle::destroy() {
  // This will destroy the projectile on Update
  age = 100.0f;
}

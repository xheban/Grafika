#include <glm/gtc/random.hpp>
#include "scene.h"
#include "projectile.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// shared resources
unique_ptr<Mesh> Projectile::mesh;
unique_ptr<Shader> Projectile::shader;
unique_ptr<Texture> Projectile::texture;

Projectile::Projectile() {
  // Set default speed
  speed = {0.0f, 3.0f, 0.0f};
  rotMomentum = {0.0f, 0.0f, linearRand(-PI/4.0f, PI/4.0f)};
  scale *= 0.6f;
  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("missile.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("missile.obj");
}

bool Projectile::update(Scene &scene, float dt) {
  // Increase age
  if(!init){
    Frame f;
    f.time = 0.0;
    f.position = position;
    frame.push_back(f);

    Frame f2;
    f2.time = 1.5f;
    f2.position = position + glm::vec3(0,20,0);
    frame.push_back(f2);
    init = true;
  }

  age += dt;
  position = glm::lerp(frame[0].position, frame[1].position, (age - frame[0].time) / (frame[1].time - frame[0].time));

  // Die after 5s
  if (age > 5.0f) return false;

  generateModelMatrix();
  return true;
}

void Projectile::render(Scene &scene) {
  shader->use();

  // Set up light
  shader->setUniform("LightDirection", scene.lightDirection1);
  shader->setUniform("CameraPos",scene.camera->position);
  shader->setUniform("LightColor", scene.lightColor);

  shader->setUniform("LightDirection2",scene.lightDirection2);
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

void Projectile::destroy() {
  // This will destroy the projectile on Update
  age = 100.0f;
}

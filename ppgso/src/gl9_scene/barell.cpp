#include <glm/gtc/random.hpp>
#include "boat.h"
#include "projectile.h"
#include "player.h"
#include "explosion.h"
#include "barell.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <zconf.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> Barell::mesh;
unique_ptr<Texture> Barell::texture;
unique_ptr<Shader> Barell::shader;

Barell::Barell() {
  // Set random scale speed and rotation
  scale *= 1.5f;
  speed = {0.0f, -5, 0.0f};

  rotation = ballRand(PI);
  rotMomentum = {linearRand(-PI,PI),linearRand(-PI,PI),0};


  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("barell.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("barell.obj");
}

bool Barell::update(Scene &scene, float dt) {
  // Animate position according to time

  position += speed * dt;
  rotation += rotMomentum * dt;
  // Collide with scenes
  for (auto &obj : scene.objects) {
    // Ignore self in scene
    if (obj.get() == this) continue;

    // We only need to collide with asteroids and projectiles, ignore other objects
    auto projectile = dynamic_cast<Projectile*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);

   float distanceX = distance(position.x, obj->position.x);
   float distanceY = distance(position.y, obj->position.y);


    if (distanceY < (obj->scale.y + scale.y) * 1.5f && distanceX < (obj->scale.x + scale.x) *1.5f && projectile){
        projectile->destroy();

        glm::vec3 explodePosition = {1,1,0};
        glm::vec3 explodePosition2 = {-1,-1,0};
        glm::vec3 explodePosition3 = {-1,1,0};
        glm::vec3 explodePosition4 = {1,-1,0};
        glm::vec3 explodePosition5 = {2,-1,0};
        glm::vec3 explodePosition6 = {1,-2,0};
        glm::vec3 explodePosition7 = {2,-2,0};

        explode(scene, (obj->position + position) / 2.0f, (obj->scale + scale) / 2.0f);
        explode(scene, (obj->position + position + explodePosition ) / 2.0f, (obj->scale + scale) / 2.0f);
        explode(scene, (obj->position + position + explodePosition2) / 2.0f, (obj->scale + scale) / 2.0f);
        explode(scene, (obj->position + position + explodePosition3) / 2.0f, (obj->scale + scale) / 2.0f);
        explode(scene, (obj->position + position + explodePosition4) / 2.0f, (obj->scale + scale) / 2.0f);
        explode(scene, (obj->position + position + explodePosition5) / 2.0f, (obj->scale + scale) / 2.0f);
        explode(scene, (obj->position + position + explodePosition6) / 2.0f, (obj->scale + scale) / 2.0f);
        explode(scene, (obj->position + position + explodePosition7) / 2.0f, (obj->scale + scale) / 2.0f);


      // Destroy self
        return false;
    }
    if(position.y < -10){
        return false;
    }
  }

    if (age > 50.0f){
        return false;
    }
  // Generate modelMatrix from position, rotation and scale
  generateModelMatrix();

  return true;
}

void Barell::explode(Scene &scene, vec3 explosionPosition, vec3 explosionScale) {
  // Generate explosion
  auto explosion = make_unique<Explosion>();
  explosion->position = explosionPosition;
  explosion->scale = explosionScale;
  explosion->speed = speed / 2.0f;
  scene.objects.push_back(move(explosion));
}

void Barell::render(Scene &scene) {
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

void Barell::destroy() {
    // This will destroy the projectile on Update
    age = 100.0f;
}



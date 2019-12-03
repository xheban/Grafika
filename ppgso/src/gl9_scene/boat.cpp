#include <glm/gtc/random.hpp>
#include "boat.h"
#include "projectile.h"
#include "player.h"
#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <zconf.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> Boat::mesh;
unique_ptr<Texture> Boat::texture;
unique_ptr<Shader> Boat::shader;

Boat::Boat() {
  // Set random scale speed and rotation
  scale *= 0.3f;
  speed = {linearRand(1,4), -5, 0.0f};

  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("metal.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("boatSmallR.obj");
}

bool Boat::update(Scene &scene, float dt) {
  // Animate position according to time

  position += speed * dt;

  if(position.x > 6 || position.x < -6){
      speed.x = speed.x *-1;
  }


  // Collide with scenes
  for (auto &obj : scene.objects) {
    // Ignore self in scene
    if (obj.get() == this) continue;

    // We only need to collide with asteroids and projectiles, ignore other objects
    auto projectile = dynamic_cast<Projectile*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);

   float distanceX = distance(position.x, obj->position.x);
   float distanceY = distance(position.y, obj->position.y);


    if (distanceY < (obj->scale.y + scale.y) * 1.5f && distanceX < (obj->scale.x + scale.x) *1.5f && projectile)
    {
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
    if(age > 90){
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
        return false;
    }
    if(position.y < -10){
        return false;
    }
  }

  // Generate modelMatrix from position, rotation and scale
  generateModelMatrix();

  return true;
}

void Boat::explode(Scene &scene, vec3 explosionPosition, vec3 explosionScale) {
  // Generate explosion
  auto explosion = make_unique<Explosion>();
  explosion->position = explosionPosition;
  explosion->scale = explosionScale;
  explosion->speed = speed / 2.0f;
  scene.objects.push_back(move(explosion));


}

void Boat::render(Scene &scene) {
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

void Boat::destroy() {
    // This will destroy the projectile on Update
    age = 100.0f;
}


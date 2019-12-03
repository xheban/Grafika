#include "player.h"
#include "scene.h"
#include "asteroid.h"
#include "projectile.h"
#include "explosion.h"
#include "waterParticle.h"
#include "boat.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// shared resources
unique_ptr<Mesh> Player::mesh;
unique_ptr<Texture> Player::texture;
unique_ptr<Shader> Player::shader;

Player::Player() {
  // Scale the default model
  scale *= 0.4f;

  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("metal.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("playerBoat.obj");
}

bool Player::update(Scene &scene, float dt) {
  // Fire delay increment
  fireDelay += dt;
  glm::vec3 waterSpeed = {linearRand(-0.8,0.8), linearRand(-4,-3), linearRand(-1,1)};
  double offset= position.x * 0.23;

  // Hit detection
  for ( auto& obj : scene.objects ) {
    // Ignore self in scene
    if (obj.get() == this)
      continue;

    // We only need to collide with asteroids, ignore other objects
    auto boat = dynamic_cast<Boat*>(obj.get());
    if (!boat) continue;

      float distanceX = distance(position.x, boat->position.x);
      float distanceY = distance(position.y, boat->position.y);


      if ((distanceY < 1 && distanceX < 1 && boat->position.y > position.y) || (distanceY < 5 && distanceX < 1.5f && boat->position.y < position.y )) {
          // Explode
          auto explosion = make_unique<Explosion>();
          explosion->position = position;
          explosion->scale = scale * 3.0f;
          scene.objects.push_back(move(explosion));
          boat->destroy();
          // Die
          return false;
      }

  }
    auto water = make_unique<WaterParticle>();
    water->position = position - glm::vec3(linearRand(-0.2f,0.2f)+offset, 3.7f, 0.3f);
    water->speed = waterSpeed;
    scene.objects.push_back(move(water));

    if(position.x > 8.5){
        position.x = 8.5;
    }
    if(position.x < -8.5){
        position.x = -8.5f;
    }

  // Keyboard controls
    if(scene.keyboard[GLFW_KEY_LEFT]) {
        position.x += 10 * dt;
//        rotation.z = -PI/16.0f;
//        if(!addedL){
//            position.x -= 0.5;
//        }
        waterSpeed = {linearRand(-0.8,0.8) - 4, linearRand(-4,-3),linearRand(-1,1)};
        addedL = true;
    } else if(scene.keyboard[GLFW_KEY_RIGHT]) {
        position.x -= 10 * dt;
//        rotation.z = PI/16.0f;
//        if(!addedR){
//            position.x += 0.3;
//        }
        waterSpeed = {linearRand(-0.8,0.8) + 4, linearRand(-4,-3),linearRand(-1,1)};
        addedR = true;
    } else {
        addedL = false;
        addedR = false;
        rotation.z = 0;
        waterSpeed = {linearRand(-0.8,0.8), linearRand(-4,-3),linearRand(-1,1)};
    }

  // Firing projectiles
  if(scene.keyboard[GLFW_KEY_SPACE] && fireDelay > fireRate) {
    // Reset fire delay
      fireDelay = 0;

    auto projectile = make_unique<Projectile>();
    auto explosion = make_unique<Explosion>();

    explosion->position = position - glm::vec3(offset, 0.3f,0.3f);
    explosion->scale = {0.2,0.2,0.2};
    scene.objects.push_back(move(explosion));

    projectile->position = position - glm::vec3(offset, 0.3f, 0.3f) ;
    scene.objects.push_back(move(projectile));

  }

  generateModelMatrix();
  return true;
}

void Player::render(Scene &scene) {
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

void Player::onClick(Scene &scene) {
  cout << "Player has been clicked!" << endl;
}

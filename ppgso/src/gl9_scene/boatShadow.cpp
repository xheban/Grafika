#include <glm/gtc/random.hpp>
#include "boat.h"
#include "projectile.h"
#include "player.h"
#include "explosion.h"
#include "boatShadow.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <zconf.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> BoatShadow::mesh;
unique_ptr<Texture> BoatShadow::texture;
unique_ptr<Shader> BoatShadow::shader;

BoatShadow::BoatShadow() {
  // Set random scale speed and rotation
  scale *= 0.8f;

  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("shadow.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("boatShade.obj");
}

bool BoatShadow::update(Scene &scene, float dt) {
  // Animate position according to time

    if(position.x > 5.5 || position.x < -5.5){
        speed.x = speed.x *-1;
    }
    if(age > 60){
        return false;
    }

  // Generate modelMatrix from position, rotation and scale
  generateModelMatrix();

  return true;
}

void BoatShadow::render(Scene &scene) {
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

  // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

  // render mesh
  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("Texture", *texture);
  mesh->render();
}

void BoatShadow::destroy() {
     age = 100.0f;
}

void BoatShadow::updatePosition(glm::vec3 positionB){
    position = positionB;
}

void BoatShadow::generate(){
    cout << position.x << endl;
    generateModelMatrix();
}


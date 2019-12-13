#include "boat.h"
#include "projectile.h"
#include "player.h"
#include "explosion.h"
#include "fuelBarFill.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <zconf.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> FuelBarFill::mesh;
unique_ptr<Texture> FuelBarFill::texture;
unique_ptr<Shader> FuelBarFill::shader;

FuelBarFill::FuelBarFill() {
  // Set random scale speed and rotation
  scale ={1.94f,0.05f,0.8};

  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("green.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("cube.obj");
}

bool FuelBarFill::update(Scene &scene, float dt) {
  // Animate position according to time

    scale.x = 1.94 - ((100-fuel)*0.0194);
    position.x = -4.87 + ((100-fuel)*0.01);
    if(scale.x > 1.3){
        texture = make_unique<Texture>(image::loadBMP("green.bmp"));
    }
    if(scale.x < 1.3 && scale.x > 0.6){
        texture = make_unique<Texture>(image::loadBMP("yelow.bmp"));
    }
    if(scale.x <= 0.6 && scale.x > 0){
        texture = make_unique<Texture>(image::loadBMP("red.bmp"));
    }
    if(scale.x < 0){
        scale.x = 0;
    }

    generateModelMatrix();
    return true;
}


void FuelBarFill::render(Scene &scene) {
  shader->use();
  fuel = 100.0f;
  // Set up light
    shader->setUniform("LightDirection", scene.lightDirection1);
    shader->setUniform("CameraPos",scene.camera->position);
    shader->setUniform("LightColor", scene.lightColor3);

    shader->setUniform("LightDirection2", scene.lightColor3);
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

void FuelBarFill::changeFuelBarFill(float fuelB){
   fuel = fuelB;
}



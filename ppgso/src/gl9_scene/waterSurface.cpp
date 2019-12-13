#include <glm/gtc/random.hpp>
#include "fuelBar.h"
#include "projectile.h"
#include "explosion.h"
#include "waterSurface.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> WaterSurface::mesh;
unique_ptr<Texture> WaterSurface::texture;
unique_ptr<Shader> WaterSurface::shader;

WaterSurface::WaterSurface() {
  // Set random scale speed and rotation
  scale = {30,60,0.001f};
  speed = {0,-4,0};

  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("waterSurface.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("cube.obj");
}

bool WaterSurface::update(Scene &scene, float dt) {
  position += speed*dt;
  generateModelMatrix();
  return true;
}

void WaterSurface::render(Scene &scene) {
  shader->use();

  // Set up light
    shader->setUniform("LightDirection", scene.lightDirection1);
    shader->setUniform("CameraPos",scene.camera->position);
    shader->setUniform("LightColor", scene.lightColor3);

    shader->setUniform("LightDirection2", scene.lightDirection2);
    shader->setUniform("LightColor2", scene.lightColor3);

    shader->setUniform("ambientProp",{0.15f,0.25f,0.8f});
    shader->setUniform("diffuseProp",{0.4f,0.4f,0.4f});
    shader->setUniform("specularProp",{0.2f,0.2f,0.3f});
    shader->setUniform("specularPower",32);

  // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

  // render mesh
  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("Texture", *texture);
  mesh->render();
}




#include <glm/gtc/random.hpp>
#include "fuelBar.h"
#include "projectile.h"
#include "explosion.h"
#include "ammoBar.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> AmmoBar::mesh;
unique_ptr<Texture> AmmoBar::texture;
unique_ptr<Shader> AmmoBar::shader;

AmmoBar::AmmoBar() {
  // Set random scale speed and rotation
  scale = {4,0.05,1};

  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = make_unique<Texture>(image::loadBMP("ammo6.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("cube.obj");
}

bool AmmoBar::update(Scene &scene, float dt) {

    switch (ammo){
        case 0: texture = make_unique<Texture>(image::loadBMP("ammo.bmp"));break;
        case 1: texture = make_unique<Texture>(image::loadBMP("ammo1.bmp"));break;
        case 2: texture = make_unique<Texture>(image::loadBMP("ammo2.bmp"));break;
        case 3: texture = make_unique<Texture>(image::loadBMP("ammo3.bmp"));break;
        case 4: texture = make_unique<Texture>(image::loadBMP("ammo4.bmp"));break;
        case 5: texture = make_unique<Texture>(image::loadBMP("ammo5.bmp"));break;
        case 6: texture = make_unique<Texture>(image::loadBMP("ammo6.bmp"));break;
    }

  generateModelMatrix();
  return true;
}

void AmmoBar::render(Scene &scene) {
  shader->use();

  // Set up light
    shader->setUniform("LightDirection", scene.lightDirection1);
    shader->setUniform("CameraPos",scene.camera->position);
    shader->setUniform("LightColor", scene.lightColor3);

    shader->setUniform("LightDirection2", scene.lightDirection2);
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

void AmmoBar::changeAmmo(int ammoB){
    ammo = ammoB;
}



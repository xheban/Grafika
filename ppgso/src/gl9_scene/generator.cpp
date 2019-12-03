#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "asteroid.h"
#include "boat.h"
#include "mountain.h"

using namespace std;
using namespace glm;
using namespace ppgso;

bool Generator::update(Scene &scene, float dt) {
  // Accumulate time
  time += dt;
  mountainTime +=dt;

  if(!firstBoat){
      auto obj = make_unique<Boat>();
      obj->position = position + glm::vec3 {0,10,0} ;
      scene.objects.push_back(move(obj));
      firstBoat= true;
      time = 0;
      auto mountain = make_unique<Mountain>();
      mountain->position = {8.5f,8.0f,-0.4f};
      scene.objects.push_back(move(mountain));

      auto mountain2 = make_unique<Mountain>();
      mountain2->position = {-19.0f,8.0f,-0.4f};
      scene.objects.push_back(move(mountain2));

      auto mountain3 = make_unique<Mountain>();
      mountain3->position = {8.5f,43.5f,-0.4f};
      scene.objects.push_back(move(mountain3));

      auto mountain4 = make_unique<Mountain>();
      mountain4->position = {-19.0f,43.5f,-0.4f};
      scene.objects.push_back(move(mountain4));
  }

  // Add boats
  if (time > 3) {
    auto obj = make_unique<Boat>();
    obj->position = position + glm::vec3 {0,0,0};
    scene.objects.push_back(move(obj));
    time = 0;
  }

  if(mountainTime > refreshTime){

      auto mountain3 = make_unique<Mountain>();
      mountain3->position = {8.5f,43.5f,-0.4f};
      scene.objects.push_back(move(mountain3));

      auto mountain4 = make_unique<Mountain>();
      mountain4->position = {-19.0f,43.5f,-0.4f};
      scene.objects.push_back(move(mountain4));

      mountainTime = 0;
  }

  return true;
}

void Generator::render(Scene &scene) {
  // Generator will not be rendered
}

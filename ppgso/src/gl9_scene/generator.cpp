#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "boat.h"
#include "mountain.h"
#include "barell.h"
#include "ammoCart.h"
#include "rain.h"

using namespace std;
using namespace glm;
using namespace ppgso;

bool Generator::update(Scene &scene, float dt) {
  // Accumulate time
  time += dt;
  mountainTime +=dt;
  barrelTime +=dt;
  ammoTime +=dt;

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

      auto barrel = make_unique<Barell>();
      barrel->position = position + glm::vec3 {linearRand(-6,6),20,2};
      scene.objects.push_back(move(barrel));

      auto ammo = make_unique<AmmoCart>();
      ammo->position = position + glm::vec3 {linearRand(-6,6),10,0};
      scene.objects.push_back(move(ammo));
  }

  // Add boats
  if (time > 3) {
    auto obj = make_unique<Boat>();
    obj->position = position + glm::vec3 {0,15,0};
    scene.objects.push_back(move(obj));
    time = 0;
  }

  if(barrelTime > refreshTimeBarrel){
      auto barrel = make_unique<Barell>();
      barrel->position = position + glm::vec3 {linearRand(-6,6),20,0};
      scene.objects.push_back(move(barrel));
      refreshTimeBarrel = linearRand(8,12);
      barrelTime = 0.0f;
  }

    if(ammoTime > refreshTimeAmmo){
        auto ammo = make_unique<AmmoCart>();
        ammo->position = position + glm::vec3 {linearRand(-5,5),20,-1};
        scene.objects.push_back(move(ammo));
        refreshTimeAmmo = linearRand(5,7);
        ammoTime = 0.0f;
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

  if(rain){
      rainTime +=dt;
      for(int i = 0; i < 20; i++ ){
          auto raindrop = make_unique<Rain>();
          raindrop->position = {linearRand(-6,6),linearRand(-12,20),-10};
          raindrop->speed = {linearRand(2,4),0,linearRand(6,10)};
          scene.objects.push_back(move(raindrop));
      }
      if(rainTime > rainTimer){
          rainTime = 0;
          rain = false;
      }
  }else{
      noRainTime +=dt;
  }

  return true;
}

void Generator::render(Scene &scene) {
  // Generator will not be rendered
}

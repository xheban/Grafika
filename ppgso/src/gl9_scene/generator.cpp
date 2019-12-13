#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "boat.h"
#include "mountain.h"
#include "barell.h"
#include "ammoCart.h"
#include "rain.h"
#include "waterSurface.h"
#include "player.h"
#include "boatShadow.h"

using namespace std;
using namespace glm;
using namespace ppgso;

bool Generator::update(Scene &scene, float dt) {
  // Accumulate time
  time += dt;
  mountainTime +=dt;
  barrelTime +=dt;
  ammoTime +=dt;
  surfaceTime +=dt;

  if(!firstBoat){

      auto surface = make_unique<WaterSurface>();
      surface->position = position + glm::vec3 {0,10,2} ;
      scene.objects.push_back(move(surface));

      auto obj = make_unique<Boat>();
      obj->position = position + glm::vec3 {0,25,0} ;
      scene.objects.push_back(move(obj));

      firstBoat= true;
      time = 0;

      auto mountain = make_unique<Mountain>();
      mountain->position = {9.0f,8.0f,1};
      scene.objects.push_back(move(mountain));

      auto mountain2 = make_unique<Mountain>();
      mountain2->position = {-20.0f,8.0f,1};
      scene.objects.push_back(move(mountain2));

      auto mountain3 = make_unique<Mountain>();
      mountain3->position = {9.0f,43.5f,1};
      scene.objects.push_back(move(mountain3));

      auto mountain4 = make_unique<Mountain>();
      mountain4->position = {-20.0f,43.5f,1};
      scene.objects.push_back(move(mountain4));

      auto barrel = make_unique<Barell>();
      barrel->position = position + glm::vec3 {linearRand(-6,6),20,0.2};
      scene.objects.push_back(move(barrel));

      auto ammo = make_unique<AmmoCart>();
      ammo->position = position + glm::vec3 {linearRand(-6,6),10,0};
      scene.objects.push_back(move(ammo));
  }

  // Add boats
  if (time > 3) {
    auto obj = make_unique<Boat>();
    obj->position = position + glm::vec3 {0,25,0};
    scene.objects.push_back(move(obj));
    time = 0;
  }

  if(surfaceTime > surfaceRefreshTime){
      auto surface = make_unique<WaterSurface>();
      surface->position = position + glm::vec3 {0,46,2} ;
      scene.objects.push_back(move(surface));
      surfaceTime = 0.0f;
      surfaceRefreshTime = 15.0f;
  }

  if(barrelTime > refreshTimeBarrel){
      auto barrel = make_unique<Barell>();
      barrel->position = position + glm::vec3 {linearRand(-6,6),8,0.2};
      scene.objects.push_back(move(barrel));
      refreshTimeBarrel = linearRand(8,12);
      barrelTime = 0.0f;
  }

    if(ammoTime > refreshTimeAmmo){
        auto ammo = make_unique<AmmoCart>();
        ammo->position = position + glm::vec3 {linearRand(-5,5),20,0.2};
        scene.objects.push_back(move(ammo));
        refreshTimeAmmo = linearRand(4,6);
        ammoTime = 0.0f;
    }

  if(mountainTime > refreshTime){

      auto mountain3 = make_unique<Mountain>();
      mountain3->position = {9.0f,43.5f,1};
      scene.objects.push_back(move(mountain3));

      auto mountain4 = make_unique<Mountain>();
      mountain4->position = {-20.0f,43.5f,1};
      scene.objects.push_back(move(mountain4));

      mountainTime = 0;
  }

  if(rain){
      int v1 = rand() % 2;
      if(v1 == 1 && !wind) {
          wind = true;
          windStrength = linearRand(-8,8);

          for ( auto& obj : scene.objects ) {
              // Ignore self in scene
              if (obj.get() == this)
                  continue;

              auto player = dynamic_cast<Player *>(obj.get());

              if (player) {
                  player->windForce(windStrength);
              }
          }
      }
      rainTime +=dt;
      for(int i = 0; i < 80; i++ ){
          auto raindrop = make_unique<Rain>();
          raindrop->position = {linearRand(-9,9),linearRand(-13,25),-11};
          raindrop->speed = {0+windStrength,0,9.81};
          raindrop->rotation.z = float(windStrength*0.08);
          scene.objects.push_back(move(raindrop));
      }
      if(rainTime > rainTimer){
          rainTime = 0;
          rain = false;
      }
  }else{

      if(noRainTime > noRainTimer -5){
          if (scene.lightColor.x > 0.4f) scene.lightColor.x -= 0.1*dt;
          if (scene.lightColor.y > 0.4f) scene.lightColor.y -= 0.1*dt;
          if (scene.lightColor.z > 0.4f) scene.lightColor.z -= 0.1*dt;
          if (scene.lightColor2.x > 0.4f) scene.lightColor2.x -= 0.1*dt;
          if (scene.lightColor2.y > 0.4f) scene.lightColor2.y -= 0.1*dt;
          if (scene.lightColor2.z > 0.4f) scene.lightColor2.z -= 0.1*dt;
      }else{
          if (scene.lightColor.x < 1.0f) scene.lightColor.x += 0.8*dt;
          if (scene.lightColor.y < 1.0f) scene.lightColor.y += 0.8*dt;
          if (scene.lightColor.z < 1.0f) scene.lightColor.z += 0.8*dt;
          if (scene.lightColor2.x < 1.0f) scene.lightColor2.x += 0.8*dt;
          if (scene.lightColor2.y < 1.0f) scene.lightColor2.y += 0.8*dt;
          if (scene.lightColor2.z < 1.0f) scene.lightColor2.z += 0.8*dt;
      }
      if(wind){
          windStrength = 0;
          for ( auto& obj : scene.objects ) {
              // Ignore self in scene
              if (obj.get() == this)
                  continue;

              auto player = dynamic_cast<Player *>(obj.get());

              if (player) {
                  player->windForce(windStrength);
              }
          }
          wind = false;
      }
      noRainTime +=dt;
      if(noRainTime > noRainTimer){
          rain = true;
          noRainTime = 0;
      }
  }

  return true;
}

void Generator::render(Scene &scene) {
  // Generator will not be rendered
}


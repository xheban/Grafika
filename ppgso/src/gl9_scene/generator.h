#pragma once
#include "object.h"
#include "scene.h"

/*!
 * Example generator of objects
 * Constructs a new object during Update and adds it into the scene
 * Does not render anything
 */
class Generator final : public Object {
public:
  /*!
   * Generate new asteroids over time
   * @param scene Scene to update
   * @param dt Time delta
   * @return true to delete the object
   */
  bool update(Scene &scene, float dt) override;

  /*!
   * Render placeholder for generator
   * @param scene Scene to render in
   */
  void render(Scene &scene) override;

  float time = 0.0f;
  bool firstBoat = false;
  float mountainTime = 0.0f;
  float refreshTime = 17.8f;
  float refreshTimeBarrel = 8.0f;
  float barrelTime = 0.0f;
  float refreshTimeAmmo = 5.0f;
  float rainTime = 0.0f;
  float rainTimer = 10.0f;
  bool rain = false;
  float noRainTime = 0.0f;
  float noRainTimer = 20.0f;
  float ammoTime = 0.0f;
  float surfaceTime = 0.0f;
  float surfaceRefreshTime = 6.0f;
  bool wind;
  float windStrength;
};

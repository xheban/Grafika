#include <iostream>
#include <map>
#include <list>

#include <ppgso/ppgso.h>

#include "camera.h"
#include "scene.h"
#include "generator.h"
#include "player.h"
#include "water.h"
#include "fuelBar.h"
#include "ammoBar.h"
#include "fuelBarFill.h"
#include "winScene.h"
#include "looseScene.h"

using namespace std;
using namespace glm;
using namespace ppgso;

const unsigned int SIZE = 1600;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public Window {
private:
  Scene scene;
  bool animate = true;

  /*!
   * Reset and initialize the game scene
   * Creating unique smart pointers to objects that are stored in the scene object list
   */
  void initScene() {
    scene.objects.clear();

    // Create a camera
    auto camera = make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
    camera->position.z = -15.0f;
    scene.camera = move(camera);

    // Add space background
    scene.objects.push_back(make_unique<Water>());

    // Add generator to scene
    auto generator = make_unique<Generator>();
    generator->position.y = 10.0f;
    scene.objects.push_back(move(generator));

    // Add player to the scene
    auto player = make_unique<Player>();
    player->position.y = -8;
    scene.objects.push_back(move(player));

    //add fuel bar
    auto fuelBar = make_unique<FuelBar>();
    fuelBar->position.y = -10.8;
    fuelBar->position.x = -4;
    fuelBar->position.z = -3;
    fuelBar->rotation.x = 80;
    scene.objects.push_back(move(fuelBar));

    //add fuel bar
    auto fuelBarFill = make_unique<FuelBarFill>();
    fuelBarFill->position.y = -10.83;
    fuelBarFill->position.x = -4.87;
    fuelBarFill->position.z = -3;
    fuelBarFill->rotation.x = 80;
    scene.objects.push_back(move(fuelBarFill));

    //add ammo bar
    auto ammoBar = make_unique<AmmoBar>();
      ammoBar->position.y = -10.8;
      ammoBar->position.x = 4;
      ammoBar->position.z = -3;
      ammoBar->rotation.x = 80;
      ammoBar->rotation.y = 0.03f;
    scene.objects.push_back(move(ammoBar));
  }

    void initSceneWinGame() {
      scene.objects.clear();

      // Create a camera
      auto camera = make_unique<Camera>(60.0f, 1.0f, 0.1f, 200.0f);
      camera->position.y = 0.0f;
      camera->position.z = -15.0f;
      scene.camera = move(camera);
      //

      // Add space background
      scene.objects.push_back(make_unique<WinScene>());
    }

    void initSceneLooseGame() {
        scene.objects.clear();

        // Create a camera
        auto camera = make_unique<Camera>(60.0f, 1.0f, 0.1f, 200.0f);
        camera->position.y = 0.0f;
        camera->position.z = -15.0f;
        scene.camera = move(camera);
        //

        // Add space background
        scene.objects.push_back(make_unique<LooseScene>());
    }

public:
  /*!
   * Construct custom game window
   */
  SceneWindow() : Window{"gl9_scene", SIZE, SIZE} {
    //hideCursor();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    // Initialize OpenGL state
    // Enable Z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable polygon culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    initScene();
  }

  /*!
   * Handles pressed key when the window is focused
   * @param key Key code of the key being pressed/released
   * @param scanCode Scan code of the key being pressed/released
   * @param action Action indicating the key state change
   * @param mods Additional modifiers to consider
   */
  void onKey(int key, int scanCode, int action, int mods) override {
    scene.keyboard[key] = action;

    // Reset
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
      initScene();
    }

    // Pause
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
      animate = !animate;
    }
  }

  /*!
   * Handle cursor position changes
   * @param cursorX Mouse horizontal position in window coordinates
   * @param cursorY Mouse vertical position in window coordinates
   */
  void onCursorPos(double cursorX, double cursorY) override {
    scene.cursor.x = cursorX;
    scene.cursor.y = cursorY;
  }

  /*!
   * Handle cursor buttons
   * @param button Mouse button being manipulated
   * @param action Mouse bu
   * @param mods
   */
  void onMouseButton(int button, int action, int mods) override {
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
      scene.cursor.left = action == GLFW_PRESS;

      if (scene.cursor.left) {
        // Convert pixel coordinates to Screen coordinates
        float u = (scene.cursor.x / width - 0.5f) * 2.0f;
        float v = - (scene.cursor.y / height - 0.5f) * 2.0f;

        // Get mouse pick vector in world coordinates
        auto direction = scene.camera->cast(u, v);
        auto position = scene.camera->position;

        // Get all objects in scene intersected by ray
        auto picked = scene.intersect(position, direction);

        // Go through all objects that have been picked
        for (auto &obj: picked) {
          // Pass on the click event
          obj->onClick(scene);
        }
      }
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT) {
      scene.cursor.right = action == GLFW_PRESS;
    }
  }

  /*!
   * Window update implementation that will be called automatically from pollEvents
   */
  void onIdle() override {
    // Track time
    static auto time = (float) glfwGetTime();

    // Compute time delta
    float dt = animate ? (float) glfwGetTime() - time : 0;

    time = (float) glfwGetTime();

    // Set gray background
    glClearColor(.5f, .5f, .5f, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update and render all objects
    scene.update(dt);
    scene.render();

    if(scene.boatDestroyed > 10){
        initSceneWinGame();
      scene.boatDestroyed = 0;
    }

    if(scene.lost){
        initSceneLooseGame();
        scene.lost = false;
    }
  }
};

int main() {
  // Initialize our window
  SceneWindow window;

  // Main execution loop
  while (window.pollEvents()) {}

  return EXIT_SUCCESS;
}

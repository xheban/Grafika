#include "looseScene.h"
#include "scene.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

LooseScene::LooseScene() {
    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("endGame.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("quad.obj");
}

bool LooseScene::update(Scene &scene, float dt) {
    // Offset for UV mapping, creates illusion of scrolling
//  textureOffset -= dt/5;

    generateModelMatrix();
    return true;
}

void LooseScene::render(Scene &scene) {
    // Disable writing to the depth buffer so we render a "background"
    glDepthMask(GL_FALSE);

    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->use();

    // Pass UV mapping offset to the shader
    shader->setUniform("TextureOffset", textureOffset);
    shader->setUniform("lightColor", scene.lightColor3);

    // Render mesh, not using any projections, we just render in 2D
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("ViewMatrix", mat4{});
    shader->setUniform("ProjectionMatrix", mat4{});
    shader->setUniform("Texture", *texture);
    mesh->render();

    glDepthMask(GL_TRUE);
}

// shared resources
unique_ptr<Mesh> LooseScene::mesh;
unique_ptr<Shader> LooseScene::shader;
unique_ptr<Texture> LooseScene::texture;

#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 800
#define HEIGHT 600

int main() {

  Display display(WIDTH, HEIGHT, "Hello World!");

  Mesh mesh2("./res/block.obj");

  Shader shader("./res/basicShader");
  Texture texture("./res/block_uv_1.png");
  Camera camera(glm::vec3(0,0,-5), 70.0f, ((float) WIDTH) / HEIGHT, 
                0.01f, 1000.0f);
  Transform transform;
  
  float counter = 0.0f;

  while (!display.IsClosed()) {
    display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

    float sinCounter = sinf(counter);
    float cosCounter = cosf(counter);

    transform.GetPos().x = sinCounter;
    transform.GetPos().z = cosCounter;
    // transform.GetRot().x = counter;
    transform.GetRot().y = counter;
    // transform.GetRot().y = counter;
    // transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

    shader.Bind();

    texture.Bind(0);

    shader.Update(transform, camera);

    mesh2.Draw();

    display.Update();
    
    counter += 0.01f;
  }

  return 0;
}

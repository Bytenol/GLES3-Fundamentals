#include <iostream>
#include <string>
#include <mayhem/mayhem.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef __cplusplus
extern "C" {
#endif

using namespace std;
using namespace mhy;

float rotation;
float scale;
Shader shader;
int mMvp;
const int W = 400;
const int H = 540;


const string vertexShaderSource {R"(#version 300 es
layout (location=0) in vec3 position;

uniform mat4 mTransform;

void main() {
    gl_Position = mTransform * vec4(position, 1.0f);
}
)"};

const string fragmentShaderSource {R"(#version 300 es
precision highp float;

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)"};


void animate() {

    rotation += 0.01f;
    scale = 0.5f + glm::cos(rotation) * 0.5f;
    auto m = glm::mat4(1.0f) * 
        glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.76f, 0.32f, 0.5f)) *
        glm::scale(glm::mat4(1.0f), glm::abs(glm::vec3(scale, scale, scale)));
    

    glViewport(0, 0, W, H);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader.getProgram());
    glUniformMatrix4fv(mMvp, 1, false, glm::value_ptr(m));
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


int transformation_main() {
    
    if(!initWebgl2("#gl", W, H)) {
        std::cerr << getInfoLog() << std::endl;
        return -1;
    }

    std::cout << "Transformation.cpp" << std::endl;

    if(!shader.load(vertexShaderSource, fragmentShaderSource)) {
        std::cerr << getInfoLog() << std::endl;
    }

    float position[] {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
    };

    auto positionLength = sizeof position / sizeof(float);

    mMvp = glGetUniformLocation(shader.getProgram(), "mTransform");

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof position, position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

    emscripten_set_main_loop(animate, 0, 1);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return 0;
}

#ifdef __cplusplus
}
#endif
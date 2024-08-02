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


int image_main() {
    
    if(!initWebgl2("#gl", W, H)) {
        std::cerr << getInfoLog() << std::endl;
        return -1;
    }

    std::cout << "Image.cpp" << std::endl;
    Shader shader;
    if(!shader.load(vertexShaderSource, fragmentShaderSource)) {
        std::cerr << getInfoLog() << std::endl;
    }

    float position[] {
        // position
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };

    auto positionLength = sizeof position / sizeof(float);

    int mTransformLocation = glGetUniformLocation(shader.getProgram(), "mTransform");

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    glBufferData(GL_ARRAY_BUFFER, sizeof position, position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

    auto m = glm::mat4(1.0f);

    glViewport(0, 0, W, H);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader.getProgram());
    glUniformMatrix4fv(mTransformLocation, 1, false, glm::value_ptr(m));
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return 0;
}

#ifdef __cplusplus
}
#endif
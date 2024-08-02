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

Shader shader;
float rotation;
const int W = 400;
const int H = 540;
int mMvp, mProjLocation;


const string vertexShaderSource {R"(#version 300 es
layout (location=0) in vec3 position;
layout (location=1) in vec3 color;

uniform mat4 MVP;

out vec3 o_color;

void main() {
    o_color = color;
    gl_Position = MVP * vec4(position, 1.0f);
}
)"};

const string fragmentShaderSource {R"(#version 300 es
precision highp float;

in vec3 o_color;

out vec4 FragColor;

void main() {
    FragColor = vec4(o_color, 1.0f);
}
)"};


void animate() {
    rotation += 0.01f;

    float asp = 400 / 540;
    std::cout << asp << std::endl;  // output zero
    assert(asp > 0.7f); // assertion failed in javascript
    auto mProj = glm::perspective(glm::radians(45.f), 0.7407407407407407f, 0.1f, 100.0f);
    auto mView = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -10.0f));
    auto mModel = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.43f, 0.56f, 0.721f));

    auto mvp = mProj * mView * mModel;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glViewport(0, 0, W, H);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader.getProgram());
    glUniformMatrix4fv(mMvp, 1, false, glm::value_ptr(mvp));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(0));
}


int cube_main() {
    
    if(!initWebgl2("#gl", W, H)) {
        std::cerr << getInfoLog() << std::endl;
        return -1;
    }

    std::cout << "Cube.cpp" << std::endl;
    
    if(!shader.load(vertexShaderSource, fragmentShaderSource)) {
        std::cerr << getInfoLog() << std::endl;
    }

    float position[] {
        // Front face       // colors
        -1.0, -1.0, 1.0,    1.0f, 0.0f, 0.0f,
        1.0, -1.0, 1.0,     1.0f, 0.0f, 0.0f,
        1.0, 1.0, 1.0,      1.0f, 0.0f, 0.0f,
        -1.0, 1.0, 1.0,     1.0f, 0.0f, 0.0f,

        // Back face
        -1.0, -1.0, -1.0,   1.0f, 0.0f, 0.0f,
        -1.0, 1.0, -1.0,    1.0f, 0.0f, 0.0f,
        1.0, 1.0, -1.0,     1.0f, 0.0f, 0.0f,
        1.0, -1.0, -1.0,    1.0f, 0.0f, 0.0f,

        // Top face
        -1.0, 1.0, -1.0,    1.0f, 0.0f, 0.0f,
        -1.0, 1.0, 1.0,     1.0f, 0.0f, 0.0f,
        1.0, 1.0, 1.0,      1.0f, 0.0f, 0.0f,
        1.0, 1.0, -1.0,     1.0f, 0.0f, 0.0f,

        // Bottom face
        -1.0, -1.0, -1.0,   1.0f, 0.0f, 0.0f,
        1.0, -1.0, -1.0,    1.0f, 0.0f, 0.0f,
        1.0, -1.0, 1.0,     1.0f, 0.0f, 0.0f,
        -1.0, -1.0, 1.0,    1.0f, 0.0f, 0.0f,

        // Right face
        1.0, -1.0, -1.0,    1.0f, 0.0f, 0.0f,
        1.0, 1.0, -1.0,     1.0f, 0.0f, 0.0f,
        1.0, 1.0, 1.0,      1.0f, 0.0f, 0.0f,
        1.0, -1.0, 1.0,     1.0f, 0.0f, 0.0f,

        // Left face
        -1.0, -1.0, -1.0,   1.0f, 0.0f, 0.0f,
        -1.0, -1.0, 1.0,    1.0f, 0.0f, 0.0f,
        -1.0, 1.0, 1.0,     1.0f, 0.0f, 0.0f,
        -1.0, 1.0, -1.0,    1.0f, 0.0f, 0.0f,
    };

    int indices[36] {
        0,
    1,
    2,
    0,
    2,
    3, // front
    4,
    5,
    6,
    4,
    6,
    7, // back
    8,
    9,
    10,
    8,
    10,
    11, // top
    12,
    13,
    14,
    12,
    14,
    15, // bottom
    16,
    17,
    18,
    16,
    18,
    19, // right
    20,
    21,
    22,
    20,
    22,
    23, // left
    };

    mMvp = glGetUniformLocation(shader.getProgram(), "MVP");

    unsigned int vao, vbo, ibo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof position, position, GL_STATIC_DRAW);

    const int stride = 6 * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

    emscripten_set_main_loop(animate, 0, 1);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return 0;
}

#ifdef __cplusplus
}
#endif
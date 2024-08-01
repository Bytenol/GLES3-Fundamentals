#include <iostream>
#include <string>
#include <mayhem/mayhem.h>

#ifdef __cplusplus
extern "C" {
#endif

using namespace std;
using namespace mhy;

const string vertexShaderSource {R"(#version 300 es
layout (location=0) in vec3 position;
void main() {
    gl_Position = vec4(position, 1.0f);
}
)"};

const string fragmentShaderSource {R"(#version 300 es
precision highp float;

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)"};

int transformation_main() {
    const int W = 400;
    const int H = 540;

    if(!initWebgl2("#gl", W, H)) {
        std::cerr << getInfoLog() << std::endl;
        return -1;
    }

    std::cout << "Transformation.cpp" << std::endl;

    Shader shader;
    if(!shader.load(vertexShaderSource, fragmentShaderSource)) {
        std::cerr << getInfoLog() << std::endl;
    }

    float position[] {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
    };

    auto positionLength = sizeof position / sizeof(float);

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof position, position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

    glViewport(0, 0, W, H);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader.getProgram());
    glDrawArrays(GL_TRIANGLES, 0, positionLength / 3);

    return 0;
}

#ifdef __cplusplus
}
#endif
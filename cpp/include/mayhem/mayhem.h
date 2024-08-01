/**
 * @file mayhem.h
 * @date 01 sep, 2024
 * Helper include files by github.com/Bytenol
 */
#ifndef __EMS_MAYHEM_MAYHEM_HPP__
#define __EMS_MAYHEM_MAYHEM_HPP__

#include <string>
#include <climits>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>


namespace mhy {

    extern EmscriptenWebGLContextAttributes attributes;
    extern EMSCRIPTEN_WEBGL_CONTEXT_HANDLE renderer;
    extern std::string _infoLog;

    bool initWebgl2(std::string canvasId, int w, int h);

    const std::string& getInfoLog();

    void setInfoLog(const std::string& msg);


    class Shader {
        public:
            Shader() = default;
            bool load(const std::string& vs, const std::string& fs);
            const unsigned int& getProgram() const;
            void use();
            ~Shader();

        private:
            unsigned int createShader(GLenum type, const std::string& src);
            unsigned int program;
            unsigned int vertexShader;
            unsigned int fragmentShader;
    };

}

EMSCRIPTEN_BINDINGS(my_module) {
    // emscripten::function("getMyVariable", &mhy::getMyVariable);
}

#endif
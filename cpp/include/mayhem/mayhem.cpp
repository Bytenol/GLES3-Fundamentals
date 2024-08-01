#include "mayhem.h"

namespace mhy {

    std::string _infoLog;
    EmscriptenWebGLContextAttributes attributes;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE renderer;
    

    bool initWebgl2(std::string canvasId, int w, int h) {
        emscripten_webgl_init_context_attributes(&attributes);
        attributes.majorVersion = 2;
        const char* id = (canvasId).c_str();
        renderer = emscripten_webgl_create_context(id, &attributes);
        if(renderer <= 0) {
            setInfoLog("Unable to create webgl2 context");
            return false;
        }
        emscripten_webgl_make_context_current(renderer);
        emscripten_set_canvas_element_size(id, w, h);
        return true;
    }


    const std::string &getInfoLog() {
        return _infoLog;
    }


    void setInfoLog(const std::string &msg) {
        _infoLog = msg;
    };


    ///////////////////////////////////////////////
    ///////////////////////////////////////////////
    /////////       SHADER          ///////////////
    ///////////////////////////////////////////////
    ///////////////////////////////////////////////

    void Shader::use() {
        glUseProgram(program);
    };

    bool Shader::load(const std::string& vs, const std::string& fs) {
        vertexShader = createShader(GL_VERTEX_SHADER, vs);
        fragmentShader = createShader(GL_FRAGMENT_SHADER, fs);

        if(vertexShader == UINT_MAX || fragmentShader == UINT_MAX
            || !glIsShader(vertexShader) || !glIsShader(fragmentShader)) 
            return false;

        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        char infoLog[512];
        if(!success) {
            glGetShaderInfoLog(program, 512, nullptr, infoLog);
            setInfoLog(std::string{ "SHADER_PROGRAM_ERROR: " } + infoLog);
            glDeleteProgram(program);
            return false;
        }

        return true;
    }

    unsigned int Shader::createShader(GLenum type, const std::string& src) {
        auto shader = glCreateShader(type);
        const char* src_str = src.c_str();
        glShaderSource(shader, 1, &src_str, nullptr);
        glCompileShader(shader);
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        char infoLog[512];
        if(!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            setInfoLog(std::string{ "VERTEX_SHADER_ERROR: " } + infoLog);
            glDeleteShader(shader);
            return UINT_MAX;
        }

        return shader;
    }

    const unsigned int& Shader::getProgram() const {
        return program;
    }

    Shader::~Shader() {
        glDeleteProgram(program);
    }

}
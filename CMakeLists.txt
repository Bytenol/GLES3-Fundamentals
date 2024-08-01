cmake_minimum_required(VERSION 3.19)

project(GLES2_EMS)

if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER em++)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_FILES 
    "src/window.cpp"
    "src/triangle.cpp"
    "src/transformation.cpp"
)


SET(EXPORTED_RUNTIME_METHODS 
    cwrap,
    ccall
)

include_directories(cpp/deps/glm-master/glm)
include_directories(cpp/include)

foreach (SRC IN LISTS SRC_FILES)
    string(REGEX MATCH "[A-Z|a-z|0-9]+.cpp" FILE_NAME ${SRC})
    string(REPLACE ".cpp" "" FILE ${FILE_NAME})
    set(EXPORTED_FUNCTIONS 
        "_${FILE}_main"
    )
    string(REPLACE ";" "," EXPF ${EXPORTED_FUNCTIONS})    # comment this line and uncomment the down line
    # set(EXPF "")    # comment this line and uncomment the top line
    string(REPLACE ";" "," EXPR ${EXPORTED_RUNTIME_METHODS})
    add_executable(${FILE} "cpp/src/${FILE}.cpp" "cpp/include/mayhem/mayhem.cpp")
    set_target_properties(${FILE} PROPERTIES 
        LINK_FLAGS "-s EXPORTED_FUNCTIONS=\"[${EXPF}]\" \
        -s EXPORTED_RUNTIME_METHODS=\"[${EXPR}]\" -s USE_WEBGL2=1 -s FULL_ES3=1 \
        -s EXPORT_NAME='Module' --bind"
    
        OUTPUT_NAME src/${FILE}/${FILE}
        SUFFIX ".js"
    )
endforeach ()
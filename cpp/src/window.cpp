#include <iostream>
#include <mayhem/mayhem.h>


#ifdef __cplusplus
extern "C" {
#endif 


int window_main() {
    if (!mhy::initWebgl2("#gl", 480, 600)) {
        std::cout << mhy::getInfoLog() << std::endl;
        return -1;
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    return 0;
}


#ifdef __cplusplus
}
#endif
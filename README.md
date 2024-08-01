# GLES3 Fundamental

This repository contains the implementation of some opengl_es written in c++ and runnable on the web browser. Thanks to [Emscripten](https://emscripten.org/).

You can find the compiled version runnable in a browser inside the emscripten/ directory.

## How to run
1. clone the repository or download the zipped folder. if neccessary, unzip the folder and open the project.

2. Start a local server from the project's root directory. Open your web browser and navigate to web/ path in your browser. If on a local server, the path may look like `http://localhost:port/web`. 

3. Here, you can open any .html file and see their corresponding output

## How to compile (Yourself)
Well the CMakeLists.txt has been written nicely. However, you have to ensure that you have atleast cmake 3.19 and emscripten installed on your system. After this, you may follow the following steps
1. Delete the current `web/` folder and create a new one (with the same name)
2. inside the web folder, you should create a `src/` folder, this is where all javascript and wasm files will be located after compilation
3. Now here is the job, you have to create folders for every .cpp file present in `cpp/src` inside the `web/src` folder. This implies for window.cpp, there should be a folder `web/src/window/` ... This must be completed for all other sources before trying to compile, otherwise it will fail
4. now open cmd/bash inside your web folder and run the command
```bash
emcmake cmake ../ && emmake make
```
5. After executing the command, your binaries and javascript source are ready. Create a .html for each of them and add the javascript source as a script tag to where the emscripten generated js file is. It is ideal to have your web files inside the web/ root directory, then for each file, you can add a script like this
`<script src="./src/window/window.js"></script>`.
6. This wont load your webgl code yet, you have to call the main function for that project inside a script tag, preferrably after window.onload. It may look like this
```javascript
Module.onRuntimeInitialized = () => {
    // for window.cpp
    Module._window_main();
    // for triangle.cpp
    // Module._triangle_main(); etc...
}
```

## How to contribute
This is an open source project licensed under Apache2.0, but really, i don't give a damn on how you use it and what you use it for. However, if you would like to add more examples of your openGL_es project to this repository, you can create an issue explaining what it is. i will check it and open a branch for it.

## More
I would like to acknowledge [emscripten](https://emscripten.org) as a great tool, honestly what it does is fricking awesome. Learn OPENGL in c++ and make a runnable and playable game for the browser without the need to learn webgl seperately.

it is also worth mentioning that these sites helps alot in understanding opengl and webgl stuff. you should check them out

- [Webgl2 Fundamental](https://webgl2fundamentals.org/)
- [Learn Opengl](https://learnopengl.com/Introduction)
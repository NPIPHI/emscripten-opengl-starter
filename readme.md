<h2>
Minimal openGL emscripten example
</h2>
Based on the excellent tutorial at 
<a href="http://www.opengl-tutorial.org/">http://www.opengl-tutorial.org/</a>
<br>
Get emscripten at <a href="https://emscripten.org/">https://emscripten.org/</a>
<br>
<br>
This is a minimal openGL program that compiles for both native and the web. It is based on GLEW and GLFW3.
<br>
<br>
Please note that this is not necessarily the cleanest or most correct way of doing things.
<br>
<br>
Before building you must change the directory path located in src/sourceDir.h to the path on your system that points to the folder containing the CMakeLists.txt file.
This is to make the emscripten file system work the same as the native one. (There is probably a better way to do this, but i couldn't find it)
<br>
<br>
To build for native run

```commandline
mkdir build-native
cd build-native
cmake ..
make
main.exe
```
 
To build for emscripten run

```commandline
mkdir build-wasm
cd build-wasm
emcmake cmake ..
emmake make
```
and then open main.html in your favorite browser. 
You will have to open main.html on a local server if you see an error message about cross origin requests. You can easily install one with 

```commandline
npm install http-server -g
http-server
```


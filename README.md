ModelViewer
===========

Deferred OpenGL renderer

Compiling
---------

Dependencies:
* GLEW
* GLFW
* GLM

To compile using the XCode project, simply change the header include path and library path to match where you have the libraries inside XCode.

The Makefile (tested on Debian) will look for the library header files in an include directory in the project root. It will look for the libraries in a lib directory in the project root. This can easily be changed in the Makefile.
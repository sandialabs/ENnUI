# Quickstart

## Installation with conan
While building and installing without [conan](https://conan.io/) is possible, the following simplified processes requires conan.

To install the python binding
```shell title="building with conan" linenums="1"
pip install .
```
To build unit tests
```shell title="building with conan" linenums="1"
conan install .
cmake --preset conan-default
cmake --build . --preset conan-release
```
Python and MATLAB bindings are built specifying the appropriate -D flag
```shell title="generator for Python bindings" linenums="2"
cmake --preset conan-default -DPYTHON_MODULE=true
```
```shell title="generator for MATLAB dll" linenums="2"
cmake --preset conan-default -DMATLAB_DLL=true
```

Note, MATLAB and python use conflicting matrix layouts. Deleting the build folder is recommended when switching between build generators.

## Run unit-tests
The terminal command to call the unit-test executable varies with the operating system
``` title="Windows, run unit tests" linenums="4"
.\build\bin\Release\ennui_test.exe
```
``` title="Unix, run unit tests" linenums="4"
./build/Release/bin/ennui_test
```
## Demos
Check out demos of [python bindings](demos/pyennui_demo.ipynb) and [matlab bindings](demos/mennui_build_library.md)

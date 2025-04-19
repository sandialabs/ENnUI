# Quickstart

## Python
Install the python package ``pyennui`` locally using ```pip```
```shell title="python" linenums="1"
pip install .
```
From python, evaluate the gravitation vector at the White House.

```python linenums="1"
import numpy as np
from pyennui.geodetic import gravitation_ecef

WhiteHouse_ECEF = np.array(
    (1.1150423452941689e06, -4.8438122981491517e06, 3.9835202164462707e06)
)

gravitation_ecef(WhiteHouse_ECEF)
```

## C++ Unit tests
While building without [conan](https://conan.io/) is possible, the following simplified processes requires conan.

To build with conan
```shell title="building with conan" linenums="1"
conan build .
```
Unit tests are run by calling the output. For windows systems
```shell title="building with conan" linenums="1"
.\build\bin\Release\ennui_test.exe
```
For unix systems
``` title="Unix, run unit tests" linenums="4"
./build/Release/bin/ennui_test
```

## MATLAB
 MATLAB bindings are built specifying the appropriate option
```shell title="generator for MATLAB dll" linenums="2"
conan build . -o with_matlab=True
```
Similarly, the python binding can be built
```shell title="generator for Python bindings" linenums="2"
conan build . -o with_python=True
```
Note, MATLAB and python use conflicting matrix layouts. Deleting the build folder is recommended when switching between build generators.

## Demos
Check out demos of [python bindings](demos/pyennui_demo.ipynb) and [matlab bindings](demos/mennui_build_library.md)


# Building and Demonstrating Matlab ENnUI Library

While `cmake` was used to build a C++ library MATLAB could stomach (limited C++ support), a library interface must still be compiled. As long as a compiler is available, the process is fairly straight\-forward.

# Generate library definition

The first step is using `generateLibraryDefinition` to auto\-generate two metafiles in the current folder.

-  `definemennui.m`
-  `mennuiData.xml`

Note, `generateLibraryDefinition` is fairly primitive in terms of C++ variable types understood. In this case, the `mennui.lib` interface ("mennui.hpp") was designed such that `definemennui.m` should require no modifications.

```matlab
% Main header file
hFile = fullfile(".","src","mennui.hpp");
% Include path for header files
iPath = [fullfile("..","build","matlab","src")]; % "Ennui_Export.h"
libFile = fullfile("..","build","bin","Release","mennui.lib");
assert(exist(libFile,'file'),"Looks like you did not build the matlab library yet.")

clibgen.generateLibraryDefinition(hFile,IncludePath=iPath,Libraries=libFile,OverwriteExistingDefinitionFiles=true,Verbose=true)
```

```matlabTextOutput
Deleted file 'C:\repos\ennui\matlab\definemennui.m'.
C++ compiler set to 'Microsoft Visual C++ 2019'.
Definition file definemennui.m contains definitions for 2 constructs supported by MATLAB.
- 2 constructs are fully defined.
To build the interface, call build(definemennui).
```
# Build

Build the \*.dll which MATLAB will call directly, and add its folder to the path.

```matlab
build(definemennui)
```

```matlabTextOutput
Building interface file 'mennuiInterface.dll' for clib interface 'mennui'.
Build Log:
cl /c /Zc:__cplusplus /Zp8 /GR /W3 /EHs /nologo /MD /O2 /Oy- /DNDEBUG   -I"C:\repos\ennui\build\matlab\src" -I"C:\Program Files\MATLAB\R2024a\extern\include"  "C:\repos\ennui\matlab\mennui\mennuiInterface.cpp" /Fo"C:\repos\ennui\matlab\mennui\mennuiInterface.obj"
mennuiInterface.cpp

link /nologo  /DLL  "C:\repos\ennui\matlab\mennui\mennuiInterface.obj"  "..\build\bin\Release\mennui.lib" "C:\Program Files\MATLAB\R2024a\extern\lib\win64\microsoft\libMatlabDataArray.lib"     /OUT:"C:\repos\ennui\matlab\mennui\mennuiInterface.dll" "C:\repos\ennui\matlab\mennui\mennuimeta_res.res"
   Creating library C:\repos\ennui\matlab\mennui\mennuiInterface.lib and object C:\repos\ennui\matlab\mennui\mennuiInterface.exp

---
Interface file 'mennuiInterface.dll' built in folder 'C:\repos\ennui\matlab\mennui'.

To use the library, add the interface file folder to the MATLAB path.
addpath('C:\repos\ennui\matlab\mennui')
Execution mode 'mennui' set to 'outofprocess'. To modify, call clibConfiguration('mennui','ExecutionMode','inprocess').
```

```matlab
addpath('C:\repos\ennui\matlab\mennui')
```

Input argumnet WhiteHouse\_ECEF

```matlab
p = [1.1150423452941689E+06, -4.8438122981491517E+06, 3.9835202164462707E+06];
% Return argument
g = clibArray('clib.mennui.Double',3);
clib.mennui.geodetic.gravitation_ecef(p,g)

gamma = [-1.7170260919766687E+00, 7.4588665943134185E+00, -6.1541304311837033E+00];
assert(max(abs(g.double - gamma))<1e-14);
disp("success.")
```

```matlabTextOutput
success.
```
# Clean up

In case things went sideways, this should clean things up.

```matlab
%{
!del definemennui.m
!del mennuiData.xml
clibConfiguration('mennui','ExecutionMode','outofprocess')
unload(clibConfiguration('mennui'))
rmpath('C:\repos\ennui\matlab\mennui')
clc;
%}
```

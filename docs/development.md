# Development
User binaries can be built with minimal requirements, however additional tools are required for style enforcement and building documentation locally. Most packages - but not all - are available through pip. [Pip is recommended over conda to ensure latest packages](https://github.com/pre-commit/pre-commit/issues/1946#issuecomment-1482296790). For the most-recent examples see the CI/CD pipeline (e.g. `before-script` commands in `.gitlab-ci.yml`).

## Recommended Dependencies

External : [`cmake`](https://cmake.org/), `clang-format` (e.g. distributed with [`llvm`](https://llvm.org/)), and [`doxygen`](https://www.doxygen.nl/).

Within a python virtual environment:
```
pip install conan pre-commit mkdocs-material mkdoxy
```
## Pre-Commit Hooks
[Pre-commit](https://pre-commit.com/) hooks are automatically evaluated in the CI/CD pipeline according to the configuration file `.pre-commit-config.yaml`. These checks can be run locally, once `pre-commit` is installed (e.g. `pip` above), by installing the git-hook scripts
```
pre-commit install
```
Only files tracked (staged) by git will be checked when committing. To run against all files
```
pre-commit run --all-files
```

## Building Documentation
Documentation is published using [mkdocs-material](https://squidfunk.github.io/mkdocs-material/), [doxygen](https://www.doxygen.nl/), and [mkdoxy](https://github.com/JakubAndrysek/MkDoxy). Website style and navigation are configured in `mkdocs.yml`, while site content are stored in `.\docs\`.

### Publishing documentation locally

Docs can be generated and hosted locally using
```
mkdocs serve
```
Documentation is automatically published through CI/CD.

### Publishing MATLAB demos
Since R2023b, Live Scripts can be published to markdown directly. To publish Live Scripts in the matlab subfolder, to the doc/demos subfolder as markdown, use

```shell title="publish to markdown" linenums="1"
script_name = "mennui_build_library";
export(script_name+".mlx",fullfile("..","docs","demos",script_name+".md"),Format="markdown")
```

## Style Guides & Enforcement

Aspirational style guides and enforcement. :)

| Language | Guides | Enforcement |
|----------|-------|-------------|
| C/C++ | [Google](https://google.github.io/styleguide/cppguide.html), [Cpp Core](https://isocpp.github.io/CppCoreGuidelines) | [clang-format](https://clang.llvm.org/docs/ClangFormat.html)|
| Python | [Pep8](https://peps.python.org/pep-0008/) | [Black](https://github.com/psf/black) |
| MATLAB | [FileExchange](https://www.mathworks.com/matlabcentral/fileexchange/45047-matlab-style-guidelines-cheat-sheet)| [MISS_HIT](https://misshit.org/) |

### House-style
* include guard: use `#pragma once`, not `#ifndef`.

* Naming conventions
  * `snake_case` (lower case, underscore delimited) for variables, files, namespaces
  * `UpperCamelCase` (capitalize first and each word) for classes and types
  * `ALL_CAPS` for macros and `static constexpr`.
* Organization
  * Subfolders under `Ennui` correspond with namespaces. C++ namespaces correspond with packages in both python and MATLAB. Each file may warrant an additional namespace. For example, a collection of functions.
  * Use using-declarations, not using-directives.
* API Design
  * For internal C++ functions, favor return by value and rely on named returned value optimization (NRVO).
  * For external interfaces, favor return by reference to avoid memcopies in C.
* C++ Documentation vs Comments
  * Use doxygen-compatible comment blocks to document all public and protected C++ components
    * Multi-line blocks: /** */
    * Single-line documentation: //!
  * Comments (not to appear in documentation), use single line comments: //, or C++ style /*  */

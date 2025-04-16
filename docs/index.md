# Introduction

ENnUI : exemplar navigator using inertial sensors

/// html | div[style='float: left; width: 55%;']
[ENnUI](https://github.com/sandialabs/ENnUI) is a library for inertial navigation providing a collection of reference mechanization equations. Implementing inertial navigation algorithms requires many design decisions from the state space, error models, and estimation frameworks. Design decisions are often application-specific depending on trajectory dynamics, sensor fidelity, and computational resources. Numerically, results are sensitive to the geodetic model parameters as earth-centered navigation is a poorly scaled problem. Our goal is not to implement state-of-the-art performance in terms of fidelity or computational efficiency. Instead, we focus on re-packaging well-known algorithms in a portable framework for benchmarking purposes. ENnUI provides a reference library which can be used to quantify design decisions and benefit future algorithms.
///

/// html | div[style='float: right;width: 38%;']
**exemplar**[@Merriam_Webster_2024] `ex·​em·​plar`, `ig-ˈzem-ˌplär`
*noun*
one that serves as a model or example: such as

1. <s>an ideal model</s>
2. a typical or standard specimen
3. a copy of a book or writing

///

/// html | div[style='clear: both;']
///

## License

ENnUI is distributed as open-source software under a MIT License (see the [LICENSE](https://github.com/sandialabs/ENnUI/blob/main/LICENSE) file for details). SNL open source approval reference scr-3197.

Sandia National Laboratories is a multimission laboratory managed and operated by National Technology & Engineering Solutions of Sandia, LLC, a wholly owned subsidiary of Honeywell International Inc., for the U.S. Department of Energy’s National Nuclear Security Administration under contract DE-NA0003525.

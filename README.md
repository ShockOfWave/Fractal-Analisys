# Fractal-Analisys

![GitHub](https://img.shields.io/github/license/ShockOfWave/Fractal-Analisys)
![GitHub last commit](https://img.shields.io/github/last-commit/ShockOfWave/Fractal-Analisys)
![GitHub pull requests](https://img.shields.io/github/issues-pr/ShockOfWave/Fractal-Analisys)
![contributors](https://img.shields.io/github/contributors/ShockOfWave/Fractal-Analisys) 
![codesize](https://img.shields.io/github/languages/code-size/ShockOfWave/Fractal-Analisys)
![GitHub repo size](https://img.shields.io/github/repo-size/ShockOfWave/Fractal-Analisys)
![GitHub top language](https://img.shields.io/github/languages/top/ShockOfWave/Fractal-Analisys)
![GitHub language count](https://img.shields.io/github/languages/count/ShockOfWave/Fractal-Analisys)



# Introduction

...

# Functionality tested

- [x] Debian based systems
- [ ] Windows
- [ ] MacOS

# Installation

* Copy repository on your machine
```bash
git clone git@github.com:ShockOfWave/Fractal-Analisys.git
```
* Install libgsl for your system
    * For apt package manager:
    ```bash
    sudo apt install libgsl-dev
    ```
    * For brew package manager:
    ```bash 
    brew intall gsl
    ```
* Also you will need Python3, virtualenv and make
    * Python3
    ```bash
    sudo apt install python3.10
    ```
    * Virtualenv
    ```bash
    sudo apt install python3-venv
    ```
    * Make
    ```bash
    sudo apt install make
    ```
* Install all dependencies:
```bash
make install
```
* Other commands you can check by
```bash
make help
```

* (Optional) Install pre-commit:
```bash
pre-commit install
```


# Usage

## Check package
You can use our data to test package:
```bash
source venv/bin/activate
python -m src example_data
```

Or you can test package with make:
```bash
make test_lacunarity
```

## Other options

You can run calculation on one process or to one file:
```bash
python -m src -h
```

# Future work
- [x] Write C++ code for lacunarity calculation
  - [ ] Improve speed of calculation
  - [ ] Make better integration of cpp code into python
  - [ ] Improve OOP for C++ code
- [x] Write base python bindings
- [x] Make compile C++ code with pip
- [x] Add multiprocessing in Python
- [ ] Add more TDA calculation
- [ ] Add animation for slices
- [ ] Create API

# Acknowledgments/References
We thank the [Infochemistry Scientific Center ISC](https://infochemistry.ru) for the provided data and computing power.

# Reference & Citation

Will be later...

# License
The code is distributed under the [MIT license](https://opensource.org/license/mit/).

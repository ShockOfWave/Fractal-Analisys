# Fractal-Analisys

![GitHub](https://img.shields.io/github/license/ShockOfWave/Fractal-Analisys)
![GitHub last commit](https://img.shields.io/github/last-commit/ShockOfWave/Fractal-Analisys)
![GitHub pull requests](https://img.shields.io/github/issues-pr/ShockOfWave/Fractal-Analisys)
![contributors](https://img.shields.io/github/contributors/ShockOfWave/Fractal-Analisys) 
![codesize](https://img.shields.io/github/languages/code-size/ShockOfWave/Fractal-Analisys)
![GitHub repo size](https://img.shields.io/github/repo-size/ShockOfWave/Fractal-Analisys)

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
* Install python dependencies:
```bash
pip install .
```

# Usage

You can use our data to test package:
```bash
python -m src
```

If you want to use your own data, change input folder in `__main__.py`

```python
def main():
    all_files = find_files('example_data')
    ...
```

# Future work
- [x] Write C++ code for lacunarity calculation
  - [ ] Improve speed of calculation
  - [ ] Make better integration of cpp code into python
  - [ ] Improve OOP for C++ code
- [x] Write base python bindings
- [x] Make compile C++ code with pip
- [ ] Add more TDA calculation
- [ ] Add animation for slices
- [ ] Create API

# Acknowledgments/References
We thank the [Infochemistry Scientific Center ISC](infochemistry.ru) for the provided data and computing power.

# Reference & Citation

Will be later...

# License
The code is distributed under the [MIT license](https://opensource.org/license/mit/).
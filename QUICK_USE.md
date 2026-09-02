# HLITE QUICK USE

> Welcome to HLITE Quick Use 👋.

## Description

Make sure you have installed the Hlite quick use release framework in the GitHub repository. There are 2 ways to compile HLITE Quick Use, with the c++ compiler directly or with CMAKE.
In this short tutorial we will explain these two methods.

---

## Compile this Project

### A. With a direct C++ Compiler

1. Create a directory or folder as a container for the output, for example `bin`.
    ```bash
    mkdir bin
    ```

2. Use the C++ compiler, for example I use `gcc`, more precisely `g++`. Follow this command. The command here uses Windows, it's different if you use Linux or MACOS.
    ```bash
    g++ -std=c++20 -Wall -Wextra -o bin/<name_application> src/*.cpp -Llib/HLITE/lib -Ilib/HLITE/include -Ilib/HLITE/raylib/include -Llib/HLITE/raylib/lib -lhlite -lraylib -lopengl32 -lgdi32 -lwinmm
    ```

### B. With CMake as Build Automation.

1. Create a directory or folder as a container for the output, for example `bin`.
    ```bash
    mkdir bin
    ```

2. Init CMake as a workspace project.
    ```bash
    cmake -S . -B bin -G Ninja
    # or
    cmake -S . -B bin -G Ninja -DAPP_NAME=<name_executable>
    ```

3. Build the project with CMake.
    ```bash
    cmake --build bin
    ```

### Run the application. 
```bash
./bin/<name_executable>
```

---
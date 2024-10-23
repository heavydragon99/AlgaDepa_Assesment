[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mNdixtYF)

# depaAlgo

## How to Run the Program

### Prerequisites

Make sure you have CMake, a C++ compiler, SDL2, and CURL and gtest installed on your system.

### Building the Project

1. Navigate to the `code` directory:
```sh
    cd code
```

2. Create the build directory if it doesn't exist:
```sh
    mkdir -p build
```

3. Navigate to the build directory:
```sh
    cd build
```

4. Run CMake to configure the project:
```sh
    cmake ..
```

5. Build the project:
```sh
    cmake --build . --parallel 16
```

### Running the Program

To run the program normally, execute the following command from the `build` directory:
```sh
    cmake --build . --target run --parallel 16
```

### Running with Debug Information

To build and run the project with debug information, execute the following command from the `build` directory:
```sh
    cmake .. -DENABLE_DEBUG=ON && cmake --build . --target run_debug --parallel 16    
```

### Running the Program with Valgrind

To run the program with Valgrind to check for memory leaks, execute the following command from the `build` directory:
```sh
    cmake --build . --target run_valgrind --parallel 16
```

Note: this make the program very very slow. Recommended to lower the update frequency of the view and game logic. These can be found in controller.h

### Running Tests

To run the tests using GTest, execute the following command from the `build` directory:
```sh
    cmake --build . --target run_tests --parallel 16
```
[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mNdixtYF)

# depaAlgo

## How to Run the Program

### Prerequisites

Make sure you have CMake, a C++ compiler, SDL2, and CURL installed on your system.

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
    make
    ```

### Running the Program

To run the program normally, execute the following command from the `build` directory:
```sh
./depaAlgo
```

### Building and Running with Debug Information

To build the project with debug information, follow these steps:

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

4. Run CMake with the `-DDEBUG_BUILD=ON` option to configure the project:
    ```sh
    cmake -DDEBUG_BUILD=ON ..
    ```

5. Build the project:
    ```sh
    make
    ```

6. Run the program with debug information:
    ```sh
    ./depaAlgo
    ```

### Running the Program with Valgrind

To run the program with Valgrind to check for memory leaks, execute the following command from the `build` directory:
```sh
make valgrind
```
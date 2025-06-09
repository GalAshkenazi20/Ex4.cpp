# MyContainer Project

## About

This project implements a C++ class called `MyContainer`, representing a dynamic container that supports multiple iteration orders.  
The class provides various iterator types, allowing traversal of elements in ascending, descending, reverse, side-cross, middle-out, and original insertion orders.  
Additionally, the container supports element addition, removal, modification, and error handling.

---

## Project Structure

- **MyContainer.hpp**  
  Defines the `MyContainer` class, its members, methods, and iterator types.

- **Iterator.hpp**  
  Abstract base class for all iterator types, providing the foundation for custom traversal patterns.

- **AscendingOrder.hpp**  
  Implements an iterator that traverses elements in ascending (sorted) order.

- **DescendingOrder.hpp**  
  Implements an iterator that traverses elements in descending order.

- **ReverseOrder.hpp**  
  Implements an iterator that traverses elements in reverse insertion order.

- **SideCrossOrder.hpp**  
  Implements an iterator that alternates between smallest and largest remaining elements.

- **MiddleOutOrder.hpp**  
  Implements an iterator that starts from the middle element and expands outward.

- **Order.hpp**  
  Implements an iterator that traverses elements in their original insertion order.

- **main.cpp**  
  A demonstration file showcasing the features of `MyContainer` and its iterators.

- **test.cpp**  
  Contains unit tests for all the features of `MyContainer`, written using the Doctest framework.  
  Tests cover normal functionality, edge cases, and exceptions.

- **Makefile**  
  Allows easy compilation and execution of the project, tests, and memory checking.

---

## Key Features

- Create dynamic containers of any type.
- Add and remove elements from the container.
- Traverse elements using six different iterator types:
  - Ascending order
  - Descending order
  - Reverse order
  - Side-cross order
  - Middle-out order
  - Original insertion order
- Modify elements directly through iterators.
- Preserve original order while supporting custom traversal patterns.
- Handle errors gracefully (e.g., removing non-existent elements, accessing invalid indices).
- Full support for exception safety and memory management.

---

## How to Compile and Run

You can use the **Makefile** provided in the project.

### Available Commands:

| Command         | Description |
|-----------------|-------------|
| `make Main`     | Compile `main.cpp` and `MyContainer` files to create `main_exec`. Run the demo of the project. |
| `make test`     | Compile `test.cpp` and `MyContainer` files to create `test_exec`. Run all unit tests. |
| `make valgrind` | Run the unit tests under Valgrind to detect memory leaks and memory errors. |
| `make clean`    | Delete all executables and temporary files to clean the project directory. |

---

## Usage Instructions

### 1. Run the Main Demo
```bash
make main
./main
```
**Expected Output:**

- Containers will be created and printed to the screen.
- Various operations will be demonstrated, including:
  - Adding and removing elements
  - Traversing elements using different iterator types
  - Modifying values through iterators
  - Error handling for invalid operations

---

### 2. Run the Unit Tests

```bash
make test
./test
```

**Expected Output:**

- All unit tests will run automatically.
- If everything is implemented correctly, all tests should pass successfully.
- You will see a green success message from the Doctest framework indicating that all tests passed.

---

### 3. Check for Memory Leaks

```bash
make valgrind
```

**Expected Output:**

- Valgrind will analyze the program's memory usage during the tests.
- At the end of the run, you should see the message:
  ```
  All heap blocks were freed -- no leaks are possible
  ```
- If any memory errors or leaks are detected, they will be reported.
- Fix any issues immediately before submitting the project!

---

### 4. Clean the Project

```bash
make clean
```

**Expected Output:**

- Deletes `main_exec`, `test_exec`, and any other generated files.
- Only source files (`.cpp`, `.hpp`) and documentation files (`README.md`, `Makefile`) will remain.
- This keeps your project directory clean and organized.

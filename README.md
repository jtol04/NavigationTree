# NavigationTree
A navigation tree implementation using C++

## Folder Structure
    
```plaintext
    NavigationTree/
    ├── build/                   
    │   └── Makefile             # Build config
    ├── include/                 # Header files
    │   ├── file.h               # File class declaration
    │   ├── folder.h             # Folder class declaration
    │   ├── node.h               # Node class and NodeType enum
    │   └── tree.h               # Tree class declaration
    ├── src/                     # Source files
    │   ├── file.cpp             # File class implementation
    │   ├── folder.cpp           # Folder class implementation
    │   ├── main.cpp             # Demo
    │   ├── node.cpp             # Node class implementation
    │   └── tree.cpp             # Tree class implementation
    ├── test/                    # 
    │   └── test.cpp             # Google unit test
    └── README.md                
```

## References
1. https://c2cxx.github.io/www/2025-9/
2. https://en.cppreference.com/w/cpp/language/enum.html
2. https://google.github.io/googletest/primer.html

## Build demo
```bash
cd build
make
```

## Run demo
```bash
./main
```

## Build test
```bash
cd build
make test
```

## Run test
```bash
./test
```

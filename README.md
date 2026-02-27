# NavigationTree
A navigation tree implementation using C++. All basic features have been implemented. Optional save and load tree features have also been implemented.

## Folder Structure
    
```plaintext
    NavigationTree/
    ├── build/                   
    │   └── Makefile             # Build configuration
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
1. https://c2cxx.github.io/www/2025-9/ (previous semester class; comprehensize C++ resource)
2. https://en.cppreference.com/w/cpp/language/enum.html
3. https://google.github.io/googletest/primer.html (reference for Google Unit Tests)
4. https://github.com/nlohmann/json (reference for saving the Tree as JSON)


## Dependencies
### Mac
```bash
brew install nlohmann-json
brew install googletest
```


### Linux
```bash
sudo apt-get install nlohmann-json3-dev
sudo apt-get install libgtest-dev
```

## Build and run demo
```bash
cd build
make
./main
```


## Build and run test (Google Unit Test)
```bash
cd build
make test
./test
```

#include "file.h"

File::File(std::string filename) {
    name = filename;
    type = NodeType::FILE;
}
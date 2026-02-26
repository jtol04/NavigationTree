#include "folder.h"

Folder::Folder(std::string foldername) {
    name = foldername;
    type = NodeType::FOLDER;
}
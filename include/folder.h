#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <unordered_map>
#include "node.h"

class Folder : public Node {
public:
    Folder(std::string foldername);
    std::unordered_map<std::string, std::unique_ptr<Node>> children_map;
};

#endif
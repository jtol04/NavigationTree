#ifndef _FILE_H_
#define _FILE_H_

#include "node.h"

class File : public Node {
public:
    File(std::string filename);
};

#endif
#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <atomic>

class Folder;

enum class NodeType { FILE, FOLDER };

class Node {
public:
    Node() : unique_id(++id) {};
    virtual ~Node() = default;
    std::string name;
    Folder* parent_folder = nullptr;
    NodeType type;
    inline int get_id() { return unique_id; }
    
private:
    int unique_id;
    static std::atomic<int> id;
};

#endif
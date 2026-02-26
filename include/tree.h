#ifndef _TREE_H_
#define _TREE_H_

#include <memory>
#include <string>
#include <deque>
#include "folder.h"
#include "file.h"

class Tree {
public:
    Tree(std::string rootName);
    bool create_folder(const std::string& path_to_folder);
    bool create_file(const std::string& path_to_file);
    bool delete_node(const std::string& path_to_node);
    bool rename_node(const std::string& path_to_node, const std::string& new_node_name);
    bool move_node(const std::string& path_to_node, const std::string& path_to_dest_folder);

    void print_tree();

private:
    std::unique_ptr<Folder> root;
    std::deque<std::string> parse_path(const std::string& path_to_node);
    Folder* get_folder_ptr(std::deque<std::string> tokens);
    Node* find_child(Folder* folder, const std::string& name);
    void print_tree_helper(Folder* folder, int depth);
    NodeType get_type(const std::string& path_to_node);
    bool is_subtree(Node* origin, Folder* dest_folder);
};

#endif
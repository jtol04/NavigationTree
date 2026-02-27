#ifndef _TREE_H_
#define _TREE_H_

#include <memory>
#include <string>
#include <deque>
#include "folder.h"
#include "file.h"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Tree {
public:
    Tree(std::string rootName);
    bool create_folder(const std::string& path_to_folder);
    bool create_file(const std::string& path_to_file);
    bool delete_node(const std::string& path_to_node);
    bool rename_node(const std::string& path_to_node, const std::string& new_node_name);
    bool move_node(const std::string& path_to_node, const std::string& path_to_dest_folder);
    
    void print_tree();
    bool save_tree(const std::string& path_to_file);
    bool load_tree(const std::string& path_to_json);

private:
    std::unique_ptr<Folder> root;

    /**
     * @brief Reads the path string and splits it based on '/' delimeter
     * @param path_to_node The absolute path to be parsed
     * @return A deque containing the parsed tokens
     */
    std::deque<std::string> parse_path(const std::string& path_to_node);
    
    /**
     * @brief Traverses the tree and checks the folder specified exists. 
     * @param tokens parsed path components
     * @return Pointer to the folder specified, otherwise nullptr if the path is invalid 
     */
    Folder* get_folder_ptr(std::deque<std::string> tokens);

    /**
     * @brief Checks if a child exists within a specified folder
     * @param folder The pointer to the parent folder
     * @param name The name of the child to be checked 
     * @return Pointer to the child if found, otherwise nullptr
     */
    Node* find_child(Folder* folder, const std::string& name);

    /**
     * @brief Recursively prints the tree node names and indents based on depth
     * @param folder The pointer to the folder
     * @param depth The depth of the folder
     */
    void print_tree_helper(Folder* folder, int depth);

    /**
     * @brief Checks if the specified node is a file or a folder based on the trailing slash
     * @note Paths ending in '/' are treated as FOLDER, FILE otherwise
     * @param path_to_node The path leading to the node to be checked
     * @return The type of the node (e.g. FILE or FOLDER)
     */
    NodeType get_type(const std::string& path_to_node);

    /**
     * @brief Checks if the destination folder is inside the subtree of the origin.
     * @param origin The node being attempted to be moved
     * @param dest_folder The destination folder of the move
     * @return true if dest_folder is a descendant of origin, otherwise false 
     */
    bool is_subtree(Node* origin, Folder* dest_folder);

    /**
     * @brief Shared implementation for create_file and create_folder
     * @param path_to_node The path to the node being created
     * @param type The type of the node being created
     * @return true if node was created, otherwise false
     */
    bool create_node_helper(const std::string& path_to_node, NodeType type);

    /**
     * @brief Converts the specified folder into a JSON object
     * @param folder The pointer to the folder to be converted into a json
     * @return JSON of the folder
     */
    json folder_to_json(Folder* folder);

    /**
     * @brief Reconstructs the tree from JSON object
     * @param parnet_folder The folder where children will be inserted
     * @param j The JSON object representing parent folder
     */
    bool json_to_node(Folder* parent_folder, const json& j);

};

#endif
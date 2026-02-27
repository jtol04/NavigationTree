#include "tree.h"
#include <memory>
#include <sstream>
#include <queue>
#include <iostream>
#include <string>

Tree::Tree(std::string rootName) {
    root = std::make_unique<Folder>(rootName);
}

std::deque<std::string> Tree::parse_path(const std::string& path_to_node) {
    std::stringstream ss{path_to_node};
    std::string token;
    std::deque<std::string> tokens;

    while (std::getline(ss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

Node* Tree::find_child(Folder* folder, const std::string& name) {
    if (folder->children_map.find(name) != folder->children_map.end()) {
        return folder->children_map[name].get();
    } 
    
    return nullptr; 
}

Folder* Tree::get_folder_ptr (std::deque<std::string> tokens ) {
    if (tokens.empty()) {
        //std::cerr << "<get_folder_ptr> Error: No path to folder.\n";
        return nullptr;
    }

    Folder* curr = root.get();

    if (curr->name == tokens.front()) {
        tokens.pop_front();
    } else {
        std::cerr << "<get_folder_ptr> Error: Invalid Root.\n";
        return nullptr;
    }

    while (!tokens.empty()) {
        std::string token = tokens.front();
        Node* child_node = find_child(curr, token);
        if (child_node && child_node->type == NodeType::FOLDER) {
            tokens.pop_front();
            curr = dynamic_cast<Folder*>(child_node);
        } else {
            break;
        }
    }

    if (tokens.empty()) {
        return curr;
    } else {
        std::cerr << "<get_folder_ptr> Error: Invalid Path.\n";
        return nullptr;
    }
}

NodeType Tree::get_type(const std::string& path_to_node) {
    if (path_to_node.back() == '/') {
        return NodeType::FOLDER;
    } else {
        return NodeType::FILE;
    }
}

bool Tree::create_node_helper(const std::string& path_to_node, NodeType type) {
    std::deque<std::string> tokens = parse_path(path_to_node);
    std::string node_name = tokens.back();
    tokens.pop_back();

    Folder* parent_folder = get_folder_ptr(tokens);
    if (!parent_folder) {  return false; }
    if (find_child(parent_folder, node_name) != nullptr) { 
        std::cerr << "<create_node> Error: Duplicate detected.\n";
        return false; 
    }
    
    if (type == NodeType::FILE) {
        parent_folder->children_map[node_name] = std::make_unique<File>(node_name);
    } else {
        parent_folder->children_map[node_name] = std::make_unique<Folder>(node_name);
    }
    parent_folder->children_map[node_name]->parent_folder = parent_folder;
    // std::cout << "node: " << parent_folder->children_map[node_name]->get_id() << " created.\n";

    return true;
}

bool Tree::create_folder(const std::string& path_to_folder) {
    return create_node_helper(path_to_folder, NodeType::FOLDER);
}

bool Tree::create_file(const std::string& path_to_file) {
    return create_node_helper(path_to_file, NodeType::FILE);
}

bool Tree::delete_node(const std::string& path_to_node) {
    std::deque<std::string> tokens = parse_path(path_to_node);
    NodeType node_to_delete_type = get_type(path_to_node);
    std::string node_to_delete_name = tokens.back();
    tokens.pop_back();

    Folder* parent_folder = get_folder_ptr(tokens);
    if (parent_folder == nullptr && node_to_delete_name == root->name) { 
        std::cerr << "<delete_node> Error: Root can't be deleted.\n";
        return false;
    } 

    if (parent_folder == nullptr) { 
        std::cerr << "<delete_node> Error: Invalid path.\n";
        return false;
    } 

    Node* existing_node = find_child(parent_folder, node_to_delete_name);
    if (existing_node == nullptr) {
        std::cerr << "<delete_node> Error: Invalid path.\n";
        return false;
    }

    if (existing_node->type != node_to_delete_type) {
        std::cerr << "<delete_node> Error: " << path_to_node << " has the wrong type.\n";
        return false;
    }
    parent_folder->children_map.erase(node_to_delete_name);
    return true;
}

bool Tree::rename_node(const std::string& path_to_node, const std::string& new_node_name) {
    std::deque<std::string> tokens = parse_path(path_to_node);
    std::string old_node_name = tokens.back();
    tokens.pop_back();

    Folder* parent_folder = get_folder_ptr(tokens);
    if (!parent_folder) { return false; } 

    Node* old_node = find_child(parent_folder, old_node_name);
    if (old_node == nullptr) {
        std::cerr << "<rename_node> Error: Invalid path.\n";
        return false;
    }

    if (find_child(parent_folder, new_node_name) != nullptr) {
        std::cerr << "<rename_node> Error: Name already exists.\n";
        return false;
    }

    auto it = parent_folder->children_map.find(old_node_name);
    parent_folder->children_map[new_node_name] = std::move(it->second);
    parent_folder->children_map.erase(old_node_name);
    parent_folder->children_map[new_node_name]->name = new_node_name;
    
    return true;
}
bool Tree::move_node(const std::string& path_to_node, const std::string& path_to_dest_folder){
    std::deque<std::string> origin_tokens = parse_path(path_to_node);
    std::string node_name = origin_tokens.back();
    origin_tokens.pop_back();

    Folder* origin_parent_folder = get_folder_ptr(origin_tokens);
    
    if (origin_parent_folder == nullptr && node_name == root->name) { 
        std::cerr << "<move_node> Error: Root can't be moved.\n";
        return false; 
    } 

     if (origin_parent_folder == nullptr) { 
        std::cerr << "<move_node> Error: Invalid path.\n";
        return false; 
    } 

    Node* node = find_child(origin_parent_folder, node_name);
    if (node == nullptr) {
        std::cerr << "<move_node> Error: Invalid origin path.\n";
        return false;
    }

    std::deque<std::string> dest_tokens = parse_path(path_to_dest_folder);
    Folder* new_parent_folder = get_folder_ptr(dest_tokens);

    if (new_parent_folder == nullptr) {
        std::cerr << "<move_node> Error: Invalid destination path.\n";
        return false;
    }

    if (origin_parent_folder == new_parent_folder) {
        std::cerr << "<move_node> Error: Origin folder is the same as the destination folder.\n";
        return false;
    }

    if (is_subtree(node, new_parent_folder)) {
        std::cerr << "<move_node> Error: Subtree detected.\n";
        return false;
    }

    if (find_child(new_parent_folder, node_name)) {
        std::cerr << "<move_node>: Duplicate detected in destination folder.\n";
        return false;
    }

    
    auto it = origin_parent_folder->children_map.find(node_name);
    new_parent_folder->children_map[node_name] = std::move(it->second);
    node->parent_folder = new_parent_folder;
    origin_parent_folder->children_map.erase(node_name);
    return true;
}

bool Tree::is_subtree(Node* origin, Folder* dest_folder) {
    if (dest_folder == origin) {
        return true;
    }

   Folder* current_folder = dest_folder;

    while (current_folder->parent_folder != nullptr) {
        if (current_folder->parent_folder == origin) {
            return true;
        }
        current_folder = current_folder->parent_folder;
    }
    return false;
}

void Tree::print_tree() {
    Folder* curr = root.get();
    int depth = 0;

    print_tree_helper(curr, depth);
}


void Tree::print_tree_helper(Folder* folder, int depth) {
    
    auto& children_map = folder->children_map;
    std::string indent(depth * 2 , ' ');
    std::cout << indent << folder->name << "/\n";
    
    for (auto it = children_map.begin(); it != children_map.end(); ++it) {
        if (it->second->type == NodeType::FOLDER) {
            Folder* child_folder = dynamic_cast<Folder*>(it->second.get());
            
            print_tree_helper(child_folder, depth + 1);
        } else {
            std::string file_indent((depth + 1) * 2 , ' ');
            std::cout << file_indent << it->second->name << "\n";
        }
    }
}

json Tree::folder_to_json(Folder* folder) {
    json j;
    j["name"] = folder->name;
    j["type"] = "FOLDER";
    j["unique_id"] = folder->get_id();
    j["children"] = json::array();

    for (auto& [name, node] : folder->children_map) {
        if (node->type == NodeType::FOLDER) {
            Folder* child_folder = dynamic_cast<Folder*>(node.get());
            j["children"].push_back(folder_to_json(child_folder));
        } else {
            json file;
            file["name"] = node->name;
            file["type"] = "FILE";
            file["unique_id"] = node->get_id();
            j["children"].push_back(file);
        }
    }
    return j;
}

bool Tree::save_tree(const std::string& path_to_file) {
    Folder* folder = root.get();
    json root = folder_to_json(folder);
    std::ofstream output(path_to_file);

    if (!output) {
        std::cerr << "<save> Error: Could not open file.\n";
        return false;
    }
    output << root.dump(2);
    return true;
}

void Tree::json_to_node(Folder* parent_folder, const json& j) {
    for (auto& child : j["children"]) {
        std::string name = child["name"];
        if (child["type"] == "FOLDER") {
            parent_folder->children_map[name] = std::make_unique<Folder>(name);
            parent_folder->children_map[name]->parent_folder = parent_folder;
            Folder* child_folder = dynamic_cast<Folder*>(parent_folder->children_map[name].get());
            json_to_node(child_folder, child);
        } else {
            parent_folder->children_map[name] = std::make_unique<File>(name);
            parent_folder->children_map[name]->parent_folder = parent_folder;
        }
    }
}
bool Tree::load_tree(const std::string& path_to_json) {
    std::ifstream input(path_to_json);
    if (!input) {
        std::cerr << "<load> Error: Could not open file.\n";
    }

    json j = json::parse(input);
    root = std::make_unique<Folder>(j["name"]);
    json_to_node(root.get(), j);

    return true;
}


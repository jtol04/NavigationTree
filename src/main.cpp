#include "tree.h"

int main() {

    Tree tree("Project");
     
    tree.create_folder("/Project/src/");
    tree.rename_node("/Project/src/", "src1");
    tree.create_file("/Project/src1/main.py");
    tree.create_folder("/Project/src1/models/");
    tree.delete_node("/Project/src1/models/");
    tree.create_folder("/Project/tests/");
    tree.create_file("/Project/tests/test_main.py");
    tree.create_file("/Project/README.md");
    tree.create_file("/Project/main.md");
    tree.move_node("/Project/src1/", "/Project/tests/");

    tree.save_tree("tree.json");

    Tree new_tree("temp");
    new_tree.load_tree("tree.json");
    new_tree.print_tree();
} 
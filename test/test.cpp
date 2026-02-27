#include <gtest/gtest.h>
#include "tree.h"

class TreeTest : public testing::Test {
protected:
    void SetUp() override {
    // Code here will be called immediately after the constructor (right before each test).
        tree.create_folder("/Project/src/");
        tree.create_folder("/Project/to_delete/");
        tree.create_folder("/Project/src/models/");
        tree.create_file("/Project/README.md");
        tree.create_file("/Project/test.txt");       
    }

    Tree tree{"Project"};
    Tree new_tree{"Temp"};
};

TEST_F(TreeTest, CreateFolder) {
    EXPECT_TRUE(tree.create_folder("/Project/tests/"));
}

TEST_F(TreeTest, CreateFile) {
    EXPECT_TRUE(tree.create_file("/Project/main.py"));
}

TEST_F(TreeTest, CreateDuplicateFolder) {
    EXPECT_FALSE(tree.create_folder("/Project/src/"));
}

TEST_F(TreeTest, CreateDuplicateFile) {
    EXPECT_FALSE(tree.create_file("/Project/test.txt"));
}

TEST_F(TreeTest, DeleteFolder) {
    EXPECT_TRUE(tree.delete_node("/Project/to_delete/"));
}

TEST_F(TreeTest, DeleteFile) {
    EXPECT_TRUE(tree.delete_node("/Project/README.md"));
}

TEST_F(TreeTest, DeleteNonExistingPath) {
    EXPECT_FALSE(tree.delete_node("/Project/invalid.md"));
}

TEST_F(TreeTest, DeleteRoot) {
    EXPECT_FALSE(tree.delete_node("/Project/"));
}

TEST_F(TreeTest, RenameNode) {
    EXPECT_TRUE(tree.rename_node("/Project/test.txt", "new.txt"));
}

TEST_F(TreeTest, RenameNodeThatDoesntExist) {
    EXPECT_FALSE(tree.rename_node("/Project/fail", "new.txt"));
}

TEST_F(TreeTest, RenameNodeAlreadyExists) {
    tree.create_folder("/Project/tests/");
    tree.create_folder("/Project/test1/");
    EXPECT_FALSE(tree.rename_node("/Project/test1/", "tests"));
}


TEST_F(TreeTest, MoveNode) {
    tree.create_folder("/Project/new_folder/");
    EXPECT_TRUE(tree.move_node("/Project/src/models", "Project/new_folder/"));
}

TEST_F(TreeTest, MoveNodeAlreadyExists) {
    tree.create_folder("/Project/models/");
    EXPECT_FALSE(tree.move_node("/Project/src/models/", "Project/"));
}

TEST_F(TreeTest, MoveToSubtree) {
    EXPECT_FALSE(tree.move_node("/Project/src/", "Project/src/models"));
}

TEST_F(TreeTest, MoveRoot) {
    EXPECT_FALSE(tree.move_node("/Project/", "Project/new_folder/"));
}


TEST_F(TreeTest, SaveTree) {
    EXPECT_TRUE(tree.save_tree("test.json"));
}

TEST_F(TreeTest, LoadTree) {
    tree.save_tree("test.json");
    EXPECT_TRUE(new_tree.load_tree("test.json"));
}


TEST_F(TreeTest, LoadTreeNoExist) {
    EXPECT_FALSE(new_tree.load_tree("noexist.json"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
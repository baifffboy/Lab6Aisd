#include "pch.h"
#include "TUnorderedTable.h"
#include "Unordered_Table_on_forward_list.h"
#include "Ordered_Table.h"
#include "Hash_Table.h"
#include "AVLTree.h"
#include "RedBlackTree.h"

// TUnorderedTable Tests
TEST(TUnorderedTableTest, insertion) {
    TUnorderedTable<int, std::string> table("Key", "Value");
    EXPECT_TRUE(table.create_record(1, "first", true));
    EXPECT_TRUE(table.create_record(2, "second", true));
}

TEST(TUnorderedTableTest, duplicate_key_with_replacement) {
    TUnorderedTable<int, std::string> table("Key", "Value");
    table.create_record(1, "first", true);
    EXPECT_TRUE(table.create_record(1, "updated", true));
    EXPECT_EQ(*table.search_of_value(1), "updated");
}

TEST(TUnorderedTableTest, duplicate_key_without_replacement) {
    TUnorderedTable<int, std::string> table("Key", "Value");
    table.create_record(1, "first", true);
    table.create_record(1, "conflict", false);
    EXPECT_NE(table.search_of_value(1), nullptr);
    EXPECT_EQ(*table.search_of_value(1), "first");
}

TEST(TUnorderedTableTest, search) {
    TUnorderedTable<int, std::string> table("Key", "Value");
    table.create_record(1, "first", true);
    EXPECT_NE(table.search_of_value(1), nullptr);
    EXPECT_EQ(*table.search_of_value(1), "first");
    EXPECT_EQ(table.search_of_value(3), nullptr);
}

TEST(TUnorderedTableTest, deletion) {
    TUnorderedTable<int, std::string> table("Key", "Value");
    table.create_record(1, "first", true);
    EXPECT_NE(table.delete_value(1), nullptr);
    EXPECT_EQ(table.search_of_value(1), nullptr);
    EXPECT_EQ(table.delete_value(99), nullptr);
}

// Unordered_Table_on_forward_list Tests
TEST(UnorderedTableForwardListTest, insertion) {
    Unordered_Table_on_forward_list<int, std::string> table("Key", "Value");
    EXPECT_TRUE(table.create_last_node(1, "first", true, false));
    EXPECT_TRUE(table.create_last_node(2, "second", true, false));
}

TEST(UnorderedTableForwardListTest, duplicate_key_with_replacement) {
    Unordered_Table_on_forward_list<int, std::string> table("Key", "Value");
    table.create_last_node(1, "first", true, false);
    EXPECT_TRUE(table.create_last_node(1, "updated", true, false));
}

TEST(UnorderedTableForwardListTest, duplicate_key_without_replacement) {
    Unordered_Table_on_forward_list<int, std::string> table("Key", "Value");
    table.create_last_node(1, "first", true, false);
    EXPECT_FALSE(table.create_last_node(1, "conflict", false, false));
}

TEST(UnorderedTableForwardListTest, search) {
    Unordered_Table_on_forward_list<int, std::string> table("Key", "Value");
    table.create_last_node(1, "first", true, false);
    EXPECT_NE(table.search_of_value(1), nullptr);
    EXPECT_EQ(*table.search_of_value(1), "first");
    EXPECT_EQ(table.search_of_value(3), nullptr);
}

TEST(UnorderedTableForwardListTest, deletion) {
    Unordered_Table_on_forward_list<int, std::string> table("Key", "Value");
    table.create_last_node(1, "first", true, false);
    EXPECT_NE(table.delete_value(1), nullptr);
    EXPECT_EQ(table.search_of_value(1), nullptr);
    EXPECT_EQ(table.delete_value(99), nullptr);
}

TEST(UnorderedTableForwardListTest, size) {
    Unordered_Table_on_forward_list<int, std::string> table("Key", "Value");
    table.create_last_node(1, "first", true, false);
    EXPECT_EQ(table.return_size(), 1);
}

// Ordered_Table Tests
TEST(OrderedTableTest, insertion_and_ordering) {
    Ordered_Table<int, std::string> table("Key", "Value");
    EXPECT_TRUE(table.create_last_node(3, "three", true, false));
    EXPECT_TRUE(table.create_last_node(1, "one", true, false));
    EXPECT_TRUE(table.create_last_node(2, "two", true, false));
    
    // Verify order by searching
    EXPECT_NE(table.search_of_value(1), nullptr);
    EXPECT_NE(table.search_of_value(2), nullptr);
    EXPECT_NE(table.search_of_value(3), nullptr);
}

TEST(OrderedTableTest, search) {
    Ordered_Table<int, std::string> table("Key", "Value");
    table.create_last_node(1, "one", true, false);
    table.create_last_node(2, "two", true, false);
    
    EXPECT_NE(table.search_of_value(2), nullptr);
    EXPECT_EQ(*table.search_of_value(2), "two");
    EXPECT_EQ(table.search_of_value(4), nullptr);
}

TEST(OrderedTableTest, deletion) {
    Ordered_Table<int, std::string> table("Key", "Value");
    table.create_last_node(1, "one", true, false);
    table.create_last_node(2, "two", true, false);
    
    EXPECT_NE(table.delete_value(2), nullptr);
    EXPECT_EQ(table.search_of_value(2), nullptr);
}

// Hash_Table Tests
TEST(HashTableTest, insertion_and_search) {
    Hash_Table<std::string> table("Key", "Value", 1, 100);
    table.create_record("first");
    table.create_record("second");
    
    EXPECT_NE(table.search_of_value("first"), nullptr);
    EXPECT_EQ(*table.search_of_value("first"), "first");
    EXPECT_EQ(table.search_of_value("missing"), nullptr);
}

TEST(HashTableTest, deletion) {
    Hash_Table<std::string> table("Key", "Value", 1, 100);
    table.create_record("first");
    table.create_record("second");
    
    EXPECT_TRUE(table.delete_value("second"));
    EXPECT_EQ(table.search_of_value("second"), nullptr);
    EXPECT_FALSE(table.delete_value("missing"));
}

// AVLTree Tests
TEST(AVLTreeTest, insertion_and_search) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    
    EXPECT_NE(tree.search(1), nullptr);
    EXPECT_EQ(*tree.search(1), "one");
    EXPECT_EQ(tree.search(3), nullptr);
}

TEST(AVLTreeTest, deletion) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    
    EXPECT_NE(tree.remove(1), nullptr);
    EXPECT_EQ(tree.search(1), nullptr);
}

// RedBlackTree Tests
TEST(RedBlackTreeTest, insertion_and_search) {
    RedBlackTree<int, std::string> tree;
    tree.insert(2, "two", true);
    tree.insert(3, "three", true);
    
    EXPECT_NE(tree.search(2), nullptr);
    EXPECT_EQ(tree.search(2)->value, "two");
    EXPECT_EQ(tree.search(4), nullptr);
}

TEST(RedBlackTreeTest, deletion) {
    RedBlackTree<int, std::string> tree;
    tree.insert(2, "two", true);
    tree.insert(3, "three", true);

    EXPECT_TRUE(tree.contains(2));
    tree.remove(2);
    EXPECT_FALSE(tree.contains(2));
    EXPECT_TRUE(tree.isRedBlackTreeValid());  // Проверка свойств
}
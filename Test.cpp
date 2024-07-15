// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Tree.hpp"
#include "Complex.hpp"

using namespace std;

// Test Node creation and validation
TEST_CASE("Validate Node creation and initial state") {
    // Integer Node
    Node<int> nodeInt(20);
    CHECK(nodeInt.get_value() == 20);
    CHECK(nodeInt.children.empty());

	Node<bool> nodeBool(true);
    CHECK(nodeBool.get_value() == true);
    CHECK(nodeBool.children.empty());


    Node<char> nodeChar('A');
    CHECK(nodeChar.get_value() == 'A');
    CHECK(nodeChar.children.empty());


    // String Node
    Node<string> nodeStr("Example");
    CHECK(nodeStr.get_value() == "Example");
    CHECK(nodeStr.children.empty());


    // Floating Point Node
    Node<double> nodeDouble(2.718);
    CHECK(nodeDouble.get_value() == 2.718);
    CHECK(nodeDouble.children.empty());


    // Complex Node
    Node<Complex> nodeComplex(Complex(2, 3));
    CHECK(nodeComplex.get_value().getReal() == 2);
    CHECK(nodeComplex.get_value().getImag() == 3);
    CHECK(nodeComplex.children.empty());

}

// Test Tree structure and node addition
TEST_CASE("Initialize Tree and add nodes") {
    Tree<int> intTree;
    Node<int> root(100);
    intTree.add_root(root);
    CHECK(intTree.getRoot()->get_value() == 100);

    Node<int> childA(50);
    Node<int> childB(150);
    intTree.add_sub_node(root, childA);
    intTree.add_sub_node(root, childB);

    CHECK(intTree.getRoot()->children.size() == 2);
    CHECK(intTree.getRoot()->children[0]->get_value() == 50);
    CHECK(intTree.getRoot()->children[1]->get_value() == 150);

    // Adding more children
    Node<int> childC(25);
    Node<int> childD(75);
    intTree.add_sub_node(childA, childC);
    intTree.add_sub_node(childA, childD);

    CHECK(intTree.getRoot()->children[0]->children.size() == 2);
    CHECK(intTree.getRoot()->children[0]->children[0]->get_value() == 25);
    CHECK(intTree.getRoot()->children[0]->children[1]->get_value() == 75);
}

// Test different traversal techniques
TEST_CASE("Different traversal methods") {
    Tree<int> intTree;
    Node<int> root(10);
    intTree.add_root(root);
    Node<int> n1(20);
    Node<int> n2(30);
    Node<int> n3(40);
    Node<int> n4(50);
    Node<int> n5(60);

    intTree.add_sub_node(root, n1);
    intTree.add_sub_node(root, n2);
    intTree.add_sub_node(n1, n3);
    intTree.add_sub_node(n1, n4);
    intTree.add_sub_node(n2, n5);

    SUBCASE("Pre-order") {
        std::vector<int> values;
        for (auto node = intTree.begin_pre_order(); node != intTree.end_pre_order(); ++node) {
            values.push_back(node->get_value());
        }
        std::vector<int> expected = {10, 20, 40, 50, 30, 60};
        CHECK(values == expected);
    }

    SUBCASE("Post-order") {
        std::vector<int> values;
        for (auto node = intTree.begin_post_order(); node != intTree.end_post_order(); ++node) {
            values.push_back(node->get_value());
        }
        std::vector<int> expected = {40, 50, 20, 60, 30, 10};
        CHECK(values == expected);
    }

    SUBCASE("In-order") {
        std::vector<int> values;
        for (auto node = intTree.begin_in_order(); node != intTree.end_in_order(); ++node) {
            values.push_back(node->get_value());
        }
        std::vector<int> expected = {40, 20, 50, 10, 60, 30};
        CHECK(values == expected);
    }

    SUBCASE("BFS") {
        std::vector<int> values;
        for (auto node = intTree.begin_bfs_scan(); node != intTree.end_bfs_scan(); ++node) {
            values.push_back(node->get_value());
        }
        std::vector<int> expected = {10, 20, 30, 40, 50, 60};
        CHECK(values == expected);
    }

    SUBCASE("DFS") {
        std::vector<int> values;
        for (auto node = intTree.begin_dfs_scan(); node != intTree.end_dfs_scan(); ++node) {
            values.push_back(node->get_value());
        }
        std::vector<int> expected = {10, 20, 40, 50, 30, 60};
        CHECK(values == expected);
    }
}

// Test Tree memory management
TEST_CASE("Ensure memory management and destructor") {
    Tree<int>* dynamicTree = new Tree<int>();
    Node<int> root(5);
    dynamicTree->add_root(root);
    Node<int> child(10);
    dynamicTree->add_sub_node(root, child);

    // Ensure proper memory deallocation
    delete dynamicTree;
}

TEST_CASE("Heap operations and verification") {
    Tree<int> heapTree;
    Node<int> root(70);
    heapTree.add_root(root);
    Node<int> n1(80);
    Node<int> n2(90);
    Node<int> n3(100);
    Node<int> n4(110);
    Node<int> n5(120);
    Node<int> n6(130);

    heapTree.add_sub_node(root, n1);
    heapTree.add_sub_node(root, n2);
    heapTree.add_sub_node(n1, n3);
    heapTree.add_sub_node(n1, n4);
    heapTree.add_sub_node(n2, n5);
    heapTree.add_sub_node(n2, n6);

    std::vector<int> values;
    for (auto node = heapTree.begin_heap(); node != heapTree.end_heap(); ++node) {
        values.push_back(node->get_value());
    }

    std::vector<int> expected = {70, 80, 90, 100, 110, 120, 130};
    CHECK(values == expected);
}

// Extended test case for Heap operations
TEST_CASE("Extended heap operations and verification") {
    Tree<int> heapTree;
    Node<int> root(200);
    heapTree.add_root(root);
    Node<int> n1(150);
    Node<int> n2(300);
    Node<int> n3(100);
    Node<int> n4(180);
    Node<int> n5(250);
    Node<int> n6(400);

    heapTree.add_sub_node(root, n1);
    heapTree.add_sub_node(root, n2);
    heapTree.add_sub_node(n1, n3);
    heapTree.add_sub_node(n1, n4);
    heapTree.add_sub_node(n2, n5);
    heapTree.add_sub_node(n2, n6);

    std::vector<int> values;
    for (auto node = heapTree.begin_heap(); node != heapTree.end_heap(); ++node) {
        values.push_back(node->get_value());
    }

    // Adjusted expected values to match min-heap order
    std::vector<int> expected = {100, 150, 180, 200, 250, 300, 400};
    CHECK(values == expected);
}

// Test Tree operations with k-ary nodes
TEST_CASE("Tree operations with k-ary nodes") {
    Tree<string, 4> stringTree;
    Node<string> root("root");
    stringTree.add_root(root);
    CHECK(stringTree.getRoot()->get_value() == "root");

    Node<string> child1("A");
    Node<string> child2("B");
    Node<string> child3("C");
    Node<string> child4("D");
    Node<string> child5("E");

    stringTree.add_sub_node(root, child1);
    stringTree.add_sub_node(root, child2);
    stringTree.add_sub_node(root, child3);

    CHECK(stringTree.getRoot()->children[0]->get_value() == "A");
    CHECK(stringTree.getRoot()->children[1]->get_value() == "B");
    CHECK(stringTree.getRoot()->children[2]->get_value() == "C");
}

// Extended test for Tree operations with k-ary nodes
TEST_CASE("Extended Tree operations with k-ary nodes") {
    Tree<int, 5> intTree;
    Node<int> root(10);
    intTree.add_root(root);
    CHECK(intTree.getRoot()->get_value() == 10);

    Node<int> child1(20);
    Node<int> child2(30);
    Node<int> child3(40);
    Node<int> child4(50);
    Node<int> child5(60);
    Node<int> child6(70);

    intTree.add_sub_node(root, child1);
    intTree.add_sub_node(root, child2);
    intTree.add_sub_node(root, child3);
    intTree.add_sub_node(root, child4);

    CHECK(intTree.getRoot()->children[0]->get_value() == 20);
    CHECK(intTree.getRoot()->children[1]->get_value() == 30);
    CHECK(intTree.getRoot()->children[2]->get_value() == 40);
    CHECK(intTree.getRoot()->children[3]->get_value() == 50);

    intTree.add_sub_node(child1, child6);
    CHECK(intTree.getRoot()->children[0]->children.size() == 1);
    CHECK(intTree.getRoot()->children[0]->children[0]->get_value() == 70);
}

// Test DFS on integer trees
TEST_CASE("DFS traversal for integer trees") {
    Tree<int> dfsTree;
    Node<int> root(25);
    dfsTree.add_root(root);
    Node<int> n1(35);
    Node<int> n2(45);
    Node<int> n3(55);
    Node<int> n4(65);
    Node<int> n5(75);

    dfsTree.add_sub_node(root, n1);
    dfsTree.add_sub_node(root, n2);
    dfsTree.add_sub_node(n1, n3);
    dfsTree.add_sub_node(n1, n4);
    dfsTree.add_sub_node(n2, n5);

    std::vector<int> values;
    for (auto node = dfsTree.begin_dfs_scan(); node != dfsTree.end_dfs_scan(); ++node) {
        values.push_back(node->get_value());
    }

    std::vector<int> expected = {25, 35, 55, 65, 45, 75};
    CHECK(values == expected);
}

// Test k-ary tree traversals
TEST_CASE("K-ary tree DFS and BFS traversal") {
    Tree<string, 3> kAryTree;
    Node<string> root("root");
    kAryTree.add_root(root);
    CHECK(kAryTree.getRoot()->get_value() == "root");

    Node<string> child1("child1");
    Node<string> child2("child2");
    Node<string> child3("child3");
    Node<string> child4("child4");
    Node<string> child5("child5");
    Node<string> child6("child6");

    kAryTree.add_sub_node(root, child1);
    kAryTree.add_sub_node(root, child2);
    kAryTree.add_sub_node(root, child3);
    kAryTree.add_sub_node(child1, child4);
    kAryTree.add_sub_node(child1, child5);
    kAryTree.add_sub_node(child2, child6);

    SUBCASE("DFS traversal for k-ary tree") {
        std::vector<string> values;
        for (auto node = kAryTree.begin_dfs_scan(); node != kAryTree.end_dfs_scan(); ++node) {
            values.push_back(node->get_value());
        }

        std::vector<string> expected = {"root", "child1", "child4", "child5", "child2", "child6", "child3"};
        CHECK(values == expected);
    }

    SUBCASE("BFS traversal for k-ary tree") {
        std::vector<string> values;
        for (auto node = kAryTree.begin_bfs_scan(); node != kAryTree.end_bfs_scan(); ++node) {
            values.push_back(node->get_value());
        }

        std::vector<string> expected = {"root", "child1", "child2", "child3", "child4", "child5", "child6"};
        CHECK(values == expected);
    }
}

// Test edge cases for adding nodes
TEST_CASE("Edge cases for adding nodes") {
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(root);

    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    CHECK_THROWS(tree.add_sub_node(child3, child4)); // Adding to a node not in the tree

    CHECK_NOTHROW(tree.add_sub_node(child1, child3));
    CHECK(tree.getRoot()->children.size() == 2);
    CHECK(tree.getRoot()->children[0]->children.size() == 1);
    CHECK(tree.getRoot()->children[0]->children[0]->get_value() == 4);
}

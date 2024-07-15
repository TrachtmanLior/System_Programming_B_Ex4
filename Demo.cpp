// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include "Complex.hpp"
#include "TreeDrawer.hpp"

using namespace std;

int main() {
    // Create SFML window for binary tree
    sf::RenderWindow window1(sf::VideoMode(1000, 600), "Binary Tree Drawing");

    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */
    drawTree(window1, tree);

    // Display the window until it is closed
    window1.display();

    // SFML event loop for the binary tree window
    while (window1.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();
        }
    }
  
    cout << "Binary Tree Traversals:\n" << endl;
    
    cout << "Pre-order traversal (DFS):" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << "\n";
        
    cout << "Post-order traversal:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << "\n";

    cout << "In-order traversal:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << "\n";

    cout << "BFS traversal:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << "\n";

    cout << "DFS traversal:" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << "\n";

    cout << "Heap traversal: \n";
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node)
    {
        cout << node->get_value() << ", ";
        // Should print: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    }
    cout << "\n";

    // Create SFML window for 3-ary tree
    sf::RenderWindow window2(sf::VideoMode(1000, 600), "3-ary Tree Drawing");

    Tree<double,3> three_ary_tree; // 3-ary tree
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
    
    drawTree(window2, three_ary_tree);

    // Display the window until it is closed
    window2.display();

    // SFML event loop for the 3-ary tree window
    while (window2.isOpen()) {
        sf::Event event;
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();
        }
    }
    
    cout << "3-ary Tree Traversals:\n" << endl;
    
    cout << "Pre-order traversal (DFS):" << endl;
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4
    cout << "\n";

    cout << "Post-order traversal:" << endl;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.5, 1.2, 1.6, 1.3, 1.4, 1.1
    cout << "\n";
        
    cout << "In-order traversal:" << endl;
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.5, 1.2, 1.1, 1.6, 1.3, 1.4
    cout << "\n";

    cout << "BFS traversal:" << endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << "\n";

    cout << "DFS traversal:" << endl;
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4
    cout << "\n";

    cout << "Heap traversal: \n";
    for (auto node = three_ary_tree.begin_heap(); node != three_ary_tree.end_heap(); ++node)
    {
        cout << node->get_value() << ", ";
        // Should print: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    }
    cout << "\n";

    // Create SFML window for complex tree
    sf::RenderWindow window_complex(sf::VideoMode(1000, 600), "Complex Tree Drawing");

    // Define complex numbers
    Complex root_complex(1.1, 2.2);
    Complex n1_complex(3.3, 4.4);
    Complex n2_complex(5.5, 6.6);
    Complex n3_complex(7.7, 8.8);
    Complex n4_complex(9.9, 10.10);
    Complex n5_complex(11.11, 12.12);

    // Create nodes
    Node<Complex> root_node_complex(root_complex);
    Node<Complex> n1_node_complex(n1_complex);
    Node<Complex> n2_node_complex(n2_complex);
    Node<Complex> n3_node_complex(n3_complex);
    Node<Complex> n4_node_complex(n4_complex);
    Node<Complex> n5_node_complex(n5_complex);

    // Create complex tree
    Tree<Complex> complex_tree;
    complex_tree.add_root(root_node_complex);
    complex_tree.add_sub_node(root_node_complex, n1_node_complex);
    complex_tree.add_sub_node(root_node_complex, n2_node_complex);
    complex_tree.add_sub_node(n1_node_complex, n3_node_complex);
    complex_tree.add_sub_node(n1_node_complex, n4_node_complex);
    complex_tree.add_sub_node(n2_node_complex, n5_node_complex);
    // The tree should look like:
    /**
     *       root = 1.1+2.2
     *     /      \
     *  3.3+4.4   5.5+6.6
     *   /         \
     * 7.7+8.8   9.9+10.10
     *              |
     *          11.11+12.12
     */

    drawTree(window_complex, complex_tree);

    // Display the window until it is closed
    window_complex.display();

    // SFML event loop for the complex tree window
    while (window_complex.isOpen()) {
        sf::Event event;
        while (window_complex.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_complex.close();
        }
    }
    
    cout << "Complex Tree Traversals:\n" << endl;
    
    cout << "Pre-order traversal (DFS):" << endl;
    for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.1+2.2, 3.3+4.4, 7.7+8.8, 9.9+10.10, 5.5+6.6, 11.11+12.12
    cout << "\n";

    cout << "Post-order traversal:" << endl;
    for (auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 7.7+8.8, 9.9+10.10, 3.3+4.4, 11.11+12.12, 5.5+6.6, 1.1+2.2
    cout << "\n";

    cout << "In-order traversal:" << endl;
    for (auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 7.7+8.8, 3.3+4.4, 9.9+10.10, 1.1+2.2, 11.11+12.12, 5.5+6.6
    cout << "\n";

    cout << "BFS traversal:" << endl;
    for (auto node = complex_tree.begin_bfs_scan(); node != complex_tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.1+2.2, 3.3+4.4, 5.5+6.6, 7.7+8.8, 9.9+10.10, 11.11+12.12
    cout << "\n";

    cout << "DFS traversal:" << endl;
    for (auto node = complex_tree.begin_dfs_scan(); node != complex_tree.end_dfs_scan(); ++node) {
        cout << node->get_value() << ", ";
    } // Should print: 1.1+2.2, 3.3+4.4, 7.7+8.8, 9.9+10.10, 5.5+6.6, 11.11+12.12
    cout << "\n";

    cout << "Heap traversal: \n";
    for (auto node = complex_tree.begin_heap(); node != complex_tree.end_heap(); ++node)
    {
        // Should print nodes in Heap order: 1.1+2.2, 3.3+4.4, 5.5+6.6, 7.7+8.8, 9.9+10.10, 11.11+12.12
        cout << node->get_value() << ", ";
    }
    cout << "\n";
    
    // Create SFML window for k=4 tree with 12 children
    sf::RenderWindow window(sf::VideoMode(1000, 600), "k=4 Tree with 12 Children");

    // Define nodes for k=4 tree
    Node<int> root_node_k4(1);
    Tree<int, 4> k4_tree; // k=4 tree that contains integers

    // Add root node
    k4_tree.add_root(root_node_k4);

    // Create nodes for demonstration
    Node<int> n1_k4(2);
    Node<int> n2_k4(3);
    Node<int> n3_k4(4);
    Node<int> n4_k4(5);
    Node<int> n5_k4(6);
    Node<int> n6_k4(7);
    Node<int> n7_k4(8);
    Node<int> n8_k4(9);
    Node<int> n9_k4(10);
    Node<int> n10_k4(11);
    Node<int> n11_k4(12);
    Node<int> n12_k4(13);

    // Add sub-nodes with corrected relationships
    k4_tree.add_sub_node(root_node_k4, n1_k4);
    k4_tree.add_sub_node(root_node_k4, n2_k4);
    k4_tree.add_sub_node(root_node_k4, n3_k4);
    k4_tree.add_sub_node(root_node_k4, n4_k4);
    k4_tree.add_sub_node(n1_k4, n5_k4);
    k4_tree.add_sub_node(n1_k4, n6_k4);
    k4_tree.add_sub_node(n1_k4, n7_k4);
    k4_tree.add_sub_node(n1_k4, n8_k4);
    k4_tree.add_sub_node(n3_k4, n9_k4);
    k4_tree.add_sub_node(n4_k4, n11_k4);
    k4_tree.add_sub_node(n4_k4, n12_k4);

    // The corrected k=4 tree with 12 children should look like:
    /**
     *               1
     *      /     |     \     \
     *     2      3      4     5
     *   / |\ \          |    / \
     *  6  7 8 9        10  12  13
     */

    drawTree(window, k4_tree);

    // Display the window until it is closed
    window.display();

    // SFML event loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    // Perform traversals and print the results
    cout << "Pre-order traversal:" << endl;
    for (auto node = k4_tree.begin_pre_order(); node != k4_tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << ", "; 
        // Should print nodes in pre-order: 1, 2, 6, 7, 8, 3, 9, 10, 11, 12, 4, 13, 5
    }
    cout << "\n";

    cout << "Post-order traversal:" << endl;
    for (auto node = k4_tree.begin_post_order(); node != k4_tree.end_post_order(); ++node)
    {
        cout << node->get_value() << ", "; 
        // Should print nodes in post-order: 1, 2, 6, 7, 8, 3, 9, 10, 11, 12, 4, 13, 5
    }
    cout << "\n";

    cout << "In-order traversal:" << endl;
    for (auto node = k4_tree.begin_in_order(); node != k4_tree.end_in_order(); ++node)
    {
        cout << node->get_value() << ", "; 
        // Should print nodes in in-order: 1, 2, 6, 7, 8, 3, 9, 10, 11, 12, 4, 13, 5
    }
    cout << "\n";

    cout << "BFS traversal:" << endl;
    for (auto node = k4_tree.begin_bfs_scan(); node != k4_tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << ", "; 
        // Should print nodes in BFS order: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
    }
    cout << "\n";

    cout << "DFS traversal:" << endl;
    for (auto node = k4_tree.begin_dfs_scan(); node != k4_tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << ", "; 
        // Should print nodes in DFS order: 1, 2, 6, 7, 8, 3, 9, 10, 11, 12, 4, 13, 5
    }
    cout << "\n";
    
    cout << "Heap traversal: \n";
    for (auto node = k4_tree.begin_heap(); node != k4_tree.end_heap(); ++node)
    {
        cout << node->get_value() << ", ";
        // Should print nodes in Heap order: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
    }
    cout << "\n";

    return 0;
}


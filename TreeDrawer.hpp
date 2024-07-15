// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef TREEDRAWER_HPP
#define TREEDRAWER_HPP

#include "Node.hpp"
#include "Tree.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

// Forward declaration for template function
template<typename T>
std::string nodeValueToString(const T& value);

template<>
std::string nodeValueToString<std::string>(const std::string& value) {
    return value; // Directly return the string value
}

template<typename T>
std::string nodeValueToString(const T& value) {
    std::ostringstream stream;
    if constexpr (std::is_floating_point<T>::value) {
        stream << std::fixed << std::setprecision(1) << value;
    } else {
        stream << value;
    }
    return stream.str();
}

// Function to draw the tree
template<typename T, int K>
void drawTree(sf::RenderWindow& window, const Tree<T, K>& tree) {
    const Node<T>* root = tree.getRoot();
    if (!root) return;

    const int nodeRadius = 40; // Larger radius of nodes
    const int lineWidth = 4; // Thicker lines connecting nodes
    const int levelSpacing = 200; // Increased vertical spacing between levels
    const int baseHorizontalSpacing = 200; // Increased base horizontal spacing between nodes

    // Calculate the dimensions of the tree to determine window size
    sf::Vector2f treeDimensions = calculateTreeDimensions(root, nodeRadius, baseHorizontalSpacing, levelSpacing);

    // Set the window size based on tree dimensions
    sf::Vector2u windowSize(treeDimensions.x + 100, treeDimensions.y + 100); // Adding padding for margin

    // Adjust the view to center the tree in the window
    sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    window.setView(view);

    // Initial position for root node
    int x = windowSize.x / 2; // Center horizontally
    int y = 50; // Initial y position

    drawTreeNode(window, root, x, y, nodeRadius, lineWidth, levelSpacing, baseHorizontalSpacing); // Pass parameters to drawTreeNode
}

// Function to calculate the dimensions of the tree
template<typename T>
sf::Vector2f calculateTreeDimensions(const Node<T>* node, int nodeRadius, int horizontalSpacing, int levelSpacing) {
    if (!node) return sf::Vector2f(0, 0);

    // Calculate dimensions recursively for each child
    sf::Vector2f dimensions(0, 0);
    int numChildren = node->children.size();
    
    // Calculate total width required for all children
    int totalWidth = (numChildren - 1) * horizontalSpacing;

    // Ensure sufficient spacing between children
    horizontalSpacing = std::max(horizontalSpacing, totalWidth / (numChildren + 1));

    // Calculate size of current node and all its children
    for (int i = 0; i < numChildren; ++i) {
        sf::Vector2f childDimensions = calculateTreeDimensions(node->children[i], nodeRadius, horizontalSpacing, levelSpacing);
        dimensions.x += childDimensions.x;
        dimensions.y = std::max(dimensions.y, childDimensions.y);
    }

    // Adjust dimensions for current node
    dimensions.x += std::max(nodeRadius * 2, totalWidth);
    dimensions.y += levelSpacing;

    return dimensions;
}


// Function to draw a node in the tree
template<typename T>
void drawTreeNode(sf::RenderWindow& window, const Node<T>* node, int x, int y, int nodeRadius, int lineWidth, int levelSpacing, int baseHorizontalSpacing) {
    if (!node) return;

    sf::CircleShape circle(nodeRadius); // Node shape
    circle.setPosition(x - nodeRadius, y - nodeRadius);
    circle.setFillColor(sf::Color::Cyan); // Node color
    circle.setOutlineColor(sf::Color::White); // Outline color
    circle.setOutlineThickness(2);

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Could not load font\n";
        return;
    }

    std::string nodeValueStr = nodeValueToString(node->get_value()); // Convert node value to string

    sf::Text text(nodeValueStr, font, 20); // Larger text with node value
    text.setFillColor(sf::Color::Blue);
    text.setPosition(x - text.getLocalBounds().width / 2, y - text.getLocalBounds().height / 2);

    window.draw(circle);
    window.draw(text);

    int numChildren = node->children.size();
    if (numChildren > 0) {
        // Calculate the total width required for all children nodes
        int totalWidth = (numChildren - 1) * baseHorizontalSpacing;

        // Ensure sufficient spacing between children
        int actualHorizontalSpacing = std::max(baseHorizontalSpacing, totalWidth / (numChildren + 1));

        int startX = x - totalWidth / 2; // Starting x position for the first child
        int startY = y + levelSpacing; // Vertical spacing for child nodes

        for (int i = 0; i < numChildren; ++i) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y + nodeRadius)),
                sf::Vertex(sf::Vector2f(startX + i * actualHorizontalSpacing, startY - nodeRadius))
            };
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
            line[0].color.a = 200; // Reduce transparency of lines
            line[1].color.a = 200;
            window.draw(line, 2, sf::Lines);

            drawTreeNode(window, node->children[i], startX + i * actualHorizontalSpacing, startY, nodeRadius, lineWidth, levelSpacing, baseHorizontalSpacing);
        }
    }
}

#endif // TREEDRAWER_HPP

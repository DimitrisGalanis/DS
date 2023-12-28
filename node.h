#ifndef BST_NODE_H
#define BST_NODE_H

#include <string>

class node {
private:
    int counter;
    std::string value;
    node *left;
    node *right;
    node *parent;
    int height;

public:

    node();
    explicit node(const std::string&);


    node * getLeft() const;
    node * getRight() const;
    node * getParent() const;
    void setLeft(node *);
    void setRight(node *);
    void setParent(node *);
    std::string getValue() const;
    void setValue(const std::string&);
    void setCounter(const int &);
    int getCounter() const;
    void setHeight(int);
    int getHeight() const;

};


#endif //BST_NODE_H
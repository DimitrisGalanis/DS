#include "node.h"

node::node()
{
    counter =0 ;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
}

node::node(const std::string &v)
{
    value = v;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    counter = 1 ;
    height = 1;
}

node *node::getLeft() const { return left; }

node *node::getRight() const { return right; }

node *node::getParent() const { return parent; }

void node::setLeft(node *L) { left = L; }

void node::setRight(node *R) { right = R; }

void node::setParent(node *P) { parent = P; }

std::string node::getValue() const{ return value; }

void node::setValue(const std::string &v) { value = v;}

void node::setCounter(const int &c) { counter = c; }

int node::getCounter() const {  return counter; }

void node::setHeight(int v) { height = v;}

int node::getHeight() const { return height; }







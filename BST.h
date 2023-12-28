#ifndef BST_BST_H
#define BST_BST_H

#include "node.h"

class BST
{
private:
    node *root;

    node *search (const std::string&);
    bool insert(node*,const std::string&);
    void inOrder (node *);
    void PostOrder (node *);
    void PreOrder (node *);


    node *min(node *);
    node *max(node *);
    bool remove (node *);
    int height (node *);
    void destroyTree(node *);
public:
    BST();
    ~BST();
    bool search (const std::string& , int &);
    bool insert (const std::string &);
    void printInOrder();
    void printPostOrder();
    void printPreOrder();

    bool min (std::string &);
    bool max (std::string &);
    bool remove (const std::string&);
    int height ();

};


#endif //BST_BST_H
